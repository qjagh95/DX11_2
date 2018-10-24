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

//DX11���ʹ� ���Ե��͸� ���̺귯�� ���͸� �߰����� �ٷ� ����߰��� �����ϴ�.
//�������� ������Ʈ ���ø�(VS���)�� �̿��Ͽ� ������Ʈ�� ���� �������� �߰��ؼ� ����ߴ�.
#include <d3d11.h>
#include <d3dcompiler.h> //shader�� �������ϴ� ����� �����Ѵ�.

//DirectX11���� �����ϴ� ���� ����� ����ϱ�����
#include <DirectXMath.h>
#include <DirectXPackedVector.h> //�����Ǵ� ���͵��� ����ϱ�����
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