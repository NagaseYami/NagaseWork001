#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"

D3DXMATRIX Camera::m_MtxProj;
Camera * Camera::MainCamera = nullptr;

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
	D3DXMatrixOrthoLH(&mtxProj, SCREEN_WIDTH, SCREEN_HEIGHT, 0.1f, 1000.0f);
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProj);
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
