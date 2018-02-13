#pragma once
#include "../Main/main.h"
class Effect {
public:
	static LPD3DXEFFECT LoadEffectFromFile(string filename);
	//static void DrawEffectBegin();
private:
	static map<string,LPD3DXEFFECT> m_Manager;
};