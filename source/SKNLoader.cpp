
#include "SKNLoader.h"
#include <stdio.h>

IMesh *SKN_load(char *path) {

	// Construct dummy mesh for debugging purposes
	IMeshBuffer *buf = new SMeshBuffer();
	
	S3DVertex verts[4];
	verts[0] = S3DVertex(-1,  1, 0, 0, 0, 0, SColor(255,100,101,140), 0, 0);
	verts[1] = S3DVertex( 1,  1, 0, 0, 0, 0, SColor(100,255,101,140), 0, 0);
	verts[2] = S3DVertex( 1, -1, 0, 0, 0, 0, SColor(101,100,255,140), 0, 0);
	verts[3] = S3DVertex(-1, -1, 0, 0, 0, 0, SColor(255,255,101,140), 0, 0);
	u16 indices[6] = { 0, 1, 2, /* */ 2, 3, 0 };
	buf->append(verts, 4, indices, 6);
	
	SMesh *mesh = new SMesh();
	mesh->addMeshBuffer(buf);
	
	// Actual file reading
	FILE *file = fopen(path, "rb");
	if (!file) {
		printf("File not found: %s\n", path);
		return mesh;
	}
	
	
	fclose(file);
	
	return mesh;
	
}
