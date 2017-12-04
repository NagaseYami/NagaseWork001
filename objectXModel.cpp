#include "main.h"
#include "renderer.h"
#include "camera.h"
#include "object.h"
#include "objectXModel.h"
#include "texture.h"
#include "effect.h"

ObjectXModel::ObjectXModel(LPCSTR filepath)
{
	m_xFileName = filepath;
}

void ObjectXModel::Init()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	
	//xファイル読み込み
	LPD3DXBUFFER AdjacencyBuffer = NULL;
	LPD3DXMESH OldMesh = NULL;
	if (FAILED(D3DXLoadMeshFromX(
		m_xFileName,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		&AdjacencyBuffer,
		&m_BuffMat,
		NULL,
		&m_nNumMat,
		&OldMesh
	))) {
		//エラーメッセージ
		MessageBox(NULL, "モデルが取得できませんでした。", "D3DXLoadMeshFromX", MB_OK | MB_DEFBUTTON1);
	}
	//メッシュの最適化
	if (FAILED(
		OldMesh->OptimizeInplace(
			D3DXMESHOPT_COMPACT|D3DXMESHOPT_ATTRSORT|D3DXMESHOPT_VERTEXCACHE,
			(DWORD*)AdjacencyBuffer->GetBufferPointer(),NULL,NULL,NULL)))
	{
		MessageBox(NULL, "メッシュの最適化が失敗しました。", "ID3DMesh::OptimizeInplaces", MB_OK | MB_DEFBUTTON1);
	}
	AdjacencyBuffer->Release();
	AdjacencyBuffer = NULL;
	
	//頂点データの変更
	D3DVERTEXELEMENT9 decl[] = {
		{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0 } ,
		{ 0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0 },
		{ 0,24,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0 },
		{ 0,32,D3DDECLTYPE_SHORT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_BLENDINDICES,0 },
		{ 0,40,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_BLENDWEIGHT,0 },
		{ 0,56,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_BINORMAL,0 },
		{ 0,68,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TANGENT,0 },
		D3DDECL_END()
	};



	if (FAILED(
		OldMesh->CloneMesh(D3DXMESH_MANAGED, decl, pDevice, &m_pMesh)
	))
	{
		MessageBox(NULL, "メッシュのクローンが失敗しました。", "ID3DMesh::CloneMesh", MB_OK | MB_DEFBUTTON1);
	}


	//各頂点の法線ベクトルを計算
	//D3DXComputeNormals(m_pMesh, NULL);

	//テクスチャリストに空のテクスチャを入れる
	for (int i = 0; i < (int)m_nNumMat; i++)
	{
		m_TextureList.push_back(new Texture);
		m_TextureList[i]->SetDXTexture(NULL);
	}

	//D3DXQuaternionIdentity(&m_Quaternion);
}

void ObjectXModel::Uninit()
{
	m_TextureList.clear();
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
	if (m_KeyList.size() > 1)
	{
		for (int i = m_KeyList.size() - 2; i > -1; --i)
		{
			if (m_KeyList.at(i).Frame <= m_FrameTimer)
			{
				m_Rot = m_KeyList.at(i).Rot + (m_KeyList.at(i + 1).Rot - m_KeyList.at(i).Rot) / (float)(m_KeyList.at(i + 1).Frame - m_KeyList.at(i).Frame)*(float)(m_FrameTimer - m_KeyList.at(i).Frame);
				m_Tra = m_KeyList.at(i).Pos + (m_KeyList.at(i + 1).Pos - m_KeyList.at(i).Pos) / (float)(m_KeyList.at(i + 1).Frame - m_KeyList.at(i).Frame)*(float)(m_FrameTimer - m_KeyList.at(i).Frame);
				if (m_FrameTimer >= m_KeyList.at(m_KeyList.size() - 1).Frame)
				{
					m_Rot = m_KeyList.at(m_KeyList.size() - 1).Rot;
					m_Tra = m_KeyList.at(m_KeyList.size() - 1).Pos;
				}
				break;
			}
		}
	}
	else if (m_KeyList.size() == 1)
	{
		m_Rot = m_KeyList.at(0).Rot;
		m_Tra = m_KeyList.at(0).Pos;
	}
	else if (m_KeyList.size() == 0)
	{
		m_Rot = Vector3(0.0f, 0.0f, 0.0f);
		m_Tra = Vector3(0.0f, 0.0f, 0.0f);
	}
}

void ObjectXModel::Draw()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&m_mtxSca, m_Sca.x, m_Sca.y, m_Sca.z);
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_Rot.y + m_RFP.y, m_Rot.x + m_RFP.x, m_Rot.z + m_RFP.z);
	//D3DXMatrixRotationQuaternion(&m_mtxRot, &m_Quaternion);
	D3DXMatrixTranslation(&m_mtxTra, m_Tra.x + m_TFP.x, m_Tra.y + m_TFP.y, m_Tra.z + m_TFP.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxSca);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTra);
	if (m_pParent != nullptr)
	{
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_pParent->GetWorldMtx());
	}

	//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);//現在デバイスに設定されてるマテリアル情報を取得
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();
	
	if (!m_bLight)
	{
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	LPD3DXEFFECT pEffect = Effect::LoadEffectFromFile("data/Shader/BasicShader.fx");

	for (int i = 0; i < m_TextureList.size(); i++)
	{
		if (m_TextureList[i]->GetDXTexture() != NULL)
		{
			pEffect->SetTechnique("TexterTech");
			break;
		}
		else
		{
			pEffect->SetTechnique("NoTexterTech");
		}
	}

	m_RFP.y += 0.01f;

	UINT numPass;
	pEffect->Begin(&numPass, 0);

	D3DXMATRIX proj, view, WVP,WI,WIT;
	pDevice->GetTransform(D3DTS_PROJECTION, &proj);
	pDevice->GetTransform(D3DTS_VIEW, &view);
	WVP = m_mtxWorld*view*proj;
	D3DXMatrixInverse(&WI, nullptr, &m_mtxWorld);
	D3DXMatrixTranspose(&WIT, &WI);
	for (UINT iPass = 0; iPass < numPass; iPass++)
	{
		pEffect->BeginPass(iPass);
		for (int i = 0; i < (int)m_nNumMat; i++) {
			D3DXVECTOR4 amb = D3DXVECTOR4(pMat[i].MatD3D.Ambient.r, pMat[i].MatD3D.Ambient.g, pMat[i].MatD3D.Ambient.b, pMat[i].MatD3D.Ambient.a);
			D3DXVECTOR4 dif = D3DXVECTOR4(pMat[i].MatD3D.Diffuse.r, pMat[i].MatD3D.Diffuse.g, pMat[i].MatD3D.Diffuse.b, pMat[i].MatD3D.Diffuse.a);
			//D3DXVECTOR4 dif = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			//D3DXVECTOR4 spc = D3DXVECTOR4(pMat[i].MatD3D.Specular.r, pMat[i].MatD3D.Specular.g, pMat[i].MatD3D.Specular.b, pMat[i].MatD3D.Specular.a);
			D3DXVECTOR4 spc = D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f);
			
			pEffect->SetVector("Diffuse", &dif);
			pEffect->SetVector("Specular", &spc);
			pEffect->SetVector("Ambient", &amb);
			pEffect->SetTexture("Tex", m_TextureList[i]->GetDXTexture());	
			pEffect->SetMatrix("World",&m_mtxWorld);
			pEffect->SetMatrix("WorldViewProj", &WVP);
			pEffect->SetMatrix("WorldInverseTranspose", &WIT);
			pEffect->SetVector("LightPos", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
			pEffect->SetVector("LightDir", &D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.0f));
			pEffect->SetVector("CameraPos", &D3DXVECTOR4(Camera::GetMainCameraEye().x, Camera::GetMainCameraEye().y, Camera::GetMainCameraEye().z, 1.0f));
			pEffect->CommitChanges();
			m_pMesh->DrawSubset(i);
		}
		pEffect->EndPass();
	}

	pEffect->End();

	pDevice->SetMaterial(&matDef);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

bool operator<(const KEY & left, const KEY & right)
{
	return left.Frame < right.Frame;
}

bool operator>(const KEY & left, const KEY & right)
{
	return left.Frame > right.Frame;
}