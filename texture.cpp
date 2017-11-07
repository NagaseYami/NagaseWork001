#include "main.h"
#include "renderer.h"
#include "texture.h"

map<string, LPDIRECT3DTEXTURE9> Texture::Manager;

LPDIRECT3DTEXTURE9 Texture::LoadTexture(LPCSTR fileName)
{
	LPDIRECT3DTEXTURE9 pTex;
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	string name = fileName;

	auto itr = Manager.find(name);
	if (itr != Manager.end()) {
		return itr->second;
	}
	else {
		if (FAILED(
			D3DXCreateTextureFromFile(pDevice, fileName, &pTex)
		))
		{
			MessageBox(NULL, "ファイルからテクスチャを読み込むことができませんでした。", "ERROR from texture.cpp", MB_OK | MB_DEFBUTTON1);
			return NULL;
		}
		Manager[name] = pTex;
		return pTex;
	}
	
}

void Texture::DestoryAllTexture()
{
	for (auto itr = Manager.begin(); itr != Manager.end(); itr++)
	{
		if (itr->second)
		{
			itr->second->Release();
			itr->second = NULL;
		}
	}
	Manager.clear();
}

LPDIRECT3DTEXTURE9 Texture::GetTexture(string name)
{
	auto itr = Manager.find(name);
	if (itr != Manager.end())
	{
		return itr->second;
	}
	else 
	{
		MessageBox(NULL, "テクスチャライブラリから取得できませんでした。", "ERROR from texture.cpp", MB_OK | MB_DEFBUTTON1);
		return NULL;
	}
	
}
