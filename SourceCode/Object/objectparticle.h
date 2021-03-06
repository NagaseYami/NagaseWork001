﻿#pragma once
#include "../Main/main.h"
#include "object.h"
class ObjectParticle : public Object {
public:
	struct VERTEX_POINT{
		Vector3 pos;
		D3DCOLOR color;
		float size;		
		Vector3 dir;
	};

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
	void AddTexture(Texture * value) {
		m_TextureList.push_back(value);
	}
	void SetTexture(unsigned int value) {
		if (value < m_TextureList.size())
		{
			m_TexNum = value;
		}
	}
	void SetRot(Vector3 value) {
		m_Rot = value;
	}
	void SetTra(Vector3 value) {
		m_Tra = value;
	}
	void SetSca(Vector3 value) {
		m_Sca = value;
	}
	void SetLight(bool value) {
		m_bLight = value;
	}
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	LPDIRECT3DVERTEXDECLARATION9 m_pVertexDeclaration = NULL;

	D3DXMATRIX				m_mtxWorld;
	D3DXMATRIX				m_mtxRot;
	D3DXMATRIX				m_mtxTra;
	D3DXMATRIX				m_mtxSca;

	Vector3					m_Rot = Vector3(0.0f, 0.0f, 0.0f);
	Vector3					m_Tra = Vector3(0.0f, 0.0f, 0.0f);
	Vector3					m_Sca = Vector3(1.0f, 1.0f, 1.0f);

	array<Vector4, 1000000>	m_Pos;
	array<Vector3, 1000000>	m_Dir;
	array<Vector4, 1000000>	m_Color;

	int						m_TexNum = 0;
	bool					m_bLight = true;
	float					m_Timer = 0.0f;
};