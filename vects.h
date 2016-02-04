#ifndef _VECTS_H
#define _VECTS_H

#include <math.h>
#include <GL/glew.h>

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} vec3;

/*
 * finds the modulus of a 1x3 vector
 */
GLfloat mod_vec3 (vec3 in);

/*
 * Finds the normal of a 1x3 vector
 */
vec3 norm_vec3 (vec3 in);

/*
 * Finds the cross product of vectors a and b
 */
vec3 cross_vec3 (vec3 a, vec3 b);

/*
 * Calculates the dot product between two 3 value vectors
 */
GLfloat dot_vec3 (vec3 a, vec3 b);

#endif /* _VECTS_H */
