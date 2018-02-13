#pragma once
#include "../Main/main.h"
#include "object.h"
class ObjectStencilShadow :public Object{
public:
	void Init();
	void Uninit();
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Draw();

	//Getter
	Vector3 GetRot() {
		return m_Rot;
	}
	Vector3 GetTra() {
		return m_Tra;
	}
	Vector3 GetSca() {
		return m_Sca;
	}

	//Setter
	void SetRot(Vector3 value) {
		m_Rot = value;
	}
	void SetTra(Vector3 value) {
		m_Tra = value;
	}
	void SetSca(Vector3 value) {
		m_Sca = value;
	}
private:
	int TexNum;
	LPD3DXMESH m_pMesh = NULL;											//メッシュ情報
	LPD3DXBUFFER m_BuffMat = NULL;										//マテリアル情報
	DWORD m_nNumMat = TexNum;											//マテリアル情報の数
	LPCSTR m_xFileName = "data/Model/StencilShadow/StencilShadow.x";
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;
	D3DXQUATERNION m_Quaternion;
	D3DXMATRIX m_mtxWorld;
	D3DXMATRIX m_mtxRot;
	D3DXMATRIX m_mtxTra;
	D3DXMATRIX m_mtxSca;
	Vector3 m_Rot = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Tra = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Sca = Vector3(1.0f, 1.0f, 1.0f);
};