#include "f_obj.h"

#define BUFFSIZE 256

/*
 * Compares first strlen(pre) chars of str with pre
 */
static int check_prefix (const char * str, const char * pre)
{
	unsigned int i;
	size_t n = strlen(pre);

	if (n > strlen(str)) return 0;

	for (i = 0; i < strlen(pre); i++) {
		if (pre[i] != str[i])
			return 0;
	}

	return 1;
}

/*
 * Reads a vector line of an obj file and turns it into an array of numbers
 */
static void read_vect (GLfloat * buff, char * vect, int c)
{
	char * v = strtok(vect, " ");
	int i = 0;

	for (i = 0; i < c; i++) {
		if (v == NULL) break;

		v = strtok(NULL, " ");
		*(buff + i) = atof(v);
	}
}

/*
 * Reads a face line and turns it into an array of numbers
 */
static void read_face (GLuint * buff, char * face)
{
	char * f = strtok(face, " /");
	int i;
	
	for (i = 0; i < 9; i++) {
		f = strtok(NULL, " /");
		buff[i] = atoi(f) - 1;
	}
}

/*
 * Reads an obj file and return all of the vertices in an array
 */
GLuint read_obj (const char * filename, GLfloat ** vertices, char ** mtl_loc)
{
	int fc = 0, vc = 0, vtc = 0, vnc = 0;
	char line[BUFFSIZE];

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
	GLfloat * texns = malloc(vtc * 2 * sizeof(GLfloat));
	fc = 0, vc = 0, vtc = 0, vnc = 0;

	while (fgets(line, sizeof(line), objf)) {
		if (check_prefix(line, "f ")) {
			read_face((faces + fc), line);
			fc += 9;
		} else if (check_prefix(line, "v ")) {
			read_vect((verts + vc), line, 3);
			vc += 3;
		} else if (check_prefix(line, "vn ")) {
			read_vect((norms + vnc), line, 3);
			vnc += 3;
		} else if (check_prefix(line, "vt ")) {
			read_vect((texns + vtc), line, 2);
			vtc += 2;
		} else if (check_prefix(line, "mtllib ")) {
			strtok(line, " ");
			strcpy(*mtl_loc, strtok(NULL, " "));

			/* Remove trailing \n from string */
			char * pos;
			if ((pos = strchr(*mtl_loc, '\n')) != NULL)
				*pos = '\0';
		}
	}

	fclose(objf);

	GLfloat * ret = malloc(fc * 24 * sizeof(GLfloat));
	vc = 0;
	int i, j = 0;
	for (i = 0; i < fc / 3 * 8; i += 8) {
		*(ret + i) = verts[faces[j] * 3];
		*(ret + i + 1) = verts[faces[j] * 3 + 1];
		*(ret + i + 2) = verts[faces[j] * 3 + 2];
		*(ret + i + 3) = texns[faces[j + 1] * 2];
		*(ret + i + 4) = texns[faces[j + 1] * 2 + 1];
		*(ret + i + 5) = norms[faces[j + 2] * 3];
		*(ret + i + 6) = norms[faces[j + 2] * 3 + 1];
		*(ret + i + 7) = norms[faces[j + 2] * 3 + 2];
		vc++; j += 3;
	}

	free(faces);
	free(verts);
	free(norms);
	free(texns);

	*vertices = ret;

	return vc * 8;
}
