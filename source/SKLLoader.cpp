
#include "SKLLoader.h"
#include <stdio.h>

SKL_Skeleton SKL_load(char *path) {

    FILE *file = fopen(path, "rb");
    
    char fileType[9];
    memset(fileType, '\0', 9);
    fread(fileType, sizeof(char), 8, file);
    
    printf("fileType = %s\n", fileType);

    SKL_Skeleton skeleton;
    memset(&skeleton, '\0', sizeof(SKL_Skeleton));
    
    fread(&(skeleton.numObjects), sizeof(int), 1, file);
    fread(&(skeleton.skeletonHash), sizeof(int), 1, file);
    fread(&(skeleton.numElements), sizeof(int), 1, file);
    
    printf("numObjects = %d, skeletonHash = %d, numElements = %d\n", skeleton.numObjects, skeleton.skeletonHash, skeleton.numElements);
    
    skeleton.bones = (SKL_Bone *) calloc(skeleton.numElements, sizeof(SKL_Bone));
    fread(skeleton.bones, sizeof(SKL_Bone), skeleton.numElements, file);
    
    for (int i = 0; i < skeleton.numElements; i++) {
        printf("Bone #%d, name %s, parent is #%d, scale %.2f, affine = [%.2f, %.2f, %.2f], [%.2f, %.2f, %.2f], [%.2f, %.2f, %.2f], [%.2f, %.2f, %.2f]\n",
            i,
            skeleton.bones[i].name,
            skeleton.bones[i].parent,
            skeleton.bones[i].scale,
            skeleton.bones[i].matrix[0][0],
            skeleton.bones[i].matrix[1][0],
            skeleton.bones[i].matrix[2][0],
            skeleton.bones[i].matrix[0][1],
            skeleton.bones[i].matrix[1][1],
            skeleton.bones[i].matrix[2][1],
            skeleton.bones[i].matrix[0][2],
            skeleton.bones[i].matrix[1][2],
            skeleton.bones[i].matrix[2][2],
            skeleton.bones[i].matrix[0][3],
            skeleton.bones[i].matrix[1][3],
            skeleton.bones[i].matrix[2][3]
            );
    }
    
    fclose(file);
    
    return skeleton;
    
}
