#include "main.h"
#include "renderer.h"
#include "dxinput.h"
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
	//Camera
	Camera::SetMtxProjection();
	//Input
	Input::Init(hInst,hWnd);
	//Scene
#ifdef _DEBUG
	TestScene *Scene1 = new TestScene;
	Scene::ToNextScene(Scene1);
#endif // _DEBUG
}

void Manager::Uninit()
{
	Object::UninitAll();
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
	Renderer::DrawBegin();
	Object::DrawAll();
	Renderer::DrawEnd();
}
