#pragma once
class Scene {
public:
	virtual void Init() = 0;
	static void UpdateMainScene();
	virtual void Update() = 0;
	virtual void Uninit();
	static void ToNextScene(Scene * nextscene);

	//Getter
	static Scene* GetThisScene() {
		return ThisScene;
	}
private:
	static Scene* ThisScene;
};