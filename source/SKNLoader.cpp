
#include "SKNLoader.h"
#include <stdio.h>

typedef struct SKNVertex {
	float position[3];
	signed char boneIndex[4];
	float weights[4];
	float normals[3];
	float texcoords[2];
} SKNVertex;

typedef struct SKNMaterial {
	char name[65];
	int startVertex, numVertices, startIndex, numIndices;
} SKNMaterial;

IMesh *SKN_load(char *path) {

	FILE *file = fopen(path, "rb");
	if (!file) {
		printf("File not found: %s\n", path);
		exit(1);
	}
	
	int magic;
	short matHeader, numObjects;
	
	fread(&magic, sizeof(int), 1, file);

	fread(&matHeader, sizeof(short), 1, file);	
	fread(&numObjects, sizeof(short), 1, file);
	
	printf("magic = %d, matHeader = %d, numObjects = %d\n", magic, matHeader, numObjects);

	SKNMaterial *materials;
	
	if (matHeader > 0) {
		int numMaterials;
		fread(&numMaterials, sizeof(int), 1, file);
		materials = (SKNMaterial *) calloc(numMaterials, sizeof(SKNMaterial));
		
		for(int i = 0; i < numMaterials; i++) {
			fread(&(materials[i].name), sizeof(char), 64, file);
			fread(&(materials[i].startVertex), sizeof(int), 1, file);
			fread(&(materials[i].numVertices), sizeof(int), 1, file);
			fread(&(materials[i].startIndex), sizeof(int), 1, file);
			fread(&(materials[i].numIndices), sizeof(int), 1, file);
			
			printf("Material %s, vertex start/num = %d/%d, index start/num = %d/%d\n",
				materials[i].name,
				materials[i].startVertex,
				materials[i].numVertices,
				materials[i].startIndex,
				materials[i].numIndices);
		}
	}
	
	int numIndices, numVertices;
	fread(&numIndices,  sizeof(int), 1, file);
	fread(&numVertices, sizeof(int), 1, file);
	printf("%d indices and %d vertices\n", numIndices, numVertices);

	u16 indices[numIndices];
	fread(indices, sizeof(u16), numIndices, file);
	
	for(int i = 0; i < 10; i++) {
		printf("index #%d = %u\n", i, indices[i]);
	}
	
	SKNVertex rawVerts[numVertices];
	fread(rawVerts, sizeof(SKNVertex), numVertices, file);
	
	S3DVertex verts[numVertices];
	for(int i = 0; i < numVertices; i++) {
		verts[i] = S3DVertex(
			rawVerts[i].position[0],
			rawVerts[i].position[1],
			rawVerts[i].position[2],
			rawVerts[i].normals[0],
			rawVerts[i].normals[1],
			rawVerts[i].normals[2],
			SColor(255, 255, 255, 255),
			rawVerts[i].texcoords[0],
			rawVerts[i].texcoords[1]
		);
		
		if (i < 10) {
			printf("vertex #%d = (%.2f, %.2f, %.2f)\n", i, rawVerts[i].position[0], rawVerts[i].position[1], rawVerts[i].position[2]);
		}
	}
	
	IMeshBuffer *buf = new SMeshBuffer();

	buf->append(verts, numVertices, indices, numIndices);
	
	SMesh *mesh = new SMesh();
	mesh->addMeshBuffer(buf);
	
	fclose(file);
	
	return mesh;
	
}
