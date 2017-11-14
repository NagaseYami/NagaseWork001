#include "main.h"
#include "renderer.h"
#include "object.h"
#include "objectXModel.h"

ObjectXModel::ObjectXModel(LPCSTR filepath)
{
	m_xFileName = filepath;
}

void ObjectXModel::Init()
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
		MessageBox(NULL, "モデルが取得できませんでした。", "ERROR from objectXModel.cpp", MB_OK | MB_DEFBUTTON1);
	}

	for (int i = 0; i < (int)m_nNumMat; i++)
	{
		LPDIRECT3DTEXTURE9 voidvalue = NULL;
		m_pTextureList.push_back(voidvalue);
	}

	D3DXQuaternionIdentity(&m_Quaternion);
}

void ObjectXModel::Uninit()
{
	m_pTextureList.clear();
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

void ObjectXModel::FixedUpdate()
{
}

void ObjectXModel::Update()
{
}

void ObjectXModel::LateUpdate()
{
}

void ObjectXModel::Draw()
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

	D3DMATERIAL9 matDef;

	pDevice->GetMaterial(&matDef);//現在デバイスに設定されてるマテリアル情報を取得
	D3DXMATERIAL* pMat;

	pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();
	if (!m_bLight)
	{
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	for (int i = 0; i < (int)m_nNumMat; i++) {
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//テクスチャ配置
		pDevice->SetTexture(0, m_pTextureList[i]);

		//メッシュの描画
		m_pMesh->DrawSubset(i);

	}
	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
