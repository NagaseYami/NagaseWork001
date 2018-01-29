#pragma once
class Camera {
public:
	static void SetPerspectiveMtxProjection(void);
	static void SetOrthoMtxProjection(void);
	static void SetShadowCamera(void);
	static void UpdateMainCamera(void);	
	virtual void Update() = 0;

	//Getter
	static Vector3 GetMainCameraLookat(void) {
		return MainCamera->m_Lookat;
	}
	static Vector3 GetMainCameraEye(void) {
		return MainCamera->m_Eye;
	}
	static float GetMainCameraxz(void) {
		return MainCamera->xz;
	}
	static D3DXMATRIX GetShadowProj(void) {
		return m_ShadowProj;
	}
	static D3DXMATRIX GetShadowView(void) {
		return m_ShadowView;
	}
	static float GetShadowFar(void) {
		return m_ShadowFar;
	}
	//Setter
	static void SetMainCamera(Camera * camera) {
		MainCamera = camera;
	}
	static void SetmainCameraxz(float value) {
		MainCamera->xz = value;
	}
	void SetLookat(Vector3 l_Lookat) {
		m_Lookat = l_Lookat;
	}
protected:
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

	D3DXMATRIX m_MtxView;
	Vector3 m_Lookat = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 m_Eye = Vector3(0.0f, 0.0f, -200.0f);
	Vector3 m_VecUp = Vector3(0.0f, 1.0f, 0.0f);
	float yz = 0.0f;
	float xz = -D3DX_PI / 2;
private:
	static D3DXMATRIX m_MtxProj;
	static Camera * MainCamera;
	static Vector3 m_ShadowLookat;
	static Vector3 m_ShadowEye;
	static Vector3 m_ShadowVecUp;
	static D3DXMATRIX m_ShadowProj;
	static D3DXMATRIX m_ShadowView;
	static float m_ShadowFar;
};