#include "main.h"
#include "renderer.h"
#include "object.h"
#include "texture.h"

map<string, Texture*> Texture::m_Manager;

Texture::Texture()
{
	m_RenderTargetObj.clear();
}

Texture * Texture::LoadTextureFromFile(LPCSTR fileName)
{
	LPDIRECT3DTEXTURE9 pTex;
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	string name = fileName;

	auto itr = m_Manager.find(name);
	if (itr != m_Manager.end()) {
		return itr->second;
	}
	else {
		if (FAILED(
			D3DXCreateTextureFromFile(pDevice, fileName, &pTex)
		))
		{
			MessageBox(NULL, "ファイルからテクスチャを読み込むことができませんでした。", "ERROR from texture.cpp", MB_OK | MB_DEFBUTTON1);
			return nullptr;
		}
		m_Manager[name] = new Texture;
		m_Manager[name]->m_Texture = pTex;
		m_Manager[name]->m_RenderTargetObj.clear();
		return m_Manager[name];
	}
	
}

Texture * Texture::CreateEmptyTexture(string name, Vector2 size, bool COLORWRITEENABLE)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	Texture * Tex = new Texture;
	D3DXCreateTexture(pDevice, (UINT)size.x, (UINT)size.y, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &Tex->m_Texture);
	Tex->m_Texture->GetSurfaceLevel(0, &Tex->m_Surface);
	Tex->isRenderTargetTexture = true;
	Tex->ColorWriteEnable = COLORWRITEENABLE;
	m_Manager[name] = Tex;
	return m_Manager[name];
}

void Texture::AddObjectToRenderTargetTexture(Object *obj, string name)
{
	auto itr = m_Manager.find(name);
	if (itr != m_Manager.end())
	{
		itr->second->m_RenderTargetObj.push_back(obj);
		obj->SetRenderTarget(true);
	}
	else
	{
		MessageBox(NULL, "指定された名前のテクスチャはありません。", "ERROR from texture.cpp", MB_OK | MB_DEFBUTTON1);
	}
}

void Texture::DrawAllRenderTargetTexture()
{
	for (auto itr = m_Manager.begin(); itr != m_Manager.end(); itr++)
	{
		if (itr->second->isRenderTargetTexture)
		{
			DrawRenderTargetTextureRecursion(itr->second);
		}
	}
}

void Texture::DestoryAllTexture()
{
	for (auto itr = m_Manager.begin(); itr != m_Manager.end(); itr++)
	{
		if (itr->second->m_Texture)
		{
			itr->second->m_Texture->Release();
			itr->second->m_Texture = NULL;
		}

		if (itr->second->m_Surface)
		{
			itr->second->m_Surface->Release();
			itr->second->m_Surface = NULL;
		}
		itr->second->m_RenderTargetObj.clear();
		delete itr->second;
	}
	m_Manager.clear();
}

Texture * Texture::GetTexture(string name)
{
	auto itr = m_Manager.find(name);
	if (itr != m_Manager.end())
	{
		return itr->second;
	}
	else 
	{
		MessageBox(NULL, "テクスチャライブラリから取得できませんでした。", "ERROR from texture.cpp", MB_OK | MB_DEFBUTTON1);
		return nullptr;
	}
	
}

void Texture::DrawRenderTargetTextureRecursion(Texture * tex)
{
	auto pDevice = Renderer::GetDevice();
	//RenderTargetObj
	for (auto itr = tex->m_RenderTargetObj.begin(); itr != tex->m_RenderTargetObj.end(); itr++)
	{
		Object * obj = *itr;

		if (!obj->isDestory())
		{
			//RenderTargetObj's tex
			for (auto i = 0; i < obj->GetTexture().size(); i++)
			{
				//RenderTargetTexture
				if (obj->GetTexture().at(i)->isRenderTargetTexture)
				{
					DrawRenderTargetTextureRecursion(obj->GetTexture().at(i));
				}
			}
		}
		else
		{
			tex->m_RenderTargetObj.erase(itr);
		}
	}
	Renderer::DrawRenderTargetBegin(tex->m_Surface);
	for (auto itr = tex->m_RenderTargetObj.begin(); itr != tex->m_RenderTargetObj.end(); itr++)
	{
		Object * obj = *itr;

		if (!tex->ColorWriteEnable)
		{
			pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
		}
		
		if (!obj->isDestory())
		{
			obj->Draw();
		}	
		else
		{
			tex->m_RenderTargetObj.erase(itr);
		}

		pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
	}
	Renderer::DrawRenderTargetEnd();
}
