#include "f_obj.h"

int main ()
{
	char * mtl_loc = malloc(256);
	GLfloat * vertices = NULL;
	GLuint n = read_obj("cube.obj", &vertices, &mtl_loc);
	GLuint i;

	printf("%i\n", n);	
	printf("%s\n", mtl_loc);
	for (i = 0; i < n * 8; i += 8) {
		printf("%f, ", *(vertices + i));
		printf("%f, ", *(vertices + i + 1));
		printf("%f, ", *(vertices + i + 2));
		printf("%f, ", *(vertices + i + 3));
		printf("%f, ", *(vertices + i + 4));
		printf("%f, ", *(vertices + i + 5));
		printf("%f, ", *(vertices + i + 6));
		printf("%f\n", *(vertices + i + 7));
	}

	FILE * fp = fopen(mtl_loc, "r");
	if (fp == NULL) {
		fprintf(stderr, "Failed to open %s\n", mtl_loc);
		return 1;
	}
 
	fclose(fp);
	free(mtl_loc);
	free(vertices);
	return 0;
}
