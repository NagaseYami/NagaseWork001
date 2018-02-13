#pragma once
#include "../Main/main.h"
class Blur {
public:
	static void Init();
	static void Uninit();
	static void DrawRenderTargetTexture();
	static void ChangeTexture();
private:
	static LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_Texture;
	static LPDIRECT3DSURFACE9 m_Surface;
	static Vector2 m_Size;
	static float m_Alpha;
};