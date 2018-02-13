#pragma once
#include <dinput.h>
class DXInput {
public:
	static HRESULT Init(HINSTANCE hInst, HWND hWnd);
	static void Uninit(void);
	static void Update(void);

	static DIMOUSESTATE2 * GetMouseState();
	static BOOL GetMousePress(int nKey);
	static BOOL GetMouseDown(int nKey);
	static BOOL GetMouseRelease(int nKey);
private:
	static LPDIRECTINPUT8 m_pDInput;
	static LPDIRECTINPUTDEVICE8 m_pDIDevice;
	static DIMOUSESTATE2 m_pMouseState;
	static bool m_MouseTrigger;
};