#include "f_obj.h"

int check_prefix (const char * str, const char * pre)
{
	int i;
	int n = strlen(pre);

	if (n > strlen(str)) return 0;

	for (i = 0; i < strlen(pre); i++) {
		if (pre[i] != str[i])
			return 0;
	}

	return 1;
}

GLuint read_obj (const char * filename, GLfloat ** vertices, char ** mtl_loc)
{
	int fc = 0, vc = 0, vtc = 0, vnc = 0;
	char line[256];

	FILE * objf = fopen(filename, "r"); 
	if (objf == NULL) {
		fprintf(stderr, "Failed to open %s", filename);
		return 0;
	}

	/* Count number of each vertex type */
	while (fgets(line, sizeof(line), objf)) {
		if (check_prefix(line, "f ")) fc++;
		if (check_prefix(line, "v ")) vc++;
		if (check_prefix(line, "vn ")) vnc++;
		if (check_prefix(line, "vt ")) vtc++;
	}

	rewind(objf);

	GLuint * faces = malloc(fc * 9 * sizeof(GLuint));
	GLfloat * verts = malloc(vc * 3 * sizeof(GLfloat));
	GLfloat * norms = malloc(vnc * 3 * sizeof(GLfloat));
	GLfloat * texns = malloc(vtc * 3 * sizeof(GLfloat));

	while (fgets(line, sizeof(line), objf)) {
		if (check_prefix(line, "f ")) {

		} else if (check_prefix(line, "v ")) {

		} else if (check_prefix(line, "vn ")) {

		} else if (check_prefix(line, "vt ")) {

		}
	}

	fclose(objf);

	return fc;
}
