#include "main.h"
#include "dxinput.h"
#include "renderer.h"
#include "camera.h"
#include "tpscamera.h"
#include "player.h"

void TPSCamera::Update()
{
	
	static float length = 30.0f;
	static float lengthmovespeed = 0.0f;

	D3DXMatrixIdentity(&m_MtxView);
	if (Input::IsPress(Input::MouseButtonRight) || Input::IsPress(Input::MouseButtonLeft))
	{
		xz -= (float)DXInput::GetMouseState()->lX / 100.0f;
		yz += (float)DXInput::GetMouseState()->lY / 100.0f;
	}
	if (DXInput::GetMouseState()->lZ != 0)
	{
		lengthmovespeed = 0.001f * (float)DXInput::GetMouseState()->lZ;
	}
	length += lengthmovespeed;
	lengthmovespeed *= 0.9f;

	//length check
	if (length < 1.0f)
	{
		length = 1.0f;
	}
	else if (length > 50.0f)
	{
		length = 50.0f;
	}

	//angle check
	if (yz >= D3DX_PI / 2)
	{
		yz = D3DX_PI / 2 - 0.01f;
	}
	if (yz <= -D3DX_PI / 2)
	{
		yz = -D3DX_PI / 2 + 0.01f;
	}
	
	m_Lookat = Player::GetTra();
	m_Eye.x = length*cosf(yz)*cosf(xz) + m_Lookat.x;
	m_Eye.z = length*cosf(yz)*sinf(xz) + m_Lookat.z;
	m_Eye.y = length*sinf(yz) + m_Lookat.y;	
	if (m_Eye.y <= 0.1f)
	{
		m_Eye.y = 0.1f;
	}
}
