#pragma once

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
	void SetTexture(LPDIRECT3DTEXTURE9 value) {
		m_pTexture = value;
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
	LPDIRECT3DTEXTURE9			m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	Vector2						m_Pos = Vector2(0.0f, 0.0f);
	Vector2						m_Size = Vector2(100.0f, 100.0f);
	Vector2						m_Uv = Vector2(0.0f, 0.0f);
	Vector2						m_UvSize = Vector2(1.0f, 1.0f);
	Vector4						m_Color = Vector4(255.0f, 255.0f, 255.0f, 255.0f);
};