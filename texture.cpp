#include "main.h"
#include "renderer.h"
#include "object.h"
#include "texture.h"
#include "camera.h"

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

Texture * Texture::CreateEmptyTexture(string name, Vector2 size, TEXTURE_TYPE type, D3DFORMAT format, D3DPOOL memory, bool COLORWRITEENABLE)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	Texture * Tex = new Texture;
	if (type == DYNAMIC)
	{
		pDevice->CreateTexture((UINT)size.x, (UINT)size.y, 1, D3DUSAGE_DYNAMIC, format, memory, &Tex->m_Texture, NULL);
	}
	else
	{
		D3DXCreateTexture(pDevice, (UINT)size.x, (UINT)size.y, 1, D3DUSAGE_RENDERTARGET, format, memory, &Tex->m_Texture);
	}	
	Tex->m_Texture->GetSurfaceLevel(0, &Tex->m_Surface);
	Tex->m_Type = type;
	Tex->m_ColorWriteEnable = COLORWRITEENABLE;
	if (type == SHADOWMAP)
	{
		if (FAILED(pDevice->CreateDepthStencilSurface((UINT)size.x, (UINT)size.y, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, TRUE, &Tex->m_DepthSurface, NULL)))
		{
			MessageBox(NULL, "CreateDepthStencilSurfaceが失敗しました。", "ERROR from texture.cpp", MB_OK | MB_DEFBUTTON1);
		}
	}
	else
	{
		Tex->m_DepthSurface = Renderer::GetBackDepthSurface();
	}
	m_Manager[name] = Tex;
	return m_Manager[name];
}

void Texture::AddObjectToRenderTargetTexture(Object *obj, string name)
{
	auto itr = m_Manager.find(name);
	if (itr != m_Manager.end())
	{
		itr->second->m_RenderTargetObj.push_back(obj);
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
		if (itr->second->m_Type == RENDERTARGET ||
			itr->second->m_Type == SHADOWMAP 
			)
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
			for (unsigned int i = 0; i < obj->GetTexture().size(); i++)
			{
				//RenderTargetTexture
				if (obj->GetTexture().at(i)->m_Type != NORMAL)
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

	pDevice->SetRenderTarget(0, tex->m_Surface);
	pDevice->SetDepthStencilSurface(tex->m_DepthSurface);
	Renderer::DrawRenderTargetBegin();	

	for (auto itr = tex->m_RenderTargetObj.begin(); itr != tex->m_RenderTargetObj.end(); itr++)
	{
		Object * obj = *itr;

		if (!tex->m_ColorWriteEnable)
		{
			pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);
		}
				
		D3DXMATRIX Old_MtxView;
		pDevice->GetTransform(D3DTS_VIEW, &Old_MtxView);
		D3DVIEWPORT9 Old_vp;
		pDevice->GetViewport(&Old_vp);
		LPDIRECT3DSURFACE9 Old_DepthSurface;
		pDevice->GetDepthStencilSurface(&Old_DepthSurface);

		if (tex->m_Type == SHADOWMAP && !obj->isDestory())
		{
			Camera::SetOrthoMtxProjection();
			Camera::SetShadowCamera();			
			D3DVIEWPORT9 vp{ 0,0,SHADOWMAP_SIZE,SHADOWMAP_SIZE,0.0f,1.0f };
			pDevice->SetViewport(&vp);
			obj->SetShader("data/Shader/BasicShader.fx","ZShadowShader_Tech","ZShadowShader_Tech");
		}
		if (!obj->isDestory())
		{
			obj->Draw();
		}	
		else
		{
			tex->m_RenderTargetObj.erase(itr);
		}

		if (tex->m_Type == SHADOWMAP && !obj->isDestory())
		{
			Camera::SetPerspectiveMtxProjection();
			pDevice->SetTransform(D3DTS_VIEW, &Old_MtxView);
			pDevice->SetViewport(&Old_vp);
			pDevice->SetDepthStencilSurface(Old_DepthSurface);
			obj->SetShader("data/Shader/BasicShader.fx", "BasicShader_TexterTech", "BasicShader_NoTexterTech");
		}

		if (!tex->m_ColorWriteEnable)pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);
	}
	Renderer::DrawRenderTargetEnd();
}
