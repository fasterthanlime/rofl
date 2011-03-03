#ifndef ROFL_SKLLoader_H
#define ROFL_SKLLoader_H

#include <irrlicht.h>
#include "ddslib/DdsImage.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

typedef struct SKL_Bone {
    char name[32]; // name of bone
    int parent; // id # of parent bone. Root bone = -1
    float scale; // scale
    float matrix[3][4]; // affine bone matrix [x1 x2 x3 xt
                        //                     y1 y2 y3 yt
                        //                     z1 z2 z3 zt]
} SDL_Bone;

typedef struct SKL_Skeleton {
	int numObjects; // number of objects (skeletons)
    int skeletonHash; // unique id number?
    int numElements; // number of bones
	SKL_Bone *bones;
} SDL_Skeleton;

SKL_Skeleton SKL_load(char *path);

#endif // ROFL_SKLLoader_H
