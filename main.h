#pragma once
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)		// �E�C���h�E�̍���
#define SAFE_RELEASE(x) { if(x) { (x) -> Release(); (x) = NULL; } } //�Z�[�t�����[�X�}�N��

//*****************************************************************************
// �w�b�_�t�@�C��
//*****************************************************************************
#include <list>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <math.h>
#include "d3dx9.h"
#include "KMlib\KM_Math.h"
#include "KMlib\KM_Logic.h"
#include "input.h"


using namespace Kuma;
using namespace std;