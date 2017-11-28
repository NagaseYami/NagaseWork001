#include "main.h"
#include "renderer.h"
#include "dxinput.h"
#include "texture.h"
#include "blur.h"
#include "object.h"
#include "manager.h"
#include "camera.h"
#include "includeallcameras.h"
#include "scene.h"
#include "includeallscenes.h"


void Manager::Init(HINSTANCE hInst, HWND hWnd)
{
	//Renderer
	Renderer::Init(hWnd);
	Blur::Init();
	//Camera
	Camera::SetMtxProjection();
	//Input
	Input::Init(hInst,hWnd);
	//Scene
#ifdef _DEBUG
	RenderTargetDemo *Scene1 = new RenderTargetDemo;
	Scene::ToNextScene(Scene1);
	
#endif // _DEBUG
}

void Manager::Uninit()
{
	Object::UninitAll();
	Texture::DestoryAllTexture();
	Blur::Uninit();
	Renderer::Uninit();
	DXInput::Uninit();
}

void Manager::Update()
{
	//Input
	Input::Update();
	//Scene
	Scene::UpdateMainScene();
	//Camera
	Camera::UpdateMainCamera();
	//Object
	Object::FixedUpdateAll();
	Object::UpdateAll();
	Object::LateUpdateAll();
	//Renderer	
	Renderer::Update();
}

void Manager::Draw()
{
	Texture::DrawAllRenderTargetTexture();
	Blur::DrawRenderTargetTexture();
	Renderer::DrawBackBufferBegin();
	Object::DrawAllBackBufferObject();
	Renderer::DrawBackBufferEnd();
	Blur::ChangeTexture();
}
