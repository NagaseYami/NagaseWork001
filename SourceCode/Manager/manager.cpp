#include "../Blur/blur.h"
#include "../Imgui/imgui_impl_dx9.h"
#include "../Input/dxinput.h"
#include "../Object/object.h"
#include "../Renderer/renderer.h"
#include "../Scene/testscene.h"
#include "../Texture/texture.h"
#include "manager.h"

void Manager::Init(HINSTANCE hInst, HWND hWnd)
{
	//Renderer
	Renderer::Init(hWnd);
	Blur::Init();
	//ImGui
	ImGui_ImplDX9_Init(hWnd,Renderer::GetDevice());
	//Camera
	Camera::SetPerspectiveMtxProjection();
	//Input
	Input::Init(hInst,hWnd);
	//ShadowMap
	Texture::CreateEmptyTexture("ShadowMap", Vector2(SHADOWMAP_SIZE, SHADOWMAP_SIZE), Texture::SHADOWMAP, D3DFMT_R32F);
	//Scene
	TestScene *Scene = new TestScene;
	Scene::ToNextScene(Scene);

}

void Manager::Uninit()
{
	Object::UninitAll();
	Texture::DestoryAllTexture();
	Blur::Uninit();
	ImGui_ImplDX9_Shutdown();
	Renderer::Uninit();
	DXInput::Uninit();	
}

void Manager::Update()
{
	//ImGui
	ImGui_ImplDX9_NewFrame();
#ifdef _DEBUG
	ImGui::Begin("FPS",nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize);
	ImGui::Text("%.3f ms (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
#endif // _DEBUG

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
	ImGui::Render();
	Renderer::DrawBackBufferEnd();
	//bBlur::ChangeTexture();

	Object::UninitNotBeingUsedObject();
}
