#include <fstream>
#include "../Camera/camera.h"
#include "../Object/objectXModel.h"
#include "../Texture/texture.h"
#include "player.h"

ObjectXModel * Player::pPart[10];
Vector3 Player::m_Tra = Vector3(0.0f, 5.6f, -90.0f);
Vector3 Player::m_Dir = Vector3(0.0f, 0.0f, 1.0f);
map<string, Player::PlayerMotion> Player::m_Motion;
int Player::m_Timer = 0;
string Player::m_PlayingMotion = "Null";
bool Player::m_EndofMotion = true;

void Player::Init()
{
	XModelInit();
	ParentInit();
	TransformInit();
	MotionInit();
	m_Dir = Vector3(0.0f, 0.0f, 1.0f);
	Vector3RotationAxis(&m_Dir, Vector3(0.0f, 1.0f, 0.0f), -Camera::GetMainCameraxz() - D3DX_PI / 2);
	pPart[0]->SetRFP(Vector3(0.0f, -Camera::GetMainCameraxz() + D3DX_PI / 2, 0.0f));
}

void Player::Update()
{
	ControllerUpdate();
	MotionUpdate();	
	SetModelTimer(m_Timer);
	TimeUpdate(m_Motion[m_PlayingMotion].MotionList[0].at(m_Motion[m_PlayingMotion].MotionList[0].size() - 1).Frame);
}

void Player::XModelInit()
{
	pPart[0] = new ObjectXModel("data/Model/Player/Body.x");
	pPart[1] = new ObjectXModel("data/Model/Player/Head.x");

	for (int i = 0; i < 8; i++)
	{
		pPart[2 + i] = new ObjectXModel("data/Model/Player/AHLF.x");
	}

	for (int i = 0; i < 10; i++)
	{
		pPart[i]->Init();
		Texture::AddObjectToRenderTargetTexture(pPart[i], "ShadowMap");
	}
}

void Player::ParentInit()
{
	pPart[1]->SetParent(pPart[0]);
	pPart[2]->SetParent(pPart[0]);
	pPart[3]->SetParent(pPart[2]);
	pPart[4]->SetParent(pPart[0]);
	pPart[5]->SetParent(pPart[4]);
	pPart[6]->SetParent(pPart[0]);
	pPart[7]->SetParent(pPart[6]);
	pPart[8]->SetParent(pPart[0]);
	pPart[9]->SetParent(pPart[8]);
}

void Player::TransformInit()
{
	pPart[0]->SetTFP(m_Tra);
	pPart[1]->SetTFP(Vector3(0.0f, 2.0f, 0.0f));
	pPart[2]->SetTFP(Vector3(-1.5f, 1.6f, 0.0f));
	pPart[3]->SetTFP(Vector3(0.0f, -1.9f, 0.0f));
	pPart[4]->SetTFP(Vector3(1.5f, 1.6f, 0.0f)); 
	pPart[5]->SetTFP(Vector3(0.0f, -1.9f, 0.0f));
	pPart[6]->SetTFP(Vector3(-0.5f, -2.4f, 0.0f));
	pPart[7]->SetTFP(Vector3(0.0f, -1.9f, 0.0f));
	pPart[8]->SetTFP(Vector3(0.5f, -2.4f, 0.0f));
	pPart[9]->SetTFP(Vector3(0.0f, -1.9f, 0.0f));
}

void Player::MotionInit()
{
	LoadMotionFromFile("data/Model/Player/Forward.txt",true);
	LoadMotionFromFile("data/Model/Player/ForwardRight.txt", true);
	LoadMotionFromFile("data/Model/Player/ForwardLeft.txt", true);
	LoadMotionFromFile("data/Model/Player/Left.txt", true);
	LoadMotionFromFile("data/Model/Player/Right.txt", true);
	LoadMotionFromFile("data/Model/Player/Back.txt", true);
	LoadMotionFromFile("data/Model/Player/BackLeft.txt", true);
	LoadMotionFromFile("data/Model/Player/BackRight.txt", true);
	LoadMotionFromFile("data/Model/Player/Jump.txt",false);
	LoadMotionFromFile("data/Model/Player/JumpRight.txt", false);
	LoadMotionFromFile("data/Model/Player/JumpLeft.txt", false);
	LoadMotionFromFile("data/Model/Player/JumpBack.txt", false);
	LoadMotionFromFile("data/Model/Player/Neutral.txt",true);
	LoadMotionFromFile("data/Model/Player/Attack1.txt", false);
	LoadMotionFromFile("data/Model/Player/Rotate.txt", true);
	ChangeMotion("Neutral");
}

void Player::LoadMotionFromFile(string filename ,bool canbebreak)
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

void Player::ChangeMotion(string motionname)
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
		for (int i = 0; i < 10; i++)
		{
			pPart[i]->SetKeyList(itr->second.MotionList[i]);
		}		
	}
	else
	{
		return;
	}
}

void Player::ControllerUpdate()
{
	if (m_PlayingMotion != "Attack1")
	{
		if (Input::IsPress(Input::KeyW))
		{
			m_Tra += m_Dir.Normalize() / 3.0f;
		}
		else if (Input::IsPress(Input::KeyS))
		{
			m_Tra -= m_Dir.Normalize() / 10.0f;
		}

		if (Input::IsPress(Input::KeyD))
		{
			if (Input::IsPress(Input::MouseButtonRight))
			{
				Vector3 right;
				Vector3Cross(&right, &m_Dir, &Vector3::down);
				m_Tra += right.Normalize() / 3.0f;
			}
			else
			{
				Vector3RotationAxis(&m_Dir, Vector3::up, D3DX_PI / 120.0f);
				m_Dir.y = 0.0f;
				m_Dir = m_Dir.Normalize();
				float angle = AngleBetween2Vector3(m_Dir, Vector3::forward) - D3DX_PI;
				if (Vector3LeftorRight(m_Dir, Vector3::forward))
				{
					if (!Input::IsPress(Input::MouseButtonLeft))
					{
						Camera::SetmainCameraxz(-angle + D3DX_PI / 2);
					}
					pPart[0]->SetRFP(Vector3(0.0f, angle, 0.0f));
				}
				else
				{
					if (!Input::IsPress(Input::MouseButtonLeft))
					{
						Camera::SetmainCameraxz(angle + D3DX_PI / 2);
					}
					pPart[0]->SetRFP(Vector3(0.0f, -angle, 0.0f));
				}
			}
		}
		else if (Input::IsPress(Input::KeyA))
		{
			if (Input::IsPress(Input::MouseButtonRight))
			{
				Vector3 left;
				Vector3Cross(&left, &m_Dir, &Vector3::up);
				m_Tra += left.Normalize() / 3.0f;
			}
			else
			{
				Vector3RotationAxis(&m_Dir, Vector3::up, -D3DX_PI / 120.0f);
				m_Dir.y = 0.0f;
				m_Dir = m_Dir.Normalize();
				float angle = AngleBetween2Vector3(m_Dir, Vector3::forward) - D3DX_PI;
				if (Vector3LeftorRight(m_Dir, Vector3::forward))
				{
					if (!Input::IsPress(Input::MouseButtonLeft))
					{
						Camera::SetmainCameraxz(-angle + D3DX_PI / 2);
					}
					pPart[0]->SetRFP(Vector3(0.0f, angle, 0.0f));
				}
				else
				{
					if (!Input::IsPress(Input::MouseButtonLeft))
					{
						Camera::SetmainCameraxz(angle + D3DX_PI / 2);
					}
					pPart[0]->SetRFP(Vector3(0.0f, -angle, 0.0f));
				}
			}
		}
		if (Input::IsPress(Input::KeyQ))
		{
			Vector3 left;
			Vector3Cross(&left, &m_Dir, &Vector3::up);
			m_Tra += left.Normalize() / 3.0f;
		}
		else if (Input::IsPress(Input::KeyE))
		{
			Vector3 right;
			Vector3Cross(&right, &m_Dir, &Vector3::down);
			m_Tra += right.Normalize() / 3.0f;
		}
	}	
	if (Input::IsPress(Input::MouseButtonRight))
	{
		m_Dir = Vector3(0.0f, 0.0f, 1.0f);
		Vector3RotationAxis(&m_Dir, Vector3(0.0f, 1.0f, 0.0f), -Camera::GetMainCameraxz() - D3DX_PI / 2.0f);
		pPart[0]->SetRFP(Vector3(0.0f, -Camera::GetMainCameraxz() + D3DX_PI / 2.0f, 0.0f));
	}
	pPart[0]->SetTFP(m_Tra);
}

void Player::MotionUpdate()
{
	if (Input::IsDown(Input::Key1))
	{
		ChangeMotion("Attack1");
	}
	else if (Input::IsPress(Input::KeySpace))
	{
		if (Input::IsPress(Input::KeyA))
		{
			ChangeMotion("JumpLeft");
		}
		else if (Input::IsPress(Input::KeyD))
		{
			ChangeMotion("JumpRight");
		}
		else if (Input::IsPress(Input::KeyS))
		{
			ChangeMotion("JumpBack");
		}
		else
		{
			ChangeMotion("Jump");
		}
	}
	else if (Input::IsPress(Input::KeyW))
	{
		if (Input::IsPress(Input::KeyA) && Input::IsPress(Input::MouseButtonRight))
		{
			ChangeMotion("ForwardLeft");
		}
		else if (Input::IsPress(Input::KeyD) && Input::IsPress(Input::MouseButtonRight))
		{
			ChangeMotion("ForwardRight");
		}
		else if (Input::IsPress(Input::KeyQ))
		{
			ChangeMotion("ForwardLeft");
		}
		else if (Input::IsPress(Input::KeyE))
		{
			ChangeMotion("ForwardRight");
		}
		else
		{
			ChangeMotion("Forward");
		}
				
	}	
	else if (Input::IsPress(Input::KeyS))
	{
		if (Input::IsPress(Input::KeyA) && Input::IsPress(Input::MouseButtonRight))
		{
			ChangeMotion("BackLeft");
		}
		else if (Input::IsPress(Input::KeyD) && Input::IsPress(Input::MouseButtonRight))
		{
			ChangeMotion("BackRight");
		}
		else if (Input::IsPress(Input::KeyQ))
		{
			ChangeMotion("BackLeft");
		}
		else if (Input::IsPress(Input::KeyE))
		{
			ChangeMotion("BackRight");
		}
		else
		{
			ChangeMotion("Back");
		}
	}
	else if (Input::IsPress(Input::KeyQ))
	{
		ChangeMotion("Left");	
	}
	else if (Input::IsPress(Input::KeyE))
	{
		ChangeMotion("Right");
	}
	else if (Input::IsPress(Input::MouseButtonRight)&& Input::IsPress(Input::KeyA))
	{
		ChangeMotion("Left");
	}
	else if (Input::IsPress(Input::MouseButtonRight) && Input::IsPress(Input::KeyD))
	{
		ChangeMotion("Right");
	}
	else if (Input::IsPress(Input::KeyA) || Input::IsPress(Input::KeyD))
	{
		ChangeMotion("Rotate");
	}
	else
	{
		ChangeMotion("Neutral");
	}	
}

void Player::TimeUpdate(int limit)
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

void Player::SetModelTimer(int time)
{
	pPart[0]->SetTimer(m_Timer);
	pPart[1]->SetTimer(m_Timer);
	pPart[2]->SetTimer(m_Timer);
	pPart[3]->SetTimer(m_Timer);
	pPart[4]->SetTimer(m_Timer);
	pPart[5]->SetTimer(m_Timer);
	pPart[6]->SetTimer(m_Timer);
	pPart[7]->SetTimer(m_Timer);
	pPart[8]->SetTimer(m_Timer);
	pPart[9]->SetTimer(m_Timer);
}