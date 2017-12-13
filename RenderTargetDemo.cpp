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

	//Object2DPolygon * Screen = new Object2DPolygon;
	//Screen->Init();
	//Screen->SetPos(Vector2(0.0f, 0.0f));
	//Screen->SetSize(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
	//Screen->AddTexture(Texture::GetTexture("Screen"));	

	Texture::CreateEmptyTexture("ZoomBufferTex", Vector2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), false);

	//ObjectXModel * ModelObj = new ObjectXModel("data/Model/47/47.x");
	//ModelObj->Init();
	//ModelObj->SetLight(false);
	//ModelObj->SetTexture(Texture::LoadTextureFromFile("data/Model/47/47_1.jpg"), 0);
	//ModelObj->SetTexture(Texture::LoadTextureFromFile("data/Model/47/47_2.jpg"), 1);
	//ModelObj->SetTexture(Texture::LoadTextureFromFile("data/Model/47/47_2.jpg"), 2);
	//ModelObj->SetTexture(Texture::LoadTextureFromFile("data/Model/47/47_1.jpg"), 3);
	//ModelObj->SetTexture(Texture::LoadTextureFromFile("data/Model/47/47_3.jpg"), 4);
	//ModelObj->SetTra(Vector3(0.0f, 0.65f, 0.0f));
	//Texture::AddObjectToRenderTargetTexture(ModelObj, "ZoomBufferTex");
	//ModelObj->SetRenderTarget(false);

	for (int i = 0; i < 1; i++)
	{
		ObjectParticle * ParticleObj = new ObjectParticle;
		ParticleObj->Init();
		//ParticleObj->AddTexture(Texture::LoadTextureFromFile("data/Texture/Particles/Heart001.png"));
		Texture::AddObjectToRenderTargetTexture(ParticleObj, "ZoomBufferTex");
	}	

	Object2DPolygon * ParticlePolygon = new Object2DPolygon;
	ParticlePolygon->Init();
	ParticlePolygon->SetSize(Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
	ParticlePolygon->AddTexture(Texture::GetTexture("ZoomBufferTex"));
}

void RenderTargetDemo::Update()
{

}

void RenderTargetDemo::Uninit()
{
	Object::UninitAll();
}
#endif	