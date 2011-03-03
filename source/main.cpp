#include <irrlicht.h>
#include "SKNLoader.h"
#include "SKLLoader.h"
#include "math.h"

using namespace irr;
using namespace irrutils;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/*
Allows us to build on Windows, and avoiding the console window when using main()
instead of the platform-specific WinMain
*/
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

int main() {

	IrrlichtDevice *device = createDevice(
		video::EDT_OPENGL, // can be EDT_BURNINGSVIDEO, EDT_NULL, EDT_DIRECT3D8, EDT_DIRECT3D9, or EDT_OPENGL.
		dimension2d<u32>(1024, 768), // resolution of the window
		32, // bit depth
		false, // fullscreen
		false, // stencilbuffer
		false, // vsync
		NULL // eventReceiver
	);

	if (!device) {
		return 1;
	}

	device->setWindowCaption(L"Raiders Of Legend");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();

	smgr->setAmbientLight(SColorf(1.0, 1.0, 1.0, 1));

	IMeshSceneNode *node = SKN_addCharacter(driver, smgr, "data/Characters/Akali/Akali.skn", "data/Characters/Akali/Akali_Red_TX_CM.dds");
	SKL_Skeleton skeleton = SKL_load("data/Characters/Akali/Akali.skl");
	
	//node->setPosition(vector3df(-70, 0, 0));
	
	//IMeshSceneNode *node2 = SKN_addCharacter(driver, smgr, "data/Characters/MasterYi/MasterYi.skn", "data/Characters/MasterYi/AssassinMasterYi.dds");
	//node2->setPosition(vector3df(70, 0, 0));

	ICameraSceneNode *camera = smgr->addCameraSceneNode(0, vector3df(0, 120, 150), vector3df(0, 100, 0));

	float angle = 0.0f;

	SMaterial m; 
	m.Lighting = false;
	m.Thickness = 4.0;
	m.setFlag(EMF_ZWRITE_ENABLE, false);
	SColor white = SColor(128, 128, 128, 128);

	while(device->run()) {
		// Draw 3D objects
		driver->beginScene(true, true, SColor(0, 0, 0, 0));
		smgr->drawAll();
		
		// Draw skeleton lines
		driver->clearZBuffer();
		driver->setMaterial(m); 
		
		for (int i = 0; i < skeleton.numElements; i++) {
			driver->setTransform(ETS_WORLD, matrix4()); 
			SKL_Bone bone = skeleton.bones[i];
			if(bone.parent == -1) continue;
			SKL_Bone parent = skeleton.bones[bone.parent];
			driver->draw3DLine(
				vector3df(bone.matrix  [0][3],   bone.matrix[1][3],   bone.matrix[2][3]),
				vector3df(parent.matrix[0][3], parent.matrix[1][3], parent.matrix[2][3]),
				white);
		}
		driver->endScene();
		
		//node-> setRotation(vector3df(0, angle, 0));
		//node2->setRotation(vector3df(0, angle, 0));
		angle += 0.2f;
		
		camera->setPosition(vector3df(cos(angle / 180.0 * PI) * 150.0, 120, sin(angle / 180.0 * PI) * 150.0));
	}

	device->drop();

	return 0;
}
