#pragma once
#include "../Camera/tpscamera.h"
#include "scene.h"
class ObjectXModel;
class Boss;

class GameStage : public Scene {
public:
	void Init();
	void Update();
	void Uninit();
private:
	ObjectXModel * m_pQuarter[4];
	TPSCamera m_Camera;	
	Boss * m_pBoss;
};