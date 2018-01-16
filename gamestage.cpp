#include "main.h"
#include "object.h"
#include "texture.h"
#include "objectXModel.h"
#include "object3dpolygon.h"
#include "camera.h"
#include "tpscamera.h"
#include "scene.h"
#include "gamestage.h"
#include "player.h"


void GameStage::Init()
{	
	Camera::SetMainCamera(&m_Camera);
	for (int i = 0; i < 4; i++)
	{
		m_pQuarter[i] = new ObjectXModel("data/Model/quarter/quarter.x");
		m_pQuarter[i]->Init();
		m_pQuarter[i]->SetRFP(Vector3(0.0f, D3DX_PI / 2.0f * i, 0.0f));
		m_pQuarter[i]->SetTFP(Vector3(0.0f, -5.0f, 0.0f));
	}
	Player::Init();
}

void GameStage::Update()
{
	Player::Update();
}

void GameStage::Uninit()
{
}
