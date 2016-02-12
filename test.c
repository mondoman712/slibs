#include "f_obj.h"

int main ()
{
	char * mtl_loc = malloc(256);
	GLfloat * vertices = NULL;
	printf("%i\n", read_obj("cube.obj", &vertices, &mtl_loc));	
	printf("%s", mtl_loc);
	return 0;
}
