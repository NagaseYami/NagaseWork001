#ifdef _DEBUG
#include "main.h"
#include "texture.h"
#include "object.h"
#include "object2dpolygon.h"
#include "camera.h"
#include "includeallcameras.h"
#include "scene.h"
#include "includeallscenes.h"

void TestScene2::Init()
{
	Object2DPolygon * test = new Object2DPolygon;
	test->AddTexture(Texture::LoadTextureFromFile("data/Texture/Test/test2.png"));
	test->SetSize(Vector2(128.0f, 72.0f));
	test->Init();
}

void TestScene2::Update()
{
	if (Input::GetAxis(Input::MouseAxisX) > 0.5f)
	{
		TestScene * Scene = new TestScene;
		Scene::ToNextScene(Scene);
	}
}

void TestScene2::Uninit()
{
	Object::UninitAll();
}
#endif // _DEBUG