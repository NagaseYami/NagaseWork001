#include "main.h"
#include "renderer.h"
#include "object.h"
#include "objectstencilshadow.h"

void ObjectStencilShadow::Init()
{

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//xファイル読み込み*******************************************************************************************
	if (FAILED(D3DXLoadMeshFromX(
		m_xFileName,
		D3DXMESH_MANAGED,
		pDevice,
		NULL,
		&m_BuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh
	))) {
		//エラーメッセージ
		MessageBox(NULL, "モデルが取得できませんでした。", "ERROR from objectstencilshadow.cpp", MB_OK | MB_DEFBUTTON1);
	}
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
	pVtx[0].pos = Vector3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = Vector3((float)SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = Vector3(0.0f, (float)SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = Vector3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f);

	//rhwの設定(必ず1.0f)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定(0~255の整数値)
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);

	//頂点データへUVデータの追加
	pVtx[0].tex = Vector2(0.0f, 0.0f);
	pVtx[1].tex = Vector2(1.0f, 0.0f);
	pVtx[2].tex = Vector2(0.0f, 1.0f);
	pVtx[3].tex = Vector2(1.0f, 1.0f);

	//ロック解除
	m_pVtxBuff->Unlock();

	D3DXQuaternionIdentity(&m_Quaternion);
}

void ObjectStencilShadow::Uninit()
{
	if (m_pMesh)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	if (m_BuffMat)
	{
		m_BuffMat->Release();
		m_BuffMat = NULL;
	}
}

void ObjectStencilShadow::FixedUpdate()
{
}

void ObjectStencilShadow::Update()
{
}

void ObjectStencilShadow::LateUpdate()
{

}

void ObjectStencilShadow::Draw()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&m_mtxSca, m_Sca.x, m_Sca.y, m_Sca.z);
	//D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	D3DXMatrixRotationQuaternion(&m_mtxRot, &m_Quaternion);
	D3DXMatrixTranslation(&m_mtxTra, m_Tra.x, m_Tra.y, m_Tra.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxSca);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTra);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);					// ステンシルバッファへ書き込み宣言
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);					// Zバッファへ書き込みを禁止
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);					// レンダリング ターゲットのカラー バッファに対するチャンネルごとの書き込みを有効にする UINT 値。
	//pDevice->SetRenderState(D3DRS_STENCILMASK, 0x000000ff);				// ステンシルマスク
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_STENCILREF, 1);						// ステンシル参照値
	
	//表
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	
	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);//現在デバイスに設定されてるマテリアル情報を取得
	D3DXMATERIAL* pMat;
	pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();
	for (int i = 0; i < (int)m_nNumMat; i++) {
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//テクスチャ配置
		pDevice->SetTexture(0, NULL);

		//メッシュの描画
		m_pMesh->DrawSubset(i);

	}
	pDevice->SetMaterial(&matDef);
	//裏
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	pDevice->GetMaterial(&matDef);//現在デバイスに設定されてるマテリアル情報を取得
	pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();
	for (int i = 0; i < (int)m_nNumMat; i++) {
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//テクスチャ配置
		pDevice->SetTexture(0, NULL);

		//メッシュの描画
		m_pMesh->DrawSubset(i);

	}
	pDevice->SetMaterial(&matDef);

	//ポリゴン
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);					// レンダリング ターゲットのカラー バッファに対するチャンネルごとの書き込みを有効にする UINT 値。
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	
	pDevice->SetTexture(0, NULL);
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);	
	
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}
