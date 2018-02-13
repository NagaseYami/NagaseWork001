#pragma once
#include "../Main/main.h"
#include "camera.h"
class TPSCamera :public Camera {
public:
	void Update();
private:
	Vector3 m_TargetEye = Vector3(0.0f, 0.0f, 0.0f);
	float F = 0.0f;
	float x = 0.0f;
	float v = 0.0f;
};