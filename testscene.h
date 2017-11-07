#pragma once
#ifdef _DEBUG
class TestScene :public Scene {
public:
	void Init();
	void Update();
	void Uninit();
};
#endif