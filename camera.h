#pragma once
class Camera {
public:
	static void SetMtxProjection(void);
	static void UpdateMainCamera(void);	
	virtual void Update() = 0;

	//Getter
	Vector3 GetLookat(void) { 
		return m_Lookat; 
	}
	Vector3 GetEye(void) { 
		return m_Eye; 
	}
	float Getxz(void) { 
		return xz; 
	}

	static Vector3 GetMainCameraLookat(void) {
		return MainCamera->m_Lookat;
	}
	static Vector3 GetMainCameraEye(void) {
		return MainCamera->m_Eye;
	}
	static float GetMainCameraxz(void) {
		return MainCamera->xz;
	}
	//Setter
	static void SetMainCamera(Camera * camera) {
		MainCamera = camera;
	}
	void SetLookat(Vector3 l_Lookat) {
		m_Lookat = l_Lookat;
	}
protected:
	D3DXMATRIX m_MtxView;
	Vector3 m_Lookat = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Eye = Vector3(0.0f, 0.0f, 10.0f);
	Vector3 m_VecUp = Vector3(0.0f, 1.0f, 0.0f);
	float yz = 0.0f;
	float xz = -D3DX_PI / 2;
private:
	static D3DXMATRIX m_MtxProj;
	static Camera * MainCamera;
};