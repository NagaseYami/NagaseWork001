#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "effect.h"
#include "object2dpolygon.h"
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
		m_InfoTexture[i] = Texture::CreateEmptyTexture("AttractionParticleInfoTexture" + i, Vector2(1024.0f, 1024.0f), Texture::RENDERTARGET,D3DFMT_A32B32G32R32F);
	}

	m_TestPolygon[0] = new Object2DPolygon();
	m_TestPolygon[0]->Init();
	m_TestPolygon[0]->SetPos(Vector2(0.0f, 0.0f));
	m_TestPolygon[0]->SetSize(Vector2(320.0f, 180.0f));
	m_TestPolygon[0]->AddTexture(m_InfoTexture[2]);

	m_TestPolygon[1] = new Object2DPolygon();
	m_TestPolygon[1]->Init();
	m_TestPolygon[1]->SetPos(Vector2(0.0f, 180.0f));
	m_TestPolygon[1]->SetSize(Vector2(320.0f, 180.0f));
	m_TestPolygon[1]->AddTexture(m_InfoTexture[3]);
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
		
}

void ObjectAttractionParticle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	D3DXMatrixIdentity(&m_mtxWorld);
	//pDevice->EndScene();

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

	// ポイントスケールの設定
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	// ポイントスプライト有効化
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, (DWORD)0.1f);
	//ライトオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	D3DXMATRIX proj, view, VP, WVP;
	pDevice->GetTransform(D3DTS_PROJECTION, &proj);
	pDevice->GetTransform(D3DTS_VIEW, &view);
	VP = view*proj;
	WVP = m_mtxWorld*view*proj;

	//Effect
	LPD3DXEFFECT pEffect = Effect::LoadEffectFromFile("data/Shader/AttractionParticleShader.fx");
	pEffect->SetTechnique("AttractionShader");
	//Pass
	UINT numPass;
	pEffect->Begin(&numPass, 0);

	
	/////////////////////////一回目/////////////////////////////////

	//RenderTarget
	//pDevice->SetRenderTarget(0, Renderer::GetBackBufferSurface());
	
	pDevice->SetRenderTarget(0, m_InfoTexture[2]->GetDXSurface());
	pDevice->SetRenderTarget(1, m_InfoTexture[3]->GetDXSurface());
	//BeginScene
	//pDevice->BeginScene();
	//BeginPass
	pEffect->BeginPass(0);
	pEffect->SetMatrix("World", &m_mtxWorld);
	pEffect->SetMatrix("ViewProj", &VP);
	pEffect->SetTexture("PosInput", m_InfoTexture[0]->GetDXTexture());
	pEffect->SetTexture("SpeedInput", m_InfoTexture[1]->GetDXTexture());
	pEffect->SetTexture("PosOutput", m_InfoTexture[2]->GetDXTexture());
	pEffect->SetTexture("SpeedOutput", m_InfoTexture[3]->GetDXTexture());
	pEffect->SetTexture("Tex", NULL);
	pEffect->CommitChanges();
	pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_Pos.size());
	pEffect->EndPass();
	//EndScene
	//pDevice->EndScene();
	////////////////////////二回目//////////////////////////////////
	
	//RenderTarget
	pDevice->SetRenderTarget(0, Renderer::GetBackBufferSurface());
	pDevice->SetRenderTarget(1, NULL);
	//BeginScene
	//pDevice->BeginScene();
	//BeginPass
	pEffect->BeginPass(1);
	pEffect->SetMatrix("World", &m_mtxWorld);
	pEffect->SetMatrix("ViewProj", &VP);
	pEffect->SetTexture("PosInput", m_InfoTexture[0]->GetDXTexture());
	pEffect->SetTexture("SpeedInput", m_InfoTexture[1]->GetDXTexture());
	pEffect->SetTexture("PosOutput", m_InfoTexture[2]->GetDXTexture());
	pEffect->SetTexture("SpeedOutput", m_InfoTexture[3]->GetDXTexture());
	pEffect->SetTexture("Tex", NULL);
	pEffect->CommitChanges();
	pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_Pos.size());
	pEffect->EndPass();	
	//EffectEnd3
	pEffect->End();
	//EndScene
	//pDevice->EndScene();

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);

	////////////////////////////テクスチャ交換///////////////////////////////
	Texture * tex;

	tex = m_InfoTexture[0];
	m_InfoTexture[0] = m_InfoTexture[2];
	m_InfoTexture[2] = tex;

	tex = m_InfoTexture[1];
	m_InfoTexture[1] = m_InfoTexture[3];
	m_InfoTexture[3] = tex;

	//pDevice->BeginScene();
}