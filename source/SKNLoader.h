#ifndef ROFL_SKNLoader_H
#define ROFL_SKNLoader_H

#include <irrlicht.h>
#include "ddslib/DdsImage.h"

using namespace irr;
using namespace irrutils;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;

IMesh *SKN_load(char *path);
IMeshSceneNode* SKN_addCharacter(IVideoDriver* driver, ISceneManager* smgr, char *skinPath, char *texturePath);

#endif // ROFL_SKNLoader_H
