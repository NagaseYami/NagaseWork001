#include "main.h"

#define MAPMOUSE(x) {map.MapBool(x,mouseId,gainput::x);}
#define MAPKEYBOARD(x) {map.MapBool(x,keyboardId,gainput::x);}


gainput::InputManager Input::manager;
gainput::DeviceId Input::mouseId = manager.CreateDevice<gainput::InputDeviceMouse>();
gainput::DeviceId Input::keyboardId = manager.CreateDevice<gainput::InputDeviceKeyboard>();
gainput::InputMap Input::map(manager);

void Input::Init()
{
	manager.SetDisplaySize(SCREEN_WIDTH,SCREEN_HEIGHT);
	MAPKEYBOARD(KeySpace);
}

void Input::Update()
{
	manager.Update();
}

void Input::HandleMessage(MSG msg)
{
	manager.HandleMessage(msg);
}

bool Input::GetKeyPress(KEYBOARD key)
{
	return map.GetBool(key);
}

bool Input::GetKeyDown(KEYBOARD key)
{
	return map.GetBoolIsNew(key);
}

bool Input::GetKeyRelease(KEYBOARD key)
{
	return map.GetBoolWasDown(key);
}
