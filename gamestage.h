#pragma once
class ObjectXModel;
class GameStage : public Scene {
public:
	void Init();
	void Update();
	void Uninit();
private:
	ObjectXModel * m_pQuarter[4];
	TPSCamera m_Camera;	
};