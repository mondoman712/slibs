#include <GL/glew.h>
#include <SDL2/SDL.h>

typedef struct {
	SDL_Window * win;
	SDL_GLContext glc;
	GLushort w;
	GLushort h;
} Window;

/*
 * Reads and compiles a .glsl shader file in the shaders folder, from just the
 * core of the filename (to use shaders/vs1.glsl, filename is just vsl)
 */
GLuint create_shader (const GLenum shader_type, const char * filename);

/*
 * Takes a screenshot, saves it to scrn-yyyy-mm-dd-hh-mm-ss(-x).png
 */
GLuint take_screenshot (GLuint w, GLuint h);

/*
 * Handles window resize event
 */
void window_resize (Window * win);

/*
 * Creates an SDL window with gl context
 */
Window create_window (GLushort w, GLushort h, char * title);
