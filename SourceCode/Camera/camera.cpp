#include "../Input/input.h"
#include "../Renderer/renderer.h"
#include "camera.h"

D3DXMATRIX Camera::m_MtxProj;
Camera * Camera::MainCamera = nullptr;
Vector3 Camera::m_ShadowLookat;
Vector3 Camera::m_ShadowEye;
Vector3 Camera::m_ShadowVecUp;
D3DXMATRIX Camera::m_ShadowProj;
D3DXMATRIX Camera::m_ShadowView;
float Camera::m_ShadowFar;

void Camera::SetPerspectiveMtxProjection(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	D3DXMATRIX mtxProj;
	
	D3DXMatrixPerspectiveFovLH(
		&mtxProj,
		D3DX_PI / 3.0f,							//視野角
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,	//アスペクト比
		0.1f,									//near(必ず0.0fより大きい数字を入れてください)
		1000.0f									//far
	);
	
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProj);
}

void Camera::SetOrthoMtxProjection(void)
{
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
	D3DXMATRIX mtxProj;
	m_ShadowFar = 170.0f;
	D3DXMatrixOrthoLH(&m_ShadowProj, 320.0f, 180.0f, 0.1f, m_ShadowFar);
	pDevice->SetTransform(D3DTS_PROJECTION, &m_ShadowProj);
}

void Camera::SetShadowCamera(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();

	m_ShadowLookat = Vector3(0.0f, 0.0f, 0.0f);
	m_ShadowEye = Vector3(0.0f, 70.0f, -70.0f);
	m_ShadowVecUp = Vector3(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&m_ShadowView, (D3DXVECTOR3*)&m_ShadowEye, (D3DXVECTOR3*)&m_ShadowLookat, (D3DXVECTOR3*)&m_ShadowVecUp);
	pDevice->SetTransform(D3DTS_VIEW, &m_ShadowView);
}

void Camera::UpdateMainCamera(void)
{
	if (MainCamera)
	{
		//デバイス取得
		LPDIRECT3DDEVICE9 pDevice = Renderer::GetDevice();
		MainCamera->Update();
		D3DXMatrixLookAtLH(&MainCamera->m_MtxView, (D3DXVECTOR3*)&MainCamera->m_Eye, (D3DXVECTOR3*)&MainCamera->m_Lookat, (D3DXVECTOR3*)&MainCamera->m_VecUp);
		pDevice->SetTransform(D3DTS_VIEW, &MainCamera->m_MtxView);
	}	
}
