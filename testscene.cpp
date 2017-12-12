#ifdef _DEBUG
#include "main.h"
#include "texture.h"
#include "object.h"
#include "object2dpolygon.h"
#include "object3dpolygon.h"
#include "objectXModel.h"
#include "objectparticle.h"
#include "objectstencilshadow.h"
#include "camera.h"
#include "light.h"
#include "includeallcameras.h"
#include "scene.h"
#include "includeallscenes.h"

void TestScene::Init()
{
	Camera::SetMainCamera(&m_Camera);
	D3DLIGHT9 light;
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	Light::CreateLight(light);

	//ObjectParticle * particle = new ObjectParticle;
	//particle->AddTexture(Texture::LoadTextureFromFile("data/Texture/Test/test1.png"));
	//particle->Init();

	Object3DPolygon * polygon3d = new Object3DPolygon;
	polygon3d->AddTexture(Texture::LoadTextureFromFile("data/Texture/Test/test1.png"));
	polygon3d->SetSize(Vector3(12.8f, 7.2f, 0.0f));
	polygon3d->SetPosbyCenter(Vector3(0.0f, 0.0f, 0.0f));
	polygon3d->SetRot(Vector3(AngletoRadian(90.0f), 0.0f, 0.0f));
	polygon3d->Init();

	//ObjectXModel * model = new ObjectXModel("data/Model/gradriel/gradriel.x");
	//model->Init();
	//model->SetTexture(Texture::LoadTextureFromFile("data/Model/gradriel/gradriel_tex.dds"), 0);
	//model->SetTFP(Vector3(0.0f, 0.0f, 0.0f));

	//ObjectXModel * model2 = new ObjectXModel("data/Model/AKRhead/01_head.x");
	//model2->Init();
	//model2->SetTFP(Vector3(-3.0f, 0.0f, 0.0f));
	//model2->SetSca(Vector3(0.1f,0.1f,0.1f));

	//ObjectXModel * model3 = new ObjectXModel("data/Model/cart/cart.x");
	//model3->Init();
	//model3->SetTexture(Texture::LoadTextureFromFile("data/MOdel/cart/horse.bmp"), 0);
	//model3->SetTexture(Texture::LoadTextureFromFile("data/MOdel/cart/cart.bmp"), 1);
	//model3->SetTFP(Vector3(3.0f, 0.0f, 0.0f));

	ObjectXModel * model4 = new ObjectXModel("data/Model/Sphere/Sphere.x");	
	model4->Init();
	model4->SetTexture(Texture::LoadTextureFromFile("data/Model/Sphere/DiffuseMap.dds"), 0);
	model4->SetTFP(Vector3(0.0f, 0.8f, 0.0f));
	model4->SetSca(Vector3(0.1f, 0.1f, 0.1f));
}																	

void TestScene::Update()
{

}

void TestScene::Uninit()
{
	Object::UninitAll();
}
#endif // _DEBUG