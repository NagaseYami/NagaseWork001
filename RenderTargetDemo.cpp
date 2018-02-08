#ifdef _DEBUG
#include "main.h"
#include "texture.h"
#include "object.h"
#include "object2dpolygon.h"
#include "object3dpolygon.h"
#include "objectXModel.h"
#include "objectstencilshadow.h"
#include "objectparticle.h"
#include "camera.h"
#include "includeallcameras.h"
#include "scene.h"
#include "includeallscenes.h"



void RenderTargetDemo::Init()
{
	Camera::SetMainCamera(&m_Camera);
	
	Object2DPolygon * Toon = new Object2DPolygon;
	Toon->Init();
	Toon->SetSize(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
	Toon->AddTexture(Texture::CreateEmptyTexture("ToonShader", Vector2(SCREEN_WIDTH, SCREEN_HEIGHT)));

	ObjectXModel * model = new ObjectXModel("data/Model/AKRhead/01_head.x");
	Texture::AddObjectToRenderTargetTexture(model, "ToonShader");
	model->DontDrawThisOnBackBuffer(false);
	model->SetSFP(Vector3(0.1f, 0.1f, 0.1f));
	model->Init();
}

void RenderTargetDemo::Update()
{

}

void RenderTargetDemo::Uninit()
{
	Object::UninitAll();
}
#endif	