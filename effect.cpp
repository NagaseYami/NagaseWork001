#include "main.h"
#include "renderer.h"
#include "effect.h"

map<string, LPD3DXEFFECT> Effect::m_Manager;

LPD3DXEFFECT Effect::LoadEffectFromFile(string filename)
{
	auto itr = m_Manager.find(filename);
	if (itr != m_Manager.end())
	{
		return itr->second;
	}
	auto pDevice = Renderer::GetDevice();
	LPD3DXEFFECT pEffect;
	ID3DXBuffer *	pErrorMsgs;
	auto hr = D3DXCreateEffectFromFile(
		pDevice,
		filename.c_str(),
		NULL,
		NULL,
		0,
		NULL,
		&pEffect,
		&pErrorMsgs);

	if (FAILED(hr))
	{		
		LOG((char*)pErrorMsgs->GetBufferPointer());
		MessageBox(NULL, "エフェクト作成に失敗\n", "D3DXCreateEffectFromFile", MB_OK | MB_ICONWARNING);
	}

	D3DXHANDLE hTech = NULL;
	D3DXHANDLE hTechNext;
	
	do
	{
		hr = pEffect->FindNextValidTechnique(hTech, &hTechNext);
		if (FAILED(hr))
		{
			MessageBox(NULL, "テクニックの列挙に失敗", "LPD3DXEFFECT::FindNextValidTechnique", MB_OK | MB_ICONWARNING);
		}
		if (hTechNext)
		{
			hr = pEffect->ValidateTechnique(hTechNext);
			if (FAILED(hr))
			{
				MessageBox(NULL, "テクニックの妥当性テストに失敗", "LPD3DXEFFECT::ValidateTechnique", MB_OK | MB_ICONWARNING);
			}
		}
		hTech = hTechNext;
	} while (hTech != NULL);

	m_Manager[filename] = pEffect;
	return pEffect;
}
