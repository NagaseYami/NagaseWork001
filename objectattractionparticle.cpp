#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "effect.h"
#include "objectattractionparticle.h"

void ObjectAttractionParticle::Init()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//頂点バッファ作成******************************************************************************************************
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_POINT)*m_Pos.size(), 
		D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS,
		NULL,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成に問題が発生しました", "ObjectAttractionParticle::Init", MB_OK | MB_ICONWARNING);
		return;
	}

	D3DVERTEXELEMENT9 elements[] = {
		{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0 },
		{ 0,12,D3DDECLTYPE_D3DCOLOR,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0 },
		{ 0,16,D3DDECLTYPE_FLOAT1,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_PSIZE,0 },
		{ 0,20,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,1 },
		{ 0,32,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,2 },
		D3DDECL_END()
	};

	pDevice->CreateVertexDeclaration(elements, &m_pVertexDeclaration);

	for (unsigned int i = 0; i < m_Pos.size(); i++)
	{
		m_Pos[i] = Vector3(float(rand() % 100), float(rand() % 100), float(rand() % 100));
		m_Speed[i] = Vector3(0.0f, 0.0f, 0.0f);
		m_Color[i] = Vector4(float(rand() % 255), float(rand() % 255), float(rand() % 255), 255);
	}

	for (unsigned int i = 0; i < 1000; i++)
	{
		for (unsigned int o = 0; o < 100; o++)
		{
			m_InfoUV[i * 100 + o].x = (float)i / 1024.0f;
			m_InfoUV[i * 100 + o].y = (float)o / 1024.0f;
		}		
	}

	VERTEX_POINT* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (unsigned int i = 0; i < m_Pos.size(); i++)
	{
		pVtx[i].pos = m_Pos[i];
		pVtx[i].color = D3DCOLOR_ARGB((int)m_Color[i].w, (int)m_Color[i].x, (int)m_Color[i].y, (int)m_Color[i].z);
		pVtx[i].size = 1.0f;
		pVtx[i].speed = m_Speed[i];
		pVtx[i].InfoUV = m_InfoUV[i];
	}
	m_pVtxBuff->Unlock();

	//InfoTexture
	for (int i = 0; i < 4; i++)
	{
		D3DXCreateTexture(pDevice, (UINT)1024, (UINT)1024, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_InfoTexture[i]);
		m_InfoTexture[i]->GetSurfaceLevel(0, &m_Surface[i]);
	}
}

void ObjectAttractionParticle::Uninit()
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

void ObjectAttractionParticle::FixedUpdate()
{
}

void ObjectAttractionParticle::Update()
{
}

void ObjectAttractionParticle::LateUpdate()
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
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	//Colorの書き込みを許可
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);

	//LPD3DXEFFECT pEffect = Effect::LoadEffectFromFile("data/Shader/AttractionParticleShader.fx");
	//pEffect->SetTechnique("AttractionShader");

	//UINT numPass;
	//pEffect->Begin(&numPass, 0);

	//D3DXMATRIX proj, view, VP;
	//pDevice->GetTransform(D3DTS_PROJECTION, &proj);
	//pDevice->GetTransform(D3DTS_VIEW, &view);
	//VP = view*proj;

	//pDevice->SetRenderTarget(0, m_Surface[2]);
	//pDevice->SetRenderTarget(1, m_Surface[3]);

	//Renderer::DrawRenderTargetBegin();

	//
	//pEffect->BeginPass(0);
	//pEffect->SetMatrix("World", &m_mtxWorld);
	//pEffect->SetMatrix("ViewProj", &VP);
	//pEffect->SetTexture("PosInput", m_InfoTexture[0]);
	//pEffect->SetTexture("SpeedInput", m_InfoTexture[1]);
	//pEffect->SetTexture("PosOutput", m_InfoTexture[2]);
	//pEffect->SetTexture("SpeedOutput", m_InfoTexture[3]);
	//pEffect->SetTexture("Tex", NULL);
	//pEffect->CommitChanges();
	////ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_POINTLIST,
	//	0,
	//	m_Pos.size());
	//pEffect->EndPass();

	//Renderer::DrawRenderTargetEnd();

	//pDevice->SetRenderTarget(0, Renderer::GetBackBufferSurface());
	//pDevice->SetRenderTarget(1, NULL);

	//Renderer::DrawRenderTargetBegin();


	//pEffect->BeginPass(1);
	//pEffect->SetMatrix("World", &m_mtxWorld);
	//pEffect->SetMatrix("ViewProj", &VP);
	//pEffect->SetTexture("PosInput", m_InfoTexture[0]);
	//pEffect->SetTexture("SpeedInput", m_InfoTexture[1]);
	//pEffect->SetTexture("PosOutput", m_InfoTexture[2]);
	//pEffect->SetTexture("SpeedOutput", m_InfoTexture[3]);
	//pEffect->SetTexture("Tex", NULL);
	//pEffect->CommitChanges();
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_POINTLIST,
		0,
		m_Pos.size());
	//pEffect->EndPass();

	//pEffect->End();

	Renderer::DrawRenderTargetEnd();

	// レンダリングステートの設定を元に戻す
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);

	
}

void ObjectAttractionParticle::Draw()
{
	LPDIRECT3DTEXTURE9 tex;
	LPDIRECT3DSURFACE9 sur;

	sur = m_Surface[0];
	tex = m_InfoTexture[0];

	m_Surface[0] = m_Surface[2];
	m_InfoTexture[0] = m_InfoTexture[2];

	m_Surface[2] = sur;
	m_InfoTexture[2] = tex;

	sur = m_Surface[1];
	tex = m_InfoTexture[1];

	m_Surface[1] = m_Surface[3];
	m_InfoTexture[1] = m_InfoTexture[3];

	m_Surface[3] = sur;
	m_InfoTexture[3] = tex;
}