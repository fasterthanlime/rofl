#include <irrlicht.h>
#include "SKNLoader.h"
#include "ddslib/DdsImage.h"

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

	IMesh *mesh = SKN_load("data/Characters/Akali/Akali.skn");
	IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, false);
		
		char *texturePath = "data/Characters/Akali/Akali_Red_TX_CM.dds";
		DdsImage *ddsImage = new DdsImage(texturePath, driver);
		ITexture *texture = driver->addTexture(texturePath, ddsImage->getImage());
		node->setMaterialTexture(0, texture);
	}

	smgr->addCameraSceneNode(0, vector3df(0, 160, 80), vector3df(0, 150, 60));

	while(device->run()) {
		driver->beginScene(true, true, SColor(0, 255, 255, 255));

		smgr->drawAll();
		driver->endScene();
	}

	device->drop();

	return 0;
}
