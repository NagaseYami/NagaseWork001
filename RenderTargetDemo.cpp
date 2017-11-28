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



void RenderTargetDemo::Init()
{
	Camera::SetMainCamera(&m_Camera);

	Object2DPolygon * Screen = new Object2DPolygon;
	Screen->Init();
	Screen->SetPos(Vector2(0.0f, 0.0f));
	Screen->SetSize(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
	Screen->AddTexture(Texture::GetTexture("Screen"));

	ObjectXModel * model = new ObjectXModel("data/Model/47/47.x");
	model->Init();
	model->SetLight(false);
	model->SetTexture(Texture::LoadTextureFromFile("data/Model/47/47_1.jpg"), 0);
	model->SetTexture(Texture::LoadTextureFromFile("data/Model/47/47_2.jpg"), 1);
	model->SetTexture(Texture::LoadTextureFromFile("data/Model/47/47_2.jpg"), 2);
	model->SetTexture(Texture::LoadTextureFromFile("data/Model/47/47_1.jpg"), 3);
	model->SetTexture(Texture::LoadTextureFromFile("data/Model/47/47_3.jpg"), 4);
	model->SetTra(Vector3(0.0f, 0.65f, 0.0f));

	Texture::AddObjectToRenderTargetTexture(model, "Screen");
}

void RenderTargetDemo::Update()
{

}

void RenderTargetDemo::Uninit()
{
	Object::UninitAll();
}
#endif	