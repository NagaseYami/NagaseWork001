#include "main.h"
#include "dxinput.h"

#define MAPMOUSE(x) {map.MapBool(x,mouseId,gainput::x);}
#define MAPMOUSEAXIS(x){map.MapFloat(x,mouseId,gainput::x);}
#define MAPKEYBOARD(x) {map.MapBool(x,keyboardId,gainput::x);}


gainput::InputManager Input::manager;
gainput::DeviceId Input::mouseId = manager.CreateDevice<gainput::InputDeviceMouse>();
gainput::DeviceId Input::keyboardId = manager.CreateDevice<gainput::InputDeviceKeyboard>();
gainput::InputMap Input::map(manager);

void Input::Init(HINSTANCE hInst, HWND hWnd)
{
	DXInput::Init(hInst, hWnd);

	manager.SetDisplaySize(SCREEN_WIDTH,SCREEN_HEIGHT);
	//Mouse Mapping
	MAPMOUSE(MouseButtonLeft);
	MAPMOUSE(MouseButtonRight);
	MAPMOUSE(MouseButtonMiddle);
	MAPMOUSE(MouseButtonWheelUp);
	MAPMOUSE(MouseButtonWheelDown);
	MAPMOUSEAXIS(MouseAxisX);
	MAPMOUSEAXIS(MouseAxisY);
	//KeyBoard Mapping
	MAPKEYBOARD(KeySpace);
	MAPKEYBOARD(KeyW);
	MAPKEYBOARD(KeyS);
	MAPKEYBOARD(KeyA);
	MAPKEYBOARD(KeyD);
}

void Input::Update()
{
	DXInput::Update();
	manager.Update();
}

void Input::Uninit()
{
	DXInput::Uninit();
}

void Input::HandleMessage(MSG msg)
{
	manager.HandleMessage(msg);
}

bool Input::IsPress(USERBUTTON key)
{
	return map.GetBool(key);
}

bool Input::IsDown(USERBUTTON key)
{
	return map.GetBoolIsNew(key);
}

bool Input::IsRelease(USERBUTTON key)
{
	return map.GetBoolWasDown(key);
}

float Input::GetAxis(USERBUTTON mouse)
{
	return map.GetFloat(mouse);
}

float Input::GetAxisDelta(USERBUTTON mouse)
{
	return map.GetFloatDelta(mouse);
}
