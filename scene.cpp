#include "main.h"
#include "object.h"
#include "scene.h"

Scene* Scene::ThisScene = nullptr;

void Scene::UpdateMainScene()
{
	if (ThisScene)
	{
		ThisScene->Update();
	}
}

void Scene::Uninit()
{
	Object::UninitAll();
	delete this;
}

void Scene::ToNextScene(Scene * nextscene)
{
	if (ThisScene)
	{
		ThisScene->Uninit();
	}	
	ThisScene = nextscene;
	ThisScene->Init();
}
