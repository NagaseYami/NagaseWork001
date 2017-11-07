#include "main.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"

#include "includeallscenes.h"


void Manager::Init(HINSTANCE hInst, HWND hWnd)
{
	//Renderer
	Renderer::Init(hWnd);
	//Input	
	Input::Init();
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
}

void Manager::Update()
{
	//Input
	Input::Update();
	//Scene
	Scene::UpdateThis();
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
