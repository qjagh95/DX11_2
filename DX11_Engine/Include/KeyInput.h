#pragma once
#include "stdafx.h"
JEONG_BEGIN

struct JEONG_DLL KeyInfo
{
	string KeyName;
	vector<DWORD> vecKey;
	bool KeyDown;
	bool KeyPress;
	bool KeyUp;
};

class GameObject;
class Scene;
class JEONG_DLL KeyInput
{
public:
	bool Init();
	void Update(float DeltaTime);
	void RenderMouse(float DeltaTime);
	bool KeyDown(const string& Name);
	bool KeyPress(const string& Name);
	bool KeyUp(const string& Name);

	Vector2 GetMouseScreenPos() const { return m_MouseScreenPos; }
	Vector2 GetMouseWorldPos() const { return m_MouseWorldPos; }
	Vector2 GetMouseGap() const { return m_MouseGap; }
	void ChangeMouseScene(Scene* pScene);

	template <typename T>
	bool AddKey(const T& value)
	{
		if (m_NewKey == NULLPTR)
		{
			m_NewKey = new KeyInfo();
			m_NewKey->KeyDown = false;
			m_NewKey->KeyPress = false;
			m_NewKey->KeyUp = false;
		}

		//Ÿ���̸� ������.
		const char* typeName = typeid(T).name();

		if (strcmp(typeName, "int") == 0 || strcmp(typeName, "char") == 0)
		{
			m_NewKey->vecKey.push_back((DWORD&)value);
		}
		else
		{
			m_NewKey->KeyName = value;
			m_KeyMap.insert(make_pair(m_NewKey->KeyName, m_NewKey));
		}

		return true;
	}

	template <typename T, typename ... Types>
	bool AddKey(const T& value, Types ... Args)
	{
		if (m_NewKey == NULLPTR)
		{
			m_NewKey = new KeyInfo();
			m_NewKey->KeyDown = false;
			m_NewKey->KeyPress = false;
			m_NewKey->KeyUp = false;
		}

		//Ÿ���̸� ������.
		const char* typeName = typeid(T).name();

		if (strcmp(typeName, "int") == 0 || strcmp(typeName, "char") == 0)
		{
			m_NewKey->vecKey.push_back((DWORD&)value);
		}
		else
		{
			m_NewKey->KeyName = value;
			m_KeyMap.insert(make_pair(m_NewKey->KeyName, m_NewKey));
		}

		AddKey(Args...);

		if (m_NewKey != NULLPTR)
			m_NewKey = NULLPTR;

		return true;
	}

private:
	KeyInfo* FindKey(const string& Name);

private:
	unordered_map<string, KeyInfo*> m_KeyMap;
	KeyInfo* m_NewKey;
	Vector2 m_MouseScreenPos;	//ȭ����� ��ǥ (0 ~ 1280, 0 ~ 720)
	Vector2 m_MouseWorldPos;	//ȭ�鳻�� ��ǥ
	Vector2 m_MouseGap;			//ȭ��� ��ǥ�� ȭ�� ���� ��ǥ�� ����
	GameObject* m_MouseObject;
	bool m_ShowCursor;

public:
	CLASS_IN_SINGLE(KeyInput)
};

JEONG_END


