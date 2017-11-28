#include "main.h"

#include "dxinput.h"

LPDIRECTINPUT8 DXInput::m_pDInput;
LPDIRECTINPUTDEVICE8 DXInput::m_pDIDevice;
DIMOUSESTATE2 DXInput::m_pMouseState;
bool DXInput::m_MouseTrigger = false;

HRESULT DXInput::Init(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr = S_FALSE;

	// DirectInputオブジェクトの作成
	if (!m_pDInput)
	{
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_pDInput, NULL);
	}

	hr = m_pDInput->CreateDevice(GUID_SysMouse, &m_pDIDevice, NULL);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "マウスのデバイスが存在しません。", "ERROR form input.cpp", MB_ICONWARNING);
		return hr;
	}

	hr = m_pDIDevice->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "マウスのデータフォーマットを設定できませんでした。", "ERROR form input.cpp", MB_ICONWARNING);
		return hr;
	}

	hr = m_pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(hWnd, "マウスの協調モードを設定できませんでした。", "ERROR form input.cpp", MB_ICONWARNING);
		return hr;
	}


	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = DIPROPAXISMODE_REL;

	hr = m_pDIDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);

	// m_pDIDeviceアクセス権を獲得(入力制御開始)
	hr = m_pDIDevice->Acquire();

	return S_OK;
}

void DXInput::Uninit(void)
{
	if (m_pDIDevice)
	{// デバイスオブジェクトの開放
		m_pDIDevice->Unacquire();
		m_pDIDevice->Release();
		m_pDIDevice = NULL;
	}

	if (m_pDInput)
	{// DirectInputオブジェクトの開放
		m_pDInput->Release();
		m_pDInput = NULL;
	}
}

void DXInput::Update(void)
{
	if (!m_pDIDevice) {
		return;
	}

	// 読取前の値を保持します
	DIMOUSESTATE2 m_pMouseState_bak;	// マウス情報(変化検知用)
	memcpy(&m_pMouseState_bak, &m_pMouseState, sizeof(m_pMouseState_bak));

	// ここから、DirectInputで必要なコード -->
	// マウスの状態を取得します
	HRESULT	hr = m_pDIDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &m_pMouseState);
	if (FAILED(hr)) {
		hr = m_pDIDevice->Acquire();
		hr = m_pDIDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &m_pMouseState);
	}
}

DIMOUSESTATE2 * DXInput::GetMouseState(void)
{
	return &m_pMouseState;;
}

BOOL DXInput::GetMousePress(int nKey)
{
	if (m_pMouseState.rgbButtons[nKey] & 0x80) { return true; }
	return false;
}

BOOL DXInput::GetMouseDown(int nKey)
{
	if ((!m_MouseTrigger) && (m_pMouseState.rgbButtons[nKey] & 0x80)) {
		m_MouseTrigger = true;
		return true;
	}
	return false;
}

BOOL DXInput::GetMouseRelease(int nKey)
{
	if ((m_MouseTrigger) && !(m_pMouseState.rgbButtons[nKey] & 0x80)) {
		m_MouseTrigger = false;
		return true;
	}
	return false;
}
