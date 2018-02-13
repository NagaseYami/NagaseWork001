#include "../Input/dxinput.h"
#include "../Player/player.h"
#include "tpscamera.h"

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

	m_TargetEye.x = length*cosf(yz)*cosf(xz) + m_Lookat.x;
	m_TargetEye.z = length*cosf(yz)*sinf(xz) + m_Lookat.z;
	m_TargetEye.y = length*sinf(yz) + m_Lookat.y;

	if (m_TargetEye.y <= 0.1f)
	{
		m_TargetEye.y = 0.1f;
	}
	//フックの法則	
	x = (m_TargetEye - m_Eye).Length();
	F = x / 100.0f;
	v += F;
	if (x > 2 * v)
	{
		m_Eye += v * (m_TargetEye - m_Eye).Normalize();
	}
	else 
	{
		m_Eye = m_TargetEye;
	}
	v *= 0.98f;
}
