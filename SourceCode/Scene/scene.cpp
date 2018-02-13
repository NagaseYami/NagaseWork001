#include "../Object/object.h"
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
		delete ThisScene;
		ThisScene = nullptr;
	}	
	ThisScene = nextscene;
	ThisScene->Init();
}
