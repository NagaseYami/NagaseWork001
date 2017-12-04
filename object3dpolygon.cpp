#include "main.h"
#include "renderer.h"
#include "texture.h"
#include "object.h"
#include "object3dpolygon.h"

void Object3DPolygon::Init()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	//頂点バッファ作成******************************************************************************************************
	if (FAILED(
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&m_pVtxBuff,
			NULL)
	))
	{
		MessageBox(NULL, "頂点バッファの生成に問題が発生しました", "ERROR from object3dpolygon.cpp", MB_OK | MB_ICONWARNING);
		return;
	}
}

void Object3DPolygon::Uninit()
{
	m_TextureList.clear();
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

void Object3DPolygon::FixedUpdate()
{
}

void Object3DPolygon::Update()
{
}

void Object3DPolygon::LateUpdate()
{
	//頂点バッファ
	VERTEX_3D* pVtx;
	//頂点バッファをロックして、仮想アドレスを取得する
	m_pVtxBuff->Lock(0,
		0,
		(void**)&pVtx,
		0);

	//頂点座標の設定(2D座標・右回り)
	pVtx[0].pos = Vector3(m_Pos.x, m_Pos.y, 0.0f);
	pVtx[1].pos = Vector3(m_Pos.x + m_Size.x, m_Pos.y, 0.0f);
	pVtx[2].pos = Vector3(m_Pos.x, m_Pos.y - m_Size.y, 0.0f);
	pVtx[3].pos = Vector3(m_Pos.x + m_Size.x, m_Pos.y - m_Size.y, 0.0f);

	for (int i = 0; i<4; i++) {
		pVtx[i].normal = Vector3(0.0f, 0.0f, -1.0f);
		//頂点カラー(0～255の整数値)
		pVtx[i].color = D3DCOLOR_RGBA((int)m_Color.x, (int)m_Color.y, (int)m_Color.z, (int)m_Color.w);
	}

	//頂点UV値の設定
	pVtx[0].tex = Vector2(m_Uv.x, m_Uv.y);
	pVtx[1].tex = Vector2(m_Uv.x + m_UvSize.x, m_Uv.y);
	pVtx[2].tex = Vector2(m_Uv.x, m_Uv.y + m_UvSize.y);
	pVtx[3].tex = Vector2(m_Uv.x + m_UvSize.x, m_Uv.y + m_UvSize.y);

	//鍵をアンロック
	m_pVtxBuff->Unlock();
}

void Object3DPolygon::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixScaling(&m_mtxSca, m_Sca.x, m_Sca.y, m_Sca.z);
	D3DXMatrixRotationYawPitchRoll(&m_mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);
	//D3DXMatrixRotationQuaternion(&m_mtxRot, &m_Quaternion);
	D3DXMatrixTranslation(&m_mtxTra, m_Tra.x, m_Tra.y, m_Tra.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxSca);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxRot);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxTra);
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//MESHFIELDの描画をする寸前
	pDevice->SetTexture(0, m_TextureList[m_TexNum]->GetDXTexture());

	//パイプラインの設定
	pDevice->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_3D));

	if (!m_bLight)
	{
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
