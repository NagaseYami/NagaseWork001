#ifdef _DEBUG
#include "main.h"
#include "texture.h"
#include "object.h"
#include "object2dpolygon.h"
#include "object3dpolygon.h"
#include "camera.h"
#include "includeallcameras.h"
#include "scene.h"
#include "includeallscenes.h"

void TestScene2::Init()
{
	Camera::SetMainCamera(&m_Camera);
	
}

void TestScene2::Update()
{
}

void TestScene2::Uninit()
{
	Object::UninitAll();
}
#endif // _DEBUG