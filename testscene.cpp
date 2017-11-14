#ifdef _DEBUG
#include "main.h"
#include "texture.h"
#include "object.h"
#include "object2dpolygon.h"
#include "object3dpolygon.h"
#include "objectXModel.h"
#include "objectstencilshadow.h"
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
	polygon3d->SetRot(Vector3(AngletoRadian(90.0f), 0.0f, 0.0f));
	polygon3d->Init();
	polygon3d->SetLight(false);

	ObjectStencilShadow * shadow = new ObjectStencilShadow();
	shadow->Init();

	ObjectXModel * model = new ObjectXModel("data/Model/47/47.x");
	model->Init();
	model->SetLight(false);
	model->SetTexture(Texture::LoadTexture("data/Model/47/47_1.jpg"), 0);
	model->SetTexture(Texture::LoadTexture("data/Model/47/47_2.jpg"), 1);
	model->SetTexture(Texture::LoadTexture("data/Model/47/47_2.jpg"), 2);
	model->SetTexture(Texture::LoadTexture("data/Model/47/47_1.jpg"), 3);
	model->SetTexture(Texture::LoadTexture("data/Model/47/47_3.jpg"), 4);
	model->SetTra(Vector3(0.0f, 0.65f, 0.0f));
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