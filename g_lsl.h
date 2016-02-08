#include <GL/glew.h>

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
void window_resize (SDL_Window * window, GLuint * width, GLuint * height);
