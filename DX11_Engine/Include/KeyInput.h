#pragma once
#include "stdafx.h"
JEONG_BEGIN

class JEONG_DLL KeyInput
{
public:
	static KeyInput& Get()
	{
		static KeyInput Inst = KeyInput();
		return Inst;
	}

private:
	class InputData
	{
	private:
		friend KeyInput;

	private:
		std::vector<int> m_AllKey;
		bool m_bUp; // �� �Ѽ���
		bool m_bUpStay; // ��� ���� �־���. 
		bool m_bDown; // ó�� ���� �Ѽ���
		bool m_bDownStay; // ��� ������ ������.
		float PushTime;

	private:
		template<typename... Rest>
		void PushKeyData(const int _Value, Rest ... _Arg)
		{
			m_AllKey.push_back(_Value);
			PushKeyData(_Arg...);
		}

		// �̳༮ ������ ������.
		void PushKeyData()
		{
		}

	public:
		// Ű�� üũ�ϴ� �ܰ�
		void Update();
		bool AllKeyCheck();

	public:
		InputData(size_t _Count) : m_bUpStay(true), m_bUp(false), m_bDown(false), m_bDownStay(false)
		{
			m_AllKey.reserve(_Count);
		}
		~InputData() {}

	private:
		friend class Core;
	};

private:
	unordered_map<string, InputData*> m_MapInputData;

private:
	InputData* FindKey(const string& Name)
	{
		unordered_map<string, InputData*>::iterator FindIter = m_MapInputData.find(Name);

		if (FindIter == m_MapInputData.end())
			return NULLPTR;

		return FindIter->second;
	}

public:
	template<typename ... Rest>
	bool CreateKey(const string& Name, Rest... _Arg)
	{
		InputData* pNewKey = FindKey(Name);

		if (nullptr != pNewKey)
		{
			TrueAssert(true);
			return false;
		}

		pNewKey = new InputData(sizeof...(_Arg));
		pNewKey->PushKeyData(_Arg...);
		m_MapInputData.insert(make_pair(Name, pNewKey));

		return true;
	}

private:
	void Update();

public:
	bool KeyUp(const string& Name);
	bool KeyDown(const string& Name);
	bool KeyPress(const string& Name);

public:
	KeyInput();
	~KeyInput();

public:
	friend class Core;
};

JEONG_END


