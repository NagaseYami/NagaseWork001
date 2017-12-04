#pragma once
class Object3DPolygon : public Object {
public:

	void Init();
	void Uninit();
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Draw();	

	//Getter
	Vector3 GetPos() {
		return m_Pos;
	}
	Vector3 GetSize() {
		return m_Size;
	}
	Vector2 GetUv() {
		return m_Uv;
	}
	Vector2 GetUvSize() {
		return m_UvSize;
	}
	Vector3 GetRot(){
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
	void SetPos(Vector3 value) {
		m_Pos = value;
	}
	void SetPosbyCenter(Vector3 value) {//You should set Size First
		m_Pos = value - Vector3(m_Size.x / 2, -m_Size.y / 2, 0.0f);
	}
	void SetSize(Vector3 value) {
		m_Size = value;
	}
	void SetUv(Vector2 value) {
		m_Uv = value;
	}
	void SetUvSize(Vector2 value) {
		m_UvSize = value;
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

	D3DXMATRIX				m_mtxWorld;
	D3DXMATRIX				m_mtxRot;
	D3DXMATRIX				m_mtxTra;
	D3DXMATRIX				m_mtxSca;

	Vector3					m_Rot = Vector3(0.0f, 0.0f, 0.0f);
	Vector3					m_Tra = Vector3(0.0f, 0.0f, 0.0f);
	Vector3					m_Sca = Vector3(1.0f, 1.0f, 1.0f);

	Vector3					m_Pos = Vector3(0.0f, 0.0f, 0.0f);
	Vector3					m_Size = Vector3(1.0f, 1.0f, 0.0f);
	Vector2					m_Uv = Vector2(0.0f, 0.0f);
	Vector2					m_UvSize = Vector2(1.0f, 1.0f);
	Vector4					m_Color = Vector4(255.0f, 255.0f, 255.0f, 255.0f);

	int						m_TexNum = 0;
	bool m_bLight = true;
};