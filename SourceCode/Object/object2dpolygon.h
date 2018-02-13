#pragma once
#include "../Main/main.h"
#include "object.h"

struct VERTEX_2D
{
	Vector3 pos;	
	float rhw;		
	D3DCOLOR col;	
	Vector2 tex;	
};

class Object2DPolygon : public Object{
public:
	
	virtual void Init();
	virtual void Uninit();
	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Draw();

	//Getter
	Vector2 GetPos() {
		return m_Pos;
	}
	Vector2 GetSize() {
		return m_Size;
	}
	Vector2 GetUv() {
		return m_Uv;
	}
	Vector2 GetUvSize() {
		return m_UvSize;
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
	void SetPos(Vector2 value) {
		m_Pos = value;
	}
	void SetPosbyCenter(Vector2 value) {//You should set Size First
		m_Pos = value - m_Size / 2;
	}
	void SetSize(Vector2 value) {
		m_Size = value;
	}
	void SetUv(Vector2 value) {
		m_Uv = value;
	}
	void SetUvSize(Vector2 value) {
		m_UvSize = value;
	}
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	Vector2						m_Pos = Vector2(0.0f, 0.0f);
	Vector2						m_Size = Vector2(100.0f, 100.0f);
	Vector2						m_Uv = Vector2(0.0f, 0.0f);
	Vector2						m_UvSize = Vector2(1.0f, 1.0f);
	Vector4						m_Color = Vector4(255.0f, 255.0f, 0.0f, 255.0f);
	int							m_TexNum = 0;
};