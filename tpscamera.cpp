#include "main.h"
#include "dxinput.h"
#include "renderer.h"
#include "camera.h"
#include "tpscamera.h"

void TPSCamera::Update()
{
	
	static float length = 3.0f;
	static float lengthmovespeed = 0.0f;

	D3DXMatrixIdentity(&m_MtxView);
	if (Input::IsPress(Input::MouseButtonRight))
	{
		xz -= (float)DXInput::GetMouseState()->lX / 100.0f;
		yz += (float)DXInput::GetMouseState()->lY / 100.0f;
	}
	if (DXInput::GetMouseState()->lZ != 0)
	{
		lengthmovespeed = 0.003f * (float)DXInput::GetMouseState()->lZ;
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

	m_Lookat = Vector3(0.0f, 0.0f, 0.0f);
	m_Eye.x = length*cosf(yz)*cosf(xz) + m_Lookat.x;
	m_Eye.z = length*cosf(yz)*sinf(xz) + m_Lookat.z;
	m_Eye.y = length*sinf(yz) + m_Lookat.y;	
}
