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
#include <fstream>
#include <sstream>
#include <algorithm>
#include <atlstr.h>
#include <process.h>

#include <MathHeader.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix.h>

//DX11���ʹ� ���Ե��͸� ���̺귯�� ���͸� �߰����� �ٷ� ����߰��� �����ϴ�.
//�������� ������Ʈ ���ø�(VS���)�� �̿��Ͽ� ������Ʈ�� ���� �������� �߰��ؼ� ����ߴ�.
#include <d3d11.h>
#include <d3dcompiler.h> //shader�� �������ϴ� ����� �����Ѵ�.
#include <d2d1.h>
#include <dwrite.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
//DWrite
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")
#pragma warning(disable:4099)

#include "Macro.h"
#include "Flag.h"
#include "Type.h"

#define TrueAssert(Var) assert(!(Var))
#define new new(_CLIENT_BLOCK,__FILE__,__LINE__)