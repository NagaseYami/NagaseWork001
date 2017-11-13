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

void TestScene::Init()
{
	Camera::SetMainCamera(&m_Camera);

	Object2DPolygon * polygon2d = new Object2DPolygon;
	polygon2d->SetTexture(Texture::LoadTexture("data/Texture/Test/test1.png"));
	polygon2d->SetSize(Vector2(128.0f, 72.0f));
	polygon2d->Init();

	Object3DPolygon * polygon3d = new Object3DPolygon;
	polygon3d->SetTexture(Texture::LoadTexture("data/Texture/Test/test1.png"));
	polygon3d->SetSize(Vector3(12.8f, 7.2f,0.0f));
	polygon3d->SetPosbyCenter(Vector3(0.0f,0.0f,0.0f));
	polygon3d->Init();
}

void TestScene::Update()
{
	if (Input::IsDown(Input::KeySpace))
	{
   		TestScene2 * Scene = new TestScene2;
		Scene::ToNextScene(Scene);
	}
}

void TestScene::Uninit()
{
	Object::UninitAll();
}
#endif // _DEBUG