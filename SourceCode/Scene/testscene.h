#pragma once
#include "../Camera/tpscamera.h"
#include "scene.h"
class TestScene :public Scene {
public:
	void Init();
	void Update();
	void Uninit();
private:
	TPSCamera m_Camera;
};
