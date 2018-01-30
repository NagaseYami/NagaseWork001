#pragma once
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1280)		// ウインドウの幅
#define SCREEN_HEIGHT	(720)		// ウインドウの高さ
#define SHADOWMAP_SIZE	(2048)
#define SAFE_RELEASE(x) { if(x) { (x) -> Release(); (x) = NULL; } } //セーフリリースマクロ
#define LOG(...) {char buf[256]; sprintf(buf, __VA_ARGS__); OutputDebugStringA(buf); }

//*****************************************************************************
// ヘッダファイル
//*****************************************************************************
#include <list>
#include <vector>
#include <map>
#include <array>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <time.h>
#include <windows.h>
#include <math.h>
#include "d3dx9.h"
#include "KMlib\KM_Math.h"
#include "KMlib\KM_Logic.h"
#include "input.h"
#include "imgui.h"


using namespace Kuma;
using namespace std;