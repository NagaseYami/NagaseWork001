#include "main.h"
#include "texture.h"
#include "renderer.h"
#include "object.h"
#include "object2dpolygon.h"
#include "blur.h"

LPDIRECT3DVERTEXBUFFER9 Blur::m_pVtxBuff = NULL;
LPDIRECT3DTEXTURE9 Blur::m_Texture = NULL;
LPDIRECT3DSURFACE9 Blur::m_Surface = NULL;
Vector2 Blur::m_Size = Vector2(SCREEN_WIDTH + 3, SCREEN_HEIGHT + 3);
float Blur::m_Alpha = 0.99f;

void Blur::Init()
{	
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	Texture::CreateEmptyTexture("Screen", Vector2(SCREEN_WIDTH, SCREEN_HEIGHT));
	D3DXCreateTexture(pDevice, SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_Texture);
	m_Texture->GetSurfaceLevel(0, &m_Surface);

	//頂点作成*******************************************************************************

	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,	//作成したい頂点バッファのサイズ（一個のサイズ*頂点数）
		D3DUSAGE_WRITEONLY,				//VertexBufferの使用方法
		FVF_VERTEX_2D,					//書かなくても大丈夫
		D3DPOOL_MANAGED,				//メモリ管理方法(デバイスにお任せ)
		&m_pVtxBuff,
		NULL
	))) {
		MessageBox(NULL, "頂点バッファの生成に問題が発生しました", "ERROR from object2dpolygon.cpp", MB_OK | MB_ICONWARNING);
	}

	// ポリゴンの位置を設定**************************************************************************************
	VERTEX_2D* pVtx;

	//頂点バッファをロックして仮想アドレスを取得する
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//左上
	pVtx[0].pos = Vector3(SCREEN_WIDTH / 2 - m_Size.x / 2, SCREEN_HEIGHT / 2 - m_Size.y / 2, 0.0f);
	pVtx[1].pos = Vector3(SCREEN_WIDTH / 2 + m_Size.x / 2, SCREEN_HEIGHT / 2 - m_Size.y / 2, 0.0f);
	pVtx[2].pos = Vector3(SCREEN_WIDTH / 2 - m_Size.x / 2, SCREEN_HEIGHT / 2 + m_Size.y / 2, 0.0f);
	pVtx[3].pos = Vector3(SCREEN_WIDTH / 2 + m_Size.x / 2, SCREEN_HEIGHT / 2 + m_Size.y / 2, 0.0f);

	//rhwの設定(必ず1.0f)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定(0~255の整数値)
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, int(255.0f * m_Alpha));
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, int(255.0f * m_Alpha));
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, int(255.0f * m_Alpha));
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, int(255.0f * m_Alpha));

	//頂点データへUVデータの追加
	pVtx[0].tex = Vector2(0.0f, 0.0f);
	pVtx[1].tex = Vector2(1.0f, 0.0f);
	pVtx[2].tex = Vector2(0.0f, 1.0f);
	pVtx[3].tex = Vector2(1.0f, 1.0f);

	//ロック解除
	m_pVtxBuff->Unlock();
}

void Blur::Uninit()
{
	if (m_pVtxBuff)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_Texture)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}
	if (m_Surface)
	{
		m_Surface->Release();
		m_Surface = NULL;
	}	
}

void Blur::DrawRenderTargetTexture()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	pDevice->SetRenderTarget(0,Texture::GetTexture("Screen")->GetDXSurface());
	pDevice->BeginScene();


	//テクスチャの設定
	pDevice->SetTexture(0, m_Texture);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	pDevice->EndScene();
}

void Blur::ChangeTexture()
{
	LPDIRECT3DTEXTURE9 tex;
	LPDIRECT3DSURFACE9 sur;
	sur = m_Surface;
	tex = m_Texture;
	m_Texture = Texture::GetTexture("Screen")->GetDXTexture();
	m_Surface = Texture::GetTexture("Screen")->GetDXSurface();
	Texture::GetTexture("Screen")->SetDXTexture(tex);
	Texture::GetTexture("Screen")->SetDXSurface(sur);
}