#pragma once
class Light{
public:
	static int CreateLight(D3DLIGHT9 dxlight, int number = 99);
	static void ReleaseLight(int number);

private:
	static Light * m_Manager[10];
	D3DLIGHT9 m_LightDX;
	int m_ID;
};