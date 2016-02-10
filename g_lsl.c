#include <string.h>
#include <stdio.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include "f_png.h"
#include "g_lsl.h"

#define SHADER_DIR "src/shaders/"
#define SHADER_EXT ".glsl"

#define GL_MAJOR_VER 3
#define GL_MINOR_VER 3

/*
 * Reads and compiles a .glsl shader file in the shaders folder, from just the
 * core of the filename (to use shaders/vs1.glsl, filename is just vsl)
 */
GLuint create_shader (const GLenum shader_type, const char * filename)
{
	char _source[4096];
	char dest[64];

	/* Create full filename */
	strcpy(dest, SHADER_DIR);
	strcat(dest, filename);
	strcat(dest, SHADER_EXT);

	/* Open file */
	FILE * s = fopen(dest, "r");
	if (s == NULL) {
		fprintf(stderr, "Could not open file %s\n", dest);
		return 1;
	}

	/* Read all lines in file */
	int i = 0;
	char inc;
	while (fscanf(s, "%c", &inc) > 0)
		_source[i++] = inc;
	
	/* Close file */
	fclose(s);

	/* Add string terminator to file */
	_source[i - 1] = '\0';

	/* Change type of source */
	const char * source = _source;

	/* Compile Shader */
	GLuint shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	/* Check for and report errors */
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		char buff[512];
		glGetShaderInfoLog(shader, 512, NULL, buff);
		fprintf(stderr, "Shader %s failed to compile with error:\n", 
				filename);
		fprintf(stderr, "%s\n", buff);
		fprintf(stderr, "\n");
	}

	return shader;
}

/*
 * Create filename for screenshot
 */
static char * ss_filename (void)
{
	struct tm * tm;
	time_t t;
	char strtime[128];

	char * filename = malloc(128 * sizeof(char));
	GLushort i = 1;
	
	/* Create filename based on time */
	t = time(NULL);
	tm = localtime(&t);
	strftime(strtime, sizeof(strtime), "%Y-%m-%d-%H-%M-%S", tm);
	sprintf(filename, "screenshot-%s.png", strtime);

	/* If another file of this name exists add digits to the end */
	while (access(filename, F_OK) != -1)
		sprintf(filename, "screenshot-%s-%d.png", strtime, i++);

	return filename;
}

/*
 * Takes a screenshot, saves it to scrn-yyyy-mm-dd-hh-mm-ss(-x).png
 */
GLuint take_screenshot (GLuint w, GLuint h)
{
	GLuint ret = 0;
	GLubyte * pix = malloc(w * h * 3 * sizeof(GLubyte));
	char * filename;

	/* Get pixel data from OpenGL */
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, w, h);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid *) pix);

	/* Get filename */
	filename = ss_filename();
	
	/* Save the file and print out a message */
	if (access(filename, F_OK) == -1) {
		if (save_png(filename, pix, w, h)) { 
			ret = 1;
			fprintf(stderr, "Screenshot Failed\n");
		} else {
			printf("\nTaken screenshot %s\n", filename);
		}
	}

	free(pix);
	free(filename);

	return ret;
}

/*
 * Handles window resize event
 */
void window_resize (Window * win)
{
	GLint w, h;

	SDL_GetWindowSize(win->win, &w, &h);

	glViewport(0, 0, w, h);
	if (w > 0) win->w = w;
	if (h > 0) win->h = h;
}

/*
 * Creates an SDL window with gl context
 */
Window create_window (GLushort w, GLushort h, char * title)
{
	Window win;
	win.win = NULL;
	win.glc = NULL;

	win.w = w;
	win.h = h;

	if (SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "Failed to initialise SDL\n");
		return win;
	}

	win.win = SDL_CreateWindow(title,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			w, h,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL
				| SDL_WINDOW_RESIZABLE);

	if (win.win == NULL) {
		fprintf(stderr, "Failed to create SDL window\n");
		return win;
	}

	win.glc = SDL_GL_CreateContext(win.win);
	if (win.glc == NULL) {
		fprintf(stderr, "Failed to create OpenGL context\n");
		return win;
	}

	const unsigned char * version = glGetString(GL_VERSION);
	if (version == NULL) {
		fprintf(stderr, "Failed to get GL version\n");
		return win;
	} else {
		printf("GL version is: %s\n", version);
	}

	SDL_GL_MakeCurrent(win.win, win.glc);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, GL_MAJOR_VER);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, GL_MINOR_VER);

	glewExperimental = GL_TRUE;
	GLenum glew_status = glewInit();
	if (glew_status) {
		fprintf(stderr, "Error %s\n", glewGetErrorString(glew_status));
		return win;
	}

	return win;
}
