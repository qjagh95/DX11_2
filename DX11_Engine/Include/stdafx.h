#pragma once

#include <Windows.h>
#include <list>
#include <vector>
#include <unordered_map>
#include <string>
#include <crtdbg.h>
#include <conio.h>
#include <assert.h>
#include <array>
#include <thread>
#include <mutex>
#include <iostream>
#include <algorithm>

//DX11부터는 포함디렉터리 라이브러리 디렉터리 추가없이 바로 헤더추가가 가능하다.
//이전에는 프로젝트 템플릿(VS기능)을 이용하여 프로젝트를 먼저 만들어놓고 추가해서 사용했다.
#include <d3d11.h>
#include <d3dcompiler.h> //shader를 컴파일하는 기능을 제공한다.

//DirectX11에서 제공하는 수학 기능을 사용하기위함
#include <DirectXMath.h>
#include <DirectXPackedVector.h> //제공되는 벡터들을 사용하기위함
#include <DXGIDebug.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma warning(disable:4099)

#include "Type.h"
#include "Macro.h"
#include "Flag.h"

#define TrueAssert(Var) assert(!(Var))
#define new new(_CLIENT_BLOCK,__FILE__,__LINE__)