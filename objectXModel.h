#pragma once
class ObjectXModel : public Object{
public:
	ObjectXModel(LPCSTR filepath);
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
	void SetTexture(LPDIRECT3DTEXTURE9 value, int number) {
		m_pTextureList[number] = value;
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
	int TexNum;
	LPD3DXMESH m_pMesh = NULL;											//メッシュ情報
	LPD3DXBUFFER m_BuffMat = NULL;										//マテリアル情報
	DWORD m_nNumMat = TexNum;											//マテリアル情報の数
	vector<LPDIRECT3DTEXTURE9> m_pTextureList;							//テクスチャ、テクスチャインターフェース
	LPCSTR m_xFileName;
	D3DXQUATERNION m_Quaternion;
	D3DXMATRIX m_mtxWorld;
	D3DXMATRIX m_mtxRot;
	D3DXMATRIX m_mtxTra;
	D3DXMATRIX m_mtxSca;
	Vector3 m_Rot = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Tra = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Sca = Vector3(1.0f, 1.0f, 1.0f);
	bool m_bLight = true;
};