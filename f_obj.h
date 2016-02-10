#ifndef _F_OBJ_H
#define _F_OBJ_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <GL/glew.h>

GLuint read_obj (const char * filename, GLfloat ** vertices, char ** mtl_loc);

#endif /* _F_OBJ_H */
