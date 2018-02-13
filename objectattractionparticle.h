#pragma once
#include "object.h"
#define ATTRACTION_PARTICLE_AMOUNT 450000
class Object2DPolygon;
class ObjectAttractionParticle : public Object{
public:
	struct VERTEX_POINT {
		Vector3 pos;
		D3DCOLOR color;
		float size;
		Vector2 InfoUV;
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
	void CreatePointSprite();
	void CreateInfoPolygon();
	void CreateInfoTexture();

	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff_InfoPolygon = NULL;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff_PointSprite = NULL;		// 頂点バッファへのポインタ
	LPDIRECT3DVERTEXDECLARATION9 m_pVertex_Declaration_PointSprite = NULL;

	D3DXMATRIX				m_mtxWorld;
	D3DXMATRIX				m_mtxRot;
	D3DXMATRIX				m_mtxTra;
	D3DXMATRIX				m_mtxSca;

	Vector3					m_Rot = Vector3(0.0f, 0.0f, 0.0f);
	Vector3					m_Tra = Vector3(0.0f, 0.0f, 0.0f);
	Vector3					m_Sca = Vector3(1.0f, 1.0f, 1.0f);

	array<Vector3, ATTRACTION_PARTICLE_AMOUNT>	m_Pos;
	array<Vector3, ATTRACTION_PARTICLE_AMOUNT>	m_Speed;
	array<Vector2, ATTRACTION_PARTICLE_AMOUNT>	m_InfoUV;
	array<Vector4, ATTRACTION_PARTICLE_AMOUNT>	m_Color;

	int						m_TexNum = 0;
	bool					m_bLight = true;

	array<Texture*, 4> m_InfoTexture;
	array<Texture*, 2> m_InitInfoTexture;
	bool m_InitInfoTextureFlag = true;
	array<Object2DPolygon*, 2> m_TestPolygon;
};