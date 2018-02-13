#pragma once
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1600)		// ウインドウの幅
#define SCREEN_HEIGHT	(900)		// ウインドウの高さ
#define SHADOWMAP_SIZE	(2048)
#define SAFE_RELEASE(x) { if(x) { (x) -> Release(); (x) = NULL; } } //セーフリリースマクロ
#define LOG(...) {char buf[256]; sprintf(buf, __VA_ARGS__); OutputDebugStringA(buf); }

//*****************************************************************************
// ヘッダファイル
//*****************************************************************************
#include <algorithm>
#include <array>
#include <d3dx9.h>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <math.h>
#include <string>
#include <time.h>
#include <vector>
#include <Windows.h>
#include "../Imgui/imgui.h"
#include "../Input/input.h"
#include "../KMlib/KM_Math.h"

using namespace Kuma;
using namespace std;