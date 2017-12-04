#pragma once
struct KEY {
	int Frame;
	Vector3 Pos;
	Vector3 Rot;
};

bool operator<(const KEY& left, const KEY& right);
bool operator>(const KEY& left, const KEY& right);

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
	D3DXMATRIX GetWorldMtx(void) { 
		return m_mtxWorld; 
	}
	//Setter
	void SetTexture(Texture * value, int number) {
		m_TextureList[number] = value;
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
	void SetRFP(Vector3 value) {
		m_RFP = value;
	}
	void SetTFP(Vector3 value) {
		m_TFP = value;
	}
	void SetLight(bool value) {
		m_bLight = value;
	}
	void SetKeyList(const vector<KEY> & l_KeyList) { 
		m_KeyList = l_KeyList; 
	}
	void ResetKeyList(void) { 
		m_KeyList.clear(); 
	}
	void SetTimer(const int & l_timer) { 
		m_FrameTimer = l_timer; 
	}
private:
	int TexNum;
	LPD3DXMESH m_pMesh = NULL;											//メッシュ情報
	LPD3DXBUFFER m_BuffMat = NULL;										//マテリアル情報
	DWORD m_nNumMat = TexNum;											//マテリアル情報の数
	LPCSTR m_xFileName;

	//D3DXQUATERNION m_Quaternion;

	D3DXMATRIX m_mtxWorld;
	D3DXMATRIX m_mtxRot;
	D3DXMATRIX m_mtxTra;
	D3DXMATRIX m_mtxSca;

	ObjectXModel * m_pParent = nullptr;
	Vector3 m_TFP = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_RFP = Vector3(0.0f, 0.0f, 0.0f);

	Vector3 m_Rot = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Tra = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Sca = Vector3(1.0f, 1.0f, 1.0f);

	int m_FrameTimer = 0;
	vector<KEY> m_KeyList;

	bool m_bLight = true;
};