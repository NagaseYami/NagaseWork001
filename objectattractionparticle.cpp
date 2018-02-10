#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "effect.h"
#include "object2dpolygon.h"
#include "objectattractionparticle.h"

void ObjectAttractionParticle::Init()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	CreatePointSprite();
	CreateInfoPolygon();
	CreateInfoTexture();

	for (size_t i = 0; i < 4; i++)
	{
		m_TestPolygon[i] = new Object2DPolygon();
		m_TestPolygon[i]->Init();
		m_TestPolygon[i]->SetPos(Vector2(0.0f, 180.0f*(float)i));
		m_TestPolygon[i]->SetSize(Vector2(320.0f, 180.0f));
		m_TestPolygon[i]->AddTexture(m_InfoTexture[i]);
	}
}

void ObjectAttractionParticle::Uninit()
{
	m_TextureList.clear();
	if (m_pVtxBuff_PointSprite != NULL)
	{
		m_pVtxBuff_PointSprite->Release();
		m_pVtxBuff_PointSprite = NULL;
	}
	if (m_pVertex_Declaration_PointSprite)
	{
		m_pVertex_Declaration_PointSprite->Release();
		m_pVertex_Declaration_PointSprite = NULL;
	}
	SAFE_RELEASE(m_pVtxBuff_InfoPolygon);
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
	////////////////////////////////////InfoPolygon描画////////////////////////////////////////////
	//RenderTarget
	pDevice->SetRenderTarget(0, m_InfoTexture[2]->GetDXSurface());
	pDevice->SetRenderTarget(1, m_InfoTexture[3]->GetDXSurface());

	//BeginScene
	pDevice->BeginScene();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	//パイプラインの設定
	pDevice->SetStreamSource(0, m_pVtxBuff_InfoPolygon, 0, sizeof(VERTEX_2D));
	//LoadEffect
	LPD3DXEFFECT pEffect = Effect::LoadEffectFromFile("data/Shader/AttractionParticleShader.fx");
	//SetTechnique
	pEffect->SetTechnique("AttractionShader_Step1");

	//Wolrd View Proj　マトリクス計算
	D3DXMATRIX proj, view, VP, WVP;
	pDevice->GetTransform(D3DTS_PROJECTION, &proj);
	pDevice->GetTransform(D3DTS_VIEW, &view);
	VP = view*proj;
	WVP = m_mtxWorld*view*proj;

	//RunPass
	UINT numPass;
	pEffect->Begin(&numPass, 0);
	for (UINT iPass = 0; iPass < numPass; iPass++)
	{
		pEffect->BeginPass(iPass);
		pEffect->SetMatrix("World", &m_mtxWorld);
		pEffect->SetMatrix("ViewProj", &VP);
		if (m_InitInfoTextureFlag)
		{
			pEffect->SetTexture("PosInput", m_InitInfoTexture[0]->GetDXTexture());
			pEffect->SetTexture("SpeedInput", m_InitInfoTexture[1]->GetDXTexture());
			m_InitInfoTextureFlag = false;
		}
		else
		{
			pEffect->SetTexture("PosInput", m_InfoTexture[0]->GetDXTexture());
			pEffect->SetTexture("SpeedInput", m_InfoTexture[1]->GetDXTexture());
		}
		pEffect->SetTexture("PosOutput", m_InfoTexture[2]->GetDXTexture());
		pEffect->SetTexture("SpeedOutput", m_InfoTexture[3]->GetDXTexture());
		pEffect->SetTexture("Tex", NULL);

		pEffect->CommitChanges();
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		pEffect->EndPass();
	}
	pEffect->End();
	//EndScene
	pDevice->EndScene();
}

void ObjectAttractionParticle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	D3DXMatrixIdentity(&m_mtxWorld);	

	////////////////////////////////////ポイントスプライト描画//////////////////////////////////	
	//VertexDeclaration設定
	pDevice->SetVertexDeclaration(m_pVertex_Declaration_PointSprite);
	//パイプラインの設定
	pDevice->SetStreamSource(0,	m_pVtxBuff_PointSprite,	0,	sizeof(VERTEX_POINT));
	// ポイントスケールの設定
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	// ポイントスプライト有効化
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSIZE_MIN, (DWORD)0.1f);
	//ライトオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//加算合成
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// アルファテストの有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	// 不透明にする値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Wolrd View Proj　マトリクス計算
	D3DXMATRIX proj, view, VP, WVP;
	pDevice->GetTransform(D3DTS_PROJECTION, &proj);
	pDevice->GetTransform(D3DTS_VIEW, &view);
	VP = view*proj;
	WVP = m_mtxWorld*view*proj;

	//Effect
	LPD3DXEFFECT pEffect = Effect::LoadEffectFromFile("data/Shader/AttractionParticleShader.fx");
	pEffect->SetTechnique("AttractionShader_Step2");

	UINT numPass;
	pEffect->Begin(&numPass, 0);
	
	//BeginPass
	pEffect->BeginPass(0);
	pEffect->SetMatrix("World", &m_mtxWorld);
	pEffect->SetMatrix("ViewProj", &VP);
	pEffect->SetTexture("PosInput", m_InfoTexture[0]->GetDXTexture());
	pEffect->SetTexture("SpeedInput", m_InfoTexture[1]->GetDXTexture());
	pEffect->SetTexture("PosOutput", m_InfoTexture[2]->GetDXTexture());
	pEffect->SetTexture("SpeedOutput", m_InfoTexture[3]->GetDXTexture());
	pEffect->SetTexture("Tex", Texture::LoadTextureFromFile("data/Texture/Test/particle.png")->GetDXTexture());
	pEffect->CommitChanges();
	pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, m_Pos.size());
	pEffect->EndPass();	

	//EffectEnd
	pEffect->End();

	//RenderState復元
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//////////////////////////////テクスチャ交換///////////////////////////////
	Texture * tex;

	tex = m_InfoTexture[0];
	m_InfoTexture[0] = m_InfoTexture[2];
	m_InfoTexture[2] = tex;

	tex = m_InfoTexture[1];
	m_InfoTexture[1] = m_InfoTexture[3];
	m_InfoTexture[3] = tex;
}

void ObjectAttractionParticle::CreatePointSprite()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//ポイントスプライト頂点バッファ作成******************************************************************************************************
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_POINT)*m_Pos.size(),
		D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS,
		NULL,
		D3DPOOL_MANAGED,
		&m_pVtxBuff_PointSprite,
		NULL)))
	{
		MessageBox(NULL, "頂点バッファの生成に問題が発生しました", "ObjectAttractionParticle::Init", MB_OK | MB_ICONWARNING);
		return;
	}

	//頂点情報定義
	D3DVERTEXELEMENT9 elements[] = {
		{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0 },
		{ 0,12,D3DDECLTYPE_D3DCOLOR,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0 },
		{ 0,16,D3DDECLTYPE_FLOAT1,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_PSIZE,0 },
		{ 0,20,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,1 },
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(elements, &m_pVertex_Declaration_PointSprite);

	//頂点情報初期値計算
	for (unsigned int i = 0; i < m_Pos.size(); i++)
	{
		m_Pos[i] = Vector3(float(rand() % 100 - 50), float(rand() % 100 - 50), float(rand() % 100 - 50));
		m_Speed[i] = Vector3(0.0f, 0.0f, 0.0f);
		m_Color[i] = Vector4(255, 255, 255, 255);
	}
	for (unsigned int i = 0; i < 100; i++)
	{
		for (unsigned int o = 0; o < 1000; o++)
		{
			m_InfoUV[i * 1000 + o].x = (float)i / 1024.0f;
			m_InfoUV[i * 1000 + o].y = (float)o / 1024.0f;
		}
	}

	//頂点情報をデバイスに渡す
	VERTEX_POINT* pVtx;
	m_pVtxBuff_PointSprite->Lock(0, 0, (void**)&pVtx, 0);
	for (unsigned int i = 0; i < m_Pos.size(); i++)
	{
		pVtx[i].pos = m_Pos[i];
		pVtx[i].color = D3DCOLOR_ARGB((int)m_Color[i].w, (int)m_Color[i].x, (int)m_Color[i].y, (int)m_Color[i].z);
		pVtx[i].size = 10.0f;
		pVtx[i].InfoUV = m_InfoUV[i];
	}
	m_pVtxBuff_PointSprite->Unlock();
}

void ObjectAttractionParticle::CreateInfoPolygon()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//頂点作成*******************************************************************************

	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,	
		D3DUSAGE_WRITEONLY,		
		FVF_VERTEX_2D,			
		D3DPOOL_MANAGED,		
		&m_pVtxBuff_InfoPolygon,
		NULL
	))) {
		MessageBox(NULL, "頂点バッファの生成に問題が発生しました", "ERROR from object2dpolygon.cpp", MB_OK | MB_ICONWARNING);
	}

	// ポリゴンの位置を設定**************************************************************************************
	VERTEX_2D* pVtx;

	//頂点バッファをロックして仮想アドレスを取得する
	m_pVtxBuff_InfoPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//左上
	pVtx[0].pos = Vector3(0.0f, 0.0f,0.0f);
	pVtx[1].pos = Vector3(1024.0f, 0.0f,0.0f);
	pVtx[2].pos = Vector3(0.0f, 1024.0f,0.0f);
	pVtx[3].pos = Vector3(1024.0f, 1024.0f,0.0f);

	//rhwの設定(必ず1.0f)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定(0~255の整数値)
	pVtx[0].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].col = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].col = D3DCOLOR_RGBA(255,255,255,255);

	//頂点データへUVデータの追加
	pVtx[0].tex = Vector2(0.0f,0.0f);
	pVtx[1].tex = Vector2(1.0f,0.0f);
	pVtx[2].tex = Vector2(0.0f,1.0f);
	pVtx[3].tex = Vector2(1.0f,1.0f);

	//ロック解除
	m_pVtxBuff_InfoPolygon->Unlock();
}

void ObjectAttractionParticle::CreateInfoTexture()
{
	auto pDevice = Renderer::GetDevice();
	//PosとSpeedを保存用のテクスチャをCreate　入力と出力両方合計4枚
	for (int i = 0; i < 4; i++)
	{
		m_InfoTexture[i] = Texture::CreateEmptyTexture("AttractionParticleInfoTexture" + i, Vector2(1024.0f, 1024.0f), Texture::RENDERTARGET, D3DFMT_A32B32G32R32F);
	}
	//初期値を保存するテクスチャ
	for (size_t i = 0; i < 2; i++)
	{
		m_InitInfoTexture[i] = Texture::CreateEmptyTexture("AttractionParticleInitInfoTexture" + i, Vector2(1024.0f, 1024.0f), Texture::DYNAMIC, D3DFMT_A32B32G32R32F);
	}

	D3DLOCKED_RECT lock_rect;
	if (m_InitInfoTexture[0]->GetDXSurface()->LockRect(&lock_rect, NULL, D3DLOCK_DISCARD) == D3DERR_INVALIDCALL) {
		return;
	}

	//メモリ確保
	ZeroMemory(lock_rect.pBits, lock_rect.Pitch * 1024);

	//書き込む
	auto startaddress = (Vector4*)lock_rect.pBits;
	for (size_t count = 0; count < 100; ++count)
	{
		for (size_t i = 0; i < 1000; i++)
		{
			const Vector4 randpos = Vector4(m_Pos[count * 1000 + i], 1.0f);
			memcpy(startaddress + i, &randpos, sizeof(randpos));
		}
		startaddress += 1024;
	}
	m_InitInfoTexture[0]->GetDXSurface()->UnlockRect();
	
	m_InitInfoTexture[1]->GetDXSurface()->LockRect(&lock_rect, NULL, D3DLOCK_DISCARD);

	//メモリ確保
	ZeroMemory(lock_rect.pBits, lock_rect.Pitch * 1024);

	//書き込む
	startaddress = (Vector4*)lock_rect.pBits;
	for (size_t count = 0; count < 100; ++count)
	{
		for (size_t i = 0; i < 1000; i++)
		{
			const Vector4 randpos = Vector4(m_Speed[count * 1000 + i], 1.0f);
			memcpy(startaddress + i, &randpos, sizeof(randpos));
		}
		startaddress += 1024;
	}
	m_InitInfoTexture[1]->GetDXSurface()->UnlockRect();	
}
