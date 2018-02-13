#pragma once
#include <gainput/gainput.h>
#include "../Main/main.h"
class Input {
public:
	enum USERBUTTON
	{
		KeyEscape, KeyF1, KeyF2, KeyF3,
		KeyF4, KeyF5, KeyF6, KeyF7,
		KeyF8, KeyF9, KeyF10, KeyF11,
		KeyF12, KeyF13, KeyF14, KeyF15,
		KeyF16, KeyF17, KeyF18, KeyF19,
		KeyPrint, KeyScrollLock, KeyBreak, KeySpace,
		KeyApostrophe, KeyComma, KeyMinus, KeyPeriod,
		KeySlash, Key0, Key1, Key2,
		Key3, Key4, Key5, Key6,
		Key7, Key8, Key9, KeySemicolon,
		KeyLess, KeyEqual, KeyA, KeyB,
		KeyC, KeyD, KeyE, KeyF,
		KeyG, KeyH, KeyI, KeyJ,
		KeyK, KeyL, KeyM, KeyN,
		KeyO, KeyP, KeyQ, KeyR,
		KeyS, KeyT, KeyU, KeyV,
		KeyW, KeyX, KeyY, KeyZ,
		KeyBracketLeft, KeyBackslash, KeyBracketRight, KeyGrave,
		KeyLeft, KeyRight, KeyUp, KeyDown,
		KeyInsert, KeyHome, KeyDelete, KeyEnd,
		KeyPageUp, KeyPageDown, KeyNumLock, KeyKpEqual,
		KeyKpDivide, KeyKpMultiply, KeyKpSubtract, KeyKpAdd,
		KeyKpEnter, KeyKpInsert, KeyKpEnd, KeyKpDown,
		KeyKpPageDown, KeyKpLeft, KeyKpBegin, KeyKpRight,
		KeyKpHome, KeyKpUp, KeyKpPageUp, KeyKpDelete,
		KeyBackSpace, KeyTab, KeyReturn, KeyCapsLock,
		KeyShiftL, KeyCtrlL, KeySuperL, KeyAltL,
		KeyAltR, KeySuperR, KeyMenu, KeyCtrlR,
		KeyShiftR, KeyBack, KeySoftLeft, KeySoftRight,
		KeyCall, KeyEndcall, KeyStar, KeyPound,
		KeyDpadCenter, KeyVolumeUp, KeyVolumeDown, KeyPower,
		KeyCamera, KeyClear, KeySymbol, KeyExplorer,
		KeyEnvelope, KeyEquals, KeyAt, KeyHeadsethook,
		KeyFocus, KeyPlus, KeyNotification, KeySearch,
		KeyMediaPlayPause, KeyMediaStop, KeyMediaNext, KeyMediaPrevious,
		KeyMediaRewind, KeyMediaFastForward, KeyMute, KeyPictsymbols,
		KeySwitchCharset, KeyForward, KeyExtra1, KeyExtra2,
		KeyExtra3, KeyExtra4, KeyExtra5, KeyExtra6,
		KeyFn, KeyCircumflex, KeySsharp, KeyAcute,
		KeyAltGr, KeyNumbersign, KeyUdiaeresis, KeyAdiaeresis,
		KeyOdiaeresis, KeySection, KeyAring, KeyDiaeresis,
		KeyTwosuperior, KeyRightParenthesis, KeyDollar, KeyUgrave,
		KeyAsterisk, KeyColon, KeyExclam, KeyBraceLeft,
		KeyBraceRight, KeySysRq, 

		MouseButton0, MouseButtonLeft = MouseButton0, MouseButton1, MouseButtonMiddle = MouseButton1,
		MouseButton2, MouseButtonRight = MouseButton2, MouseButton3, MouseButtonWheelUp = MouseButton3,
		MouseButton4, MouseButtonWheelDown = MouseButton4, MouseButton5, MouseButton6,
		MouseButton7, MouseButton8, MouseButton9, MouseButton10,
		MouseButton11, MouseButton12, MouseButton13, MouseButton14,
		MouseButton15, MouseButton16, MouseButton17, MouseButton18,
		MouseButton19, MouseButton20, MouseButtonMax = MouseButton20, MouseButtonCount,
		MouseAxisX = MouseButtonCount, MouseAxisY,

		PadButtonLeftStickX, PadButtonLeftStickY, PadButtonRightStickX, PadButtonRightStickY,
		PadButtonAxis4, PadButtonAxis5, PadButtonAxis6, PadButtonAxis7,
		PadButtonAxis8, PadButtonAxis9, PadButtonAxis10, PadButtonAxis11,
		PadButtonAxis12, PadButtonAxis13, PadButtonAxis14, PadButtonAxis15,
		PadButtonAxis16, PadButtonAxis17, PadButtonAxis18, PadButtonAxis19,
		PadButtonAxis20, PadButtonAxis21, PadButtonAxis22, PadButtonAxis23,
		PadButtonAxis24, PadButtonAxis25, PadButtonAxis26, PadButtonAxis27,
		PadButtonAxis28, PadButtonAxis29, PadButtonAxis30, PadButtonAxis31,
		PadButtonAccelerationX, PadButtonAccelerationY, PadButtonAccelerationZ, PadButtonGravityX,
		PadButtonGravityY, PadButtonGravityZ, PadButtonGyroscopeX, PadButtonGyroscopeY,
		PadButtonGyroscopeZ, PadButtonMagneticFieldX, PadButtonMagneticFieldY, PadButtonMagneticFieldZ,
		PadButtonStart, PadButtonAxisCount_ = PadButtonStart, PadButtonSelect, PadButtonLeft,
		PadButtonRight, PadButtonUp, PadButtonDown, PadButtonA,
		PadButtonB, PadButtonX, PadButtonY, PadButtonL1,
		PadButtonR1, PadButtonL2, PadButtonR2, PadButtonL3,
		PadButtonR3, PadButtonHome, PadButton17, PadButton18,
		PadButton19, PadButton20, PadButton21, PadButton22,
		PadButton23, PadButton24, PadButton25, PadButton26,
		PadButton27, PadButton28, PadButton29, PadButton30,
		PadButton31
	};
	static void Init(HINSTANCE hInst, HWND hWnd);
	static void Update();
	static void Uninit();
	static void HandleMessage(MSG msg);

	static bool IsPress(USERBUTTON key);
	static bool IsDown(USERBUTTON key);
	static bool IsRelease(USERBUTTON key);

	static float GetAxis(USERBUTTON mouse);//return 0.0f~1.0f
	static float GetAxisDelta(USERBUTTON mouse);
	
private:
	static gainput::InputManager manager;
	static gainput::DeviceId mouseId;
	static gainput::DeviceId keyboardId;
	static gainput::InputMap map;
};