#include <irrlicht.h>
#include "SKNLoader.h"

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
	node->setPosition(vector3df(-70, 0, 0));
	
	IMeshSceneNode *node2 = SKN_addCharacter(driver, smgr, "data/Characters/MasterYi/MasterYi.skn", "data/Characters/MasterYi/AssassinMasterYi.dds");
	node2->setPosition(vector3df(70, 0, 0));

	smgr->addCameraSceneNode(0, vector3df(0, 150, 250), vector3df(0, 130, 60));

	float angle = 0.0f;

	while(device->run()) {
		driver->beginScene(true, true, SColor(0, 0, 0, 0));

		node-> setRotation(vector3df(0, angle, 0));
		node2->setRotation(vector3df(0, angle, 0));

		smgr->drawAll();
		driver->endScene();
		
		angle += 0.2f;
	}

	device->drop();

	return 0;
}
