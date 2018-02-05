#include "main.h"
#include "object.h"
#include "texture.h"
#include "objectXModel.h"
#include "player.h"
#include "boss.h"
#include <fstream>

Light Boss::m_Light[4];

void Boss::Init()
{
	XModelInit();
	ParentInit();
	TransformInit();
	MotionInit();
	PointLightInit();
	ShaderInit();
	ChangeMotion("Attack1");
	m_Dir = Vector3(0.0f, 0.0f, -1.0f);
	pPart[0]->SetRFP(Vector3(0.0f, 0.0f, 0.0f));
}

void Boss::UpdateMain()
{
	SetModelTimer(m_Timer);
	TimeUpdate(m_Motion[m_PlayingMotion].MotionList[0].at(m_Motion[m_PlayingMotion].MotionList[0].size() - 1).Frame);
}

void Boss::XModelInit()
{
	pPart[0] = new ObjectXModel("data/Model/Boss/Body.x");
	pPart[1] = new ObjectXModel("data/Model/Boss/Head.x");
	pPart[6] = new ObjectXModel("data/Model/crowbar/crowbar.x");

	for (int i = 0; i < 4; i++)
	{
		pPart[2 + i] = new ObjectXModel("data/Model/Boss/AHLF.x");
	}

	for (int i = 0; i < 7; i++)
	{
		pPart[i]->Init();
		Texture::AddObjectToRenderTargetTexture(pPart[i], "ShadowMap");
	}
}

void Boss::ParentInit()
{
	pPart[1]->SetParent(pPart[0]);
	pPart[2]->SetParent(pPart[0]);
	pPart[3]->SetParent(pPart[2]);
	pPart[4]->SetParent(pPart[0]);
	pPart[5]->SetParent(pPart[4]);
	pPart[6]->SetParent(pPart[3]);
}

void Boss::TransformInit()
{
	pPart[0]->SetTFP(Vector3(0.0f, 20.0f, 0.0f));
	pPart[1]->SetTFP(Vector3(0.0f, 2.0f, 0.0f));
	pPart[2]->SetTFP(Vector3(-1.5f, 1.6f, 0.0f));
	pPart[3]->SetTFP(Vector3(0.0f, -1.9f, 0.0f));
	pPart[4]->SetTFP(Vector3(1.5f, 1.6f, 0.0f));
	pPart[5]->SetTFP(Vector3(0.0f, -1.9f, 0.0f));
	pPart[6]->SetTFP(Vector3(0.0f, -1.2f, 0.0f));
	pPart[6]->SetRFP(Vector3(-1.57f, 0.0f, 0.0f));

	pPart[0]->SetSFP(Vector3(10.0f, 10.0f, 10.0f));
}

void Boss::MotionInit()
{
	LoadMotionFromFile("data/Model/Boss/Neutral.txt", true);
	LoadMotionFromFile("data/Model/Boss/Attack1.txt", false);
}

void Boss::PointLightInit()
{
	m_Light[0].SetColor(Vector3(1.0f, 0.0f, 0.0f));
	m_Light[1].SetColor(Vector3(0.0f, 1.0f, 0.0f));
	m_Light[2].SetColor(Vector3(0.0f, 0.0f, 1.0f));
	m_Light[3].SetColor(Vector3(1.0f, 1.0f, 0.0f));

	m_Light[0].SetTra(Vector3(30.0f, 5.0f, 0.0f));
	m_Light[1].SetTra(Vector3(-30.0f, 5.0f, 0.0f));
	m_Light[2].SetTra(Vector3(0.0f, 5.0f, 30.0f));
	m_Light[3].SetTra(Vector3(0.0f, 5.0f, -30.0f));
}

void Boss::ShaderInit()
{
	for (auto i = 0; i < 7; i++)
	{
		pPart[i]->SetVariableToShaderFn(UpdateShaderVariable);
	}
}

void Boss::LoadMotionFromFile(string filename, bool canbebreak)
{
	ifstream ifs(filename);

	if (ifs.fail())
		return;

	string str, name;

	//MotionName
	do
	{
		getline(ifs, str);
	} while (str != "[MotionName]");

	getline(ifs, name);
	do
	{
		//Data
		do
		{
			getline(ifs, str);
			if (str == "[End]")
			{
				return;
			}
		} while (str != "[KeyData]");//先頭token

									 //パーツ番号
		getline(ifs, str);
		int partnum = atoi(str.c_str());
		if (partnum > 6)continue;

		//TRA ROT FRAME
		getline(ifs, str);
		float f1 = (float)atof(str.c_str());
		getline(ifs, str);
		float f2 = (float)atof(str.c_str());
		getline(ifs, str);
		float f3 = (float)atof(str.c_str());
		getline(ifs, str);
		float f4 = (float)atof(str.c_str());
		getline(ifs, str);
		float f5 = (float)atof(str.c_str());
		getline(ifs, str);
		float f6 = (float)atof(str.c_str());
		getline(ifs, str);
		int frame = atoi(str.c_str());

		KEY key = { frame,Vector3(f1,f2,f3),Vector3(f4,f5,f6),Vector3(1.0f,1.0f,1.0f) };

		m_Motion[name].MotionList[partnum].push_back(key);
		m_Motion[name].CanbeBreak = canbebreak;
		sort(m_Motion[name].MotionList[partnum].begin(), m_Motion[name].MotionList[partnum].end());
	} while (str != "[End]");
}

void Boss::ChangeMotion(string motionname)
{
	if (m_Motion[m_PlayingMotion].CanbeBreak)
	{
		if (m_PlayingMotion == motionname)
			return;
	}
	else
	{
		if (m_PlayingMotion == motionname || !m_EndofMotion)
			return;
	}

	m_PlayingMotion = motionname;
	auto itr = m_Motion.find(motionname);
	if (itr != m_Motion.end()) {
		m_Timer = 0;
		for (int i = 0; i < 7; i++)
		{
			pPart[i]->SetKeyList(itr->second.MotionList[i]);
		}
	}
	else
	{
		return;
	}
}

void Boss::MotionUpdate()
{
}

void Boss::UpdateShaderVariable(LPD3DXEFFECT pEffect)
{
	D3DXVECTOR3 PointLightPos[4] = { m_Light[0].GetTra() ,m_Light[1].GetTra() ,m_Light[2].GetTra() ,m_Light[3].GetTra() };
	pEffect->SetValue("PointLightW", (D3DXVECTOR3*)&PointLightPos[0], sizeof(D3DXVECTOR3) * 4);

	D3DXVECTOR3 PointLightColor[4] = { m_Light[0].GetColor() ,m_Light[1].GetColor() ,m_Light[2].GetColor() ,m_Light[3].GetColor() };
	pEffect->SetValue("PointLightColor", (D3DXVECTOR3*)&PointLightColor[0], sizeof(D3DXVECTOR3) * 4);

	float  PointLightAttenuation[4] = { m_Light[0].GetAttenuation() ,m_Light[1].GetAttenuation() ,m_Light[2].GetAttenuation() ,m_Light[3].GetAttenuation() };
	pEffect->SetValue("PointLightAttenuation", &PointLightAttenuation[0], sizeof(float) * 4);
}

void Boss::TimeUpdate(int limit)
{
	m_Timer++;
	if (m_Timer > limit)
	{
		m_Timer = 0;
		m_EndofMotion = true;
	}
	else
	{
		m_EndofMotion = false;
	}
}

void Boss::SetModelTimer(int time)
{
	pPart[0]->SetTimer(m_Timer);
	pPart[1]->SetTimer(m_Timer);
	pPart[2]->SetTimer(m_Timer);
	pPart[3]->SetTimer(m_Timer);
	pPart[4]->SetTimer(m_Timer);
	pPart[5]->SetTimer(m_Timer);
	pPart[6]->SetTimer(m_Timer);
}
