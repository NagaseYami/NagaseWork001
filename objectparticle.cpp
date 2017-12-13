#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "effect.h"
#include "object.h"
#include "objectparticle.h"

float ObjectParticle::m_Timer = 0.0f;

void ObjectParticle::Init()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();	

	//頂点バッファ作成******************************************************************************************************
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_POINT)*m_Pos.size(), 
		D3DUSAGE_WRITEONLY|D3DUSAGE_POINTS, 
		NULL,
		D3DPOOL_MANAGED,
		&m_pVtxBuff, 
		NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成に問題が発生しました", "ObjectParticle::Init", MB_OK | MB_ICONWARNING);
		return;
	}	

	D3DVERTEXELEMENT9 elements[] = {
		//{パイプライン番号,オフセット,わからん,用途,わからん}
		{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0 },
		{ 0,12,D3DDECLTYPE_D3DCOLOR,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0 },
		{ 0,16,D3DDECLTYPE_FLOAT1,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_PSIZE,0 },
		{ 0,20,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,1 },
		D3DDECL_END()
	};

	pDevice->CreateVertexDeclaration(elements,&m_pVertexDeclaration);	
	
	for (int i = 0; i < m_Dir.size(); i++)
	{
		m_Dir[i] = Vector3(float(rand() % 1000)*0.001f - 0.5f, float(rand() % 1000)*0.001f - 0.5f, float(rand() % 1000)*0.001f - 0.5f).Normalize();
		m_Color[i] = Vector4(float(rand() % 255), float(rand() % 255), float(rand() % 255), 255);
	}	

	VERTEX_POINT* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int i = 0; i < m_Pos.size(); i++)
	{
		pVtx[i].pos = Vector3(m_Pos[i].x, m_Pos[i].y, m_Pos[i].z);
		pVtx[i].color = D3DCOLOR_ARGB((int)m_Color[i].w, (int)m_Color[i].x, (int)m_Color[i].y, (int)m_Color[i].z);
		pVtx[i].size = 1.0f;
		pVtx[i].dir = m_Dir[i];
	}
	m_pVtxBuff->Unlock();
}

void ObjectParticle::Uninit()
{
	m_TextureList.clear();
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pVertexDeclaration)
	{
		m_pVertexDeclaration->Release();
		m_pVertexDeclaration = NULL;
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
	m_Timer= 1.0f;	
	
}

void ObjectParticle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	D3DXMatrixIdentity(&m_mtxWorld);
	
	//テクスチャ
	if (m_TextureList.size() > 0)
	{
		pDevice->SetTexture(0, m_TextureList[m_TexNum]->GetDXTexture());
	}
	else
	{
		pDevice->SetTexture(0, NULL);
	}

	pDevice->SetVertexDeclaration(m_pVertexDeclaration);

	//パイプラインの設定
	pDevice->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_POINT));

	//加算合成
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// ポイントスケールの設定
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	// ポイントスプライト有効化
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, (DWORD)0.0f);
	//ライトオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//Zバッファへの書き込み禁止
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//Colorの書き込みを許可
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);

	LPD3DXEFFECT pEffect = Effect::LoadEffectFromFile("data/Shader/ParticleShader.fx");

	for (int i = 0; i < m_TextureList.size(); i++)
	{
		if (m_TextureList[i]->GetDXTexture() != NULL)
		{
			pEffect->SetTechnique("BasicShader_TexterTech");
			break;
		}
		else
		{
			pEffect->SetTechnique("BasicShader_NoTexterTech");
		}
	}

	UINT numPass;
	pEffect->Begin(&numPass, 0);

	D3DXMATRIX proj, view, WVP;
	pDevice->GetTransform(D3DTS_PROJECTION, &proj);
	pDevice->GetTransform(D3DTS_VIEW, &view);
	WVP = m_mtxWorld*view*proj;

	for (UINT iPass = 0; iPass < numPass; iPass++)
	{
		pEffect->BeginPass(iPass);
		pEffect->SetMatrix("WorldViewProj", &WVP);
		pEffect->SetFloat("Time", m_Timer);
		pEffect->SetTexture("Tex", NULL);
		pEffect->CommitChanges();
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_POINTLIST,
			0,
			m_Pos.size());
		pEffect->EndPass();
	}
	pEffect->End();

	
	
	// レンダリングステートの設定を元に戻す
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ポイントスケールの設定
	//pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	// ポイントスプライト有効化
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
}

//縮小バッファ法