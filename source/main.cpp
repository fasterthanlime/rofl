#include <irrlicht.h>

using namespace irr;

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
	
	IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
	if (node) {
		node->setMaterialFlag(EMF_LIGHTING, false);
		//node->setMaterialTexture(0, driver->getTexture("../../media/sydney.bmp"));
	}

	smgr->addCameraSceneNode(0, vector3df(0, 5, -5), vector3df(0,0,0));

	while(device->run())
	{
		driver->beginScene(true, true, SColor(255,100,101,140));

		smgr->drawAll();
		driver->endScene();
	}

	device->drop();

	return 0;
}
