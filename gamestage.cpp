#include "main.h"
#include "object.h"
#include "texture.h"
#include "object2dpolygon.h"
#include "objectXModel.h"
#include "object3dpolygon.h"
#include "objectattractionparticle.h"
#include "camera.h"
#include "tpscamera.h"
#include "scene.h"
#include "gamestage.h"
#include "player.h"
#include "boss.h"

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
