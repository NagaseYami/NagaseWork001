#ifdef _DEBUG
#include "main.h"
#include "scene.h"
#include "texture.h"
#include "object.h"
#include "object2dpolygon.h"
#include "includeallscenes.h"

void TestScene2::Init()
{
	Object2DPolygon * test = new Object2DPolygon;
	test->SetTexture(Texture::LoadTexture("data/Texture/Test/test2.png"));
	test->SetSize(Vector2(1280.0f, 720.0f));
	test->Init();
}

void TestScene2::Update()
{
	if (Input::GetKeyPress(Input::KeySpace))
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