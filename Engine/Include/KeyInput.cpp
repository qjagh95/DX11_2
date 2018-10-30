#include "KeyInput.h"
#include "GameObject.h"
#include "Core.h"
#include "Device.h"
#include "CollsionManager.h"

#include "Component/Transform_Com.h"
#include "Component/Renderer_Com.h"
#include "Component/Material_Com.h"
#include "Component/Animation2D_Com.h"
#include "Component/Camera_Com.h"
#include "Component/ColliderPoint_Com.h"

#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

JEONG_USING
SINGLETON_VAR_INIT(KeyInput)

KeyInput::KeyInput()
	:m_NewKey(NULLPTR), m_MouseObject(NULLPTR), m_ShowCursor(false)
{
}

KeyInput::~KeyInput()
{
	SAFE_RELEASE(m_MouseWorldPoint);
	SAFE_RELEASE(m_MouseObject);
	Safe_Delete_Map(m_KeyMap);
}

bool KeyInput::Init()
{
	AddKey("MoveLeft", 'A');
	AddKey("MoveRight", 'D');
	AddKey("MoveUp", 'W');
	AddKey("MoveDown", 'S');
	AddKey("SystemPause", VK_F12);
	AddKey("LButton", VK_LBUTTON);
	AddKey("RButton", VK_RBUTTON);
	AddKey("MButton", VK_MBUTTON);

	m_MouseObject = GameObject::CreateObject("MouseObject");
	m_MouseObject->GetTransform()->SetWorldScale(Vector3(31.0f, 32.0f, 0.0f));
	m_MouseObject->GetTransform()->SetWorldPivot(Vector3(0.0f, 1.0f, 0.0f));

	Renderer_Com* MouseRender = m_MouseObject->AddComponent<Renderer_Com>("MouseRenderer");
	MouseRender->SetMesh("TextureRect");
	MouseRender->SetRenderState(ALPHA_BLEND);
	SAFE_RELEASE(MouseRender);

	Material_Com* MouseMeterial = m_MouseObject->FindComponentFromType<Material_Com>(CT_MATERIAL);
	MouseMeterial->SetDiffuseTexture(0, "Mouse", TEXT("Mouse/Default/0.png"));
	SAFE_RELEASE(MouseMeterial);

	ColliderPoint_Com* MouseWindowPoint = m_MouseObject->AddComponent<ColliderPoint_Com>("MouseWindow");
	MouseWindowPoint->SetCollisionGroup("UI");
	SAFE_RELEASE(MouseWindowPoint);

	m_MouseWorldPoint = m_MouseObject->AddComponent<ColliderPoint_Com>("MouseWorld");

	ShowCursor(FALSE);
	return true;
}

void KeyInput::Update(float DeltaTime)
{
	unordered_map<string, KeyInfo*>::iterator StartIter = m_KeyMap.begin();
	unordered_map<string, KeyInfo*>::iterator EndIter = m_KeyMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		size_t	iCount = 0;
		for (size_t i = 0; i < StartIter->second->vecKey.size(); ++i)
		{
			if (GetAsyncKeyState((int)StartIter->second->vecKey[i]) & 0x8000)
				++iCount;
		}

		if (iCount == StartIter->second->vecKey.size())
		{
			if (StartIter->second->KeyDown == false && StartIter->second->KeyPress == false)
			{
				StartIter->second->KeyDown = true;
				StartIter->second->KeyPress = true;
			}

			else if (StartIter->second->KeyDown == true)
				StartIter->second->KeyDown = false;
		}

		else if (StartIter->second->KeyPress == true)
		{
			StartIter->second->KeyUp = true;
			StartIter->second->KeyDown = false;
			StartIter->second->KeyPress = false;
		}

		else if (StartIter->second->KeyUp == true)
			StartIter->second->KeyUp = false;
	}

	POINT tempPos;
	RECT ScreenRect;

	GetClientRect(Core::Get()->GetHwnd(), &ScreenRect);
	GetCursorPos(&tempPos);
	ScreenToClient(Core::Get()->GetHwnd(), &tempPos);

	Vector2 DevicePos = Vector2((float)tempPos.x, (float)tempPos.y);

	//좌표계가 반대니까 빼준다.
	DevicePos.y = Device::Get()->GetWinSize().Height - DevicePos.y;

	DevicePos.x *= Device::Get()->GetWindowToDeviceRatio().x;
	DevicePos.y *= Device::Get()->GetWindowToDeviceRatio().y;

	m_MouseGap.x = DevicePos.x - m_MouseScreenPos.x;
	m_MouseGap.y = DevicePos.y - m_MouseScreenPos.y;

	m_MouseScreenPos.x = (float)DevicePos.x;
	m_MouseScreenPos.y = (float)DevicePos.y;

	//m_vMouseWorld = m_vMouseClient + GET_SINGLE(CCamera)->GetPos();

	m_MouseObject->GetTransform()->SetWorldPos((float)DevicePos.x, (float)DevicePos.y, 0.0f);

	m_MouseObject->Update(DeltaTime);

	if (m_ShowCursor == false && (m_MouseScreenPos.x <= 0.0f && m_MouseScreenPos.x >= Device::Get()->GetWinSize().Width || m_MouseScreenPos.y <= 0.0f && m_MouseScreenPos.y >= Device::Get()->GetWinSize().Height))
	{
		m_ShowCursor = true;
		while (ShowCursor(TRUE) != 0) {}
	}
	
	else if (m_ShowCursor == true && m_MouseScreenPos.x >= 0.0f && m_MouseScreenPos.x <= Device::Get()->GetWinSize().Width && m_MouseScreenPos.y >= 0.0f && m_MouseScreenPos.y <= Device::Get()->GetWinSize().Height)
	{
		m_ShowCursor = false;
		while (ShowCursor(FALSE) >= 0) {}
	}
}

void KeyInput::RenderMouse(float DeltaTime)
{
	m_MouseObject->Render(DeltaTime);
}

void KeyInput::ChangeMouseScene(Scene * pScene)
{
	m_MouseObject->SetScene(pScene);
}

void KeyInput::UpdateMousePos()
{
	m_MouseObject->LateUpdate(1.0f);

	Scene* pScene = SceneManager::Get()->GetCurScene();
	m_MouseWorldPoint->SetInfo(pScene->GetMainCameraTransform()->GetWorldPos());

	SAFE_RELEASE(pScene);
}

bool KeyInput::KeyDown(const string & Name)
{
	KeyInfo* getKey = FindKey(Name);

	if (getKey == NULLPTR)
		return false;

	return getKey->KeyDown;
}

bool KeyInput::KeyPress(const string & Name)
{
	KeyInfo* getKey = FindKey(Name);

	if (getKey == NULLPTR)
		return false;

	return getKey->KeyPress;
}

bool KeyInput::KeyUp(const string & Name)
{
	KeyInfo* getKey = FindKey(Name);

	if (getKey == NULLPTR)
		return false;

	return getKey->KeyUp;
}
   
KeyInfo* KeyInput::FindKey(const string& Name)
{
	unordered_map<string, KeyInfo*>::iterator FindIter = m_KeyMap.find(Name);

	if (FindIter == m_KeyMap.end())
		return NULLPTR;
	
	return FindIter->second;
}