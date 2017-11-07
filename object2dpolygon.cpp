#include "main.h"
#include "renderer.h"
#include "object.h"
#include "object2dpolygon.h"

void Object2DPolygon::Init()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

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
}

void Object2DPolygon::Uninit()
{
	m_pTexture = NULL;
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

void Object2DPolygon::FixedUpdate()
{
}

void Object2DPolygon::Update()
{
}

void Object2DPolygon::LateUpdate()
{
	// ポリゴンの位置を設定**************************************************************************************
	VERTEX_2D* pVtx;

	//頂点バッファをロックして仮想アドレスを取得する
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//左上
	pVtx[0].pos = Vector3(m_Pos.x, m_Pos.y, 0.0f);
	pVtx[1].pos = Vector3(m_Pos.x + m_Size.x, m_Pos.y, 0.0f);
	pVtx[2].pos = Vector3(m_Pos.x, m_Pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = Vector3(m_Pos.x + m_Size.x, m_Pos.y + m_Size.y, 0.0f);

	//rhwの設定(必ず1.0f)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定(0~255の整数値)
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点データへUVデータの追加
	pVtx[0].tex = Vector2(0.0f, 0.0f);
	pVtx[1].tex = Vector2(1.0f, 0.0f);
	pVtx[2].tex = Vector2(0.0f, 1.0f);
	pVtx[3].tex = Vector2(1.0f, 1.0f);

	//ロック解除
	m_pVtxBuff->Unlock();
}

void Object2DPolygon::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

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
}
