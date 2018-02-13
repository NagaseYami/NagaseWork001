#include "../Boss/boss.h"
#include "../Camera/camera.h"
#include "../Camera/tpscamera.h"
#include "../Main/main.h"
#include "../Object/objectattractionparticle.h"
#include "../Object/objectXModel.h"
#include "../Player/player.h"
#include "../Texture/texture.h"
#include "gamestage.h"
#include "scene.h"
void GameStage::Init()
{	
	Camera::SetMainCamera(&m_Camera);
	for (int i = 0; i < 4; i++)
	{
		m_pQuarter[i] = new ObjectXModel("data/Model/quarter/quarter.x");
		m_pQuarter[i]->Init();
		Texture::AddObjectToRenderTargetTexture(m_pQuarter[i], "ShadowMap");
		m_pQuarter[i]->SetRFP(Vector3(0.0f, D3DX_PI / 2.0f * i, 0.0f));
		m_pQuarter[i]->SetTFP(Vector3(0.0f, -5.0f, 0.0f));
	}

	Player::Init();

	m_pBoss = new Boss();
	m_pBoss->Init();

	ObjectAttractionParticle * pParticle = new ObjectAttractionParticle();
	pParticle->Init();
}

void GameStage::Update()
{
	Player::Update();
	m_pBoss->UpdateMain();
}

void GameStage::Uninit()
{
}
