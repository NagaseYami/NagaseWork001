#ifdef _DEBUG
#include "main.h"
#include "scene.h"
#include "texture.h"
#include "object.h"
#include "object2dpolygon.h"
#include "includeallscenes.h"

void TestScene::Init()
{
	Object2DPolygon * test = new Object2DPolygon;
	test->SetTexture(Texture::LoadTexture("data/Texture/Test/test1.png"));
	test->SetSize(Vector2(1280.0f, 720.0f));
	test->Init();
}

void TestScene::Update()
{
	if (Input::GetKeyPress(Input::KeySpace))
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