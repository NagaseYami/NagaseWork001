#pragma once
class RenderTargetDemo :public Scene {
public:
	void Init();
	void Update();
	void Uninit();
private:
	TPSCamera m_Camera;
};