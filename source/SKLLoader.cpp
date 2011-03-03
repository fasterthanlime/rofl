
#include "SKLLoader.h"
#include <stdio.h>

void SKL_load(char *path) {

    FILE *file = fopen(path, "rb");
    
    char fileType[9];
    memset(fileType, '\0', 9);
    fread(fileType, sizeof(char), 8, file);
    
    printf("fileType = %s\n", fileType);
    
    int numObjects; // number of objects (skeletons)
    int skeletonHash; // unique id number?
    int numElements; // number of bones
    
    fread(&numObjects, sizeof(int), 1, file);
    fread(&skeletonHash, sizeof(int), 1, file);
    fread(&numElements, sizeof(int), 1, file);
    
    printf("numObjects = %d, skeletonHash = %d, numElements = %d\n", numObjects, skeletonHash, numElements);
    
    SKL_Bone *bones = (SKL_Bone *) calloc(numElements, sizeof(SKL_Bone));
    fread(bones, sizeof(SKL_Bone), numElements, file);
    
    for (int i = 0; i < 10; i++) {
        printf("Bone #%d, name %s\n", i, bones[i].name);
    }
    
    fclose(file);
    
}
