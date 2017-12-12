#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "object.h"
#include "objectparticle.h"

void ObjectParticle::Init()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();	

	//頂点バッファ作成******************************************************************************************************
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_POINT)*m_Pos.size(), 
		D3DUSAGE_WRITEONLY, 
		VERTEX_POINT_FVF,
		D3DPOOL_MANAGED, 
		&m_pVtxBuff, 
		NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成に問題が発生しました", "ObjectParticle::Init", MB_OK | MB_ICONWARNING);
		return;
	}	
	
	for (int i = 0; i < m_Dir.size(); i++)
	{
		m_Dir[i] = Vector3(float(rand() % 1000)*0.001f - 0.5f, float(rand() % 1000)*0.001f - 0.5f, float(rand() % 1000)*0.001f).Normalize();
		m_Color[i] = Vector4(float(rand() % 255), float(rand() % 255), float(rand() % 255), 255);
	}
	VERTEX_POINT* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	for (int i = 0; i < m_Pos.size(); i++)
	{
		pVtx[i].pos = Vector3(m_Pos[i].x, m_Pos[i].y, m_Pos[i].z);
		pVtx[i].color = (DWORD)D3DCOLOR_ARGB((int)m_Color[i].w, (int)m_Color[i].x, (int)m_Color[i].y, (int)m_Color[i].z);
		pVtx[i].size = 0.01f;
	}
	m_pVtxBuff->Unlock();

	// ポイントスケールの設定
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	// ポイントスプライト有効化
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, (DWORD)0.0f);
}

void ObjectParticle::Uninit()
{
	m_TextureList.clear();
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

void ObjectParticle::FixedUpdate()
{
	
}

void ObjectParticle::Update()
{

}

void ObjectParticle::LateUpdate()
{
/*
	for (int i = 0; i < m_Pos.size(); i++)
	{
		m_Pos[i] += Vector4(m_Dir[i], 0.0f);
	}*/	
}

void ObjectParticle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	D3DXMatrixIdentity(&m_mtxWorld);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//D3DXMATRIX view, proj,WVP;
	//
	//pDevice->GetTransform(D3DTS_PROJECTION, &proj);
	//pDevice->GetTransform(D3DTS_VIEW, &view);

	//WVP = m_mtxWorld * view * proj;

	////コピー
	//auto copy = m_Pos;

	////Z値計算
	//for (int i = 0; i < copy.size(); ++i)
	//{
	//	auto PosWVP = Vector4(copy[i].xyz(), 1.0f) * WVP;
	//	copy[i].w = PosWVP.z / PosWVP.w;
	//}
	//int abc = 0;
	////降順ソート
	//std::sort(copy.begin(), copy.end(),[](Vector4 const &a, Vector4 const &b) { return a.w > b.w; });

	
	
	

	//FVF
	pDevice->SetFVF(VERTEX_POINT_FVF);

	//テクスチャ
	if (m_TextureList.size() > 0)
	{
		pDevice->SetTexture(0, m_TextureList[m_TexNum]->GetDXTexture());
	}
	else
	{
		pDevice->SetTexture(0, NULL);
	}
	

	//パイプラインの設定
	pDevice->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_POINT));

	//加算合成
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//ライトオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//Zバッファへの書き込み禁止
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//Colorの書き込みを許可
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);

	//ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_POINTLIST,
	//	0,
	//	m_Pos.size());
	//
	// レンダリングステートの設定を元に戻す
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//縮小バッファ法