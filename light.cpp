#include "main.h"
#include "renderer.h"
#include "light.h"

Light * Light::m_Manager[10] = { nullptr };

int Light::CreateLight(D3DLIGHT9 dxlight, int number)
{
	auto pDevice = Renderer::GetDevice();
	if (number == 99)
	{
		for (int i = 0; i < 10; i++)
		{
			if (m_Manager[i] == nullptr)
			{
				m_Manager[i] = new Light();
				m_Manager[i]->m_ID = i;
				m_Manager[i]->m_LightDX = dxlight;
				pDevice->SetLight(i, &dxlight);
				pDevice->LightEnable(i, true);
				return i;
			}
		}
	}
	else
	{
		Light::ReleaseLight(number);
		m_Manager[number] = new Light();
		m_Manager[number]->m_ID = number;
		m_Manager[number]->m_LightDX = dxlight;
		pDevice->SetLight(number, &dxlight);
		pDevice->LightEnable(number, true);
		return number;

	}
}

void Light::ReleaseLight(int number)
{
	auto pDevice = Renderer::GetDevice();
	if (m_Manager[number])
	{
		pDevice->LightEnable(number, false);
		delete m_Manager[number];
		m_Manager[number] = nullptr;
	}
}
