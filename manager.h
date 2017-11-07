#pragma once
class Manager 
{
public:
	static void Init(HINSTANCE hInst, HWND hWnd);
	static void Uninit();
	static void Update();
	static void Draw();
};