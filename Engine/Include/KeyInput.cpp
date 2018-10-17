#include "KeyInput.h"
JEONG_USING

///////////////////////////////////////////////// INPUTDATA

bool KeyInput::InputData::AllKeyCheck()
{
	for (size_t i = 0; i < m_AllKey.size(); i++)
	{
		// 그 키코드가 눌리지 않았다면
		if (0 == GetAsyncKeyState(m_AllKey[i]))
		{
			return false;
		}
	}

	return true;
}

void KeyInput::InputData::Update()
{
	// 여기서 해줄일은
	// 키가 눌렸는지 눌리지 않았는지 체크부터 한다.
	bool KeyCheck = AllKeyCheck();

	if (true == KeyCheck)
	{
		// 키가 눌렸을때
		if (true == m_bUpStay)
		{
			m_bUp = false;
			m_bUpStay = false;
			m_bDown = true;
			m_bDownStay = true;
		}
		else if (false == m_bUpStay)
		{
			m_bUp = false;
			m_bUpStay = false;
			m_bDown = false;
			m_bDownStay = true;
		}

	}
	else if (false == KeyCheck)
	{
		// 키가 눌렸을때
		if (true == m_bDownStay)
		{
			PushTime = 0.0f;
			m_bUp = true;
			m_bUpStay = true;
			m_bDown = false;
			m_bDownStay = false;
		}
		else if (false == m_bDownStay)
		{
			m_bUp = false;
			m_bUpStay = true;
			m_bDown = false;
			m_bDownStay = false;
		}
	}
}

///////////////////////////////////////////////// MGR


KeyInput::KeyInput()
{
}


KeyInput::~KeyInput()
{
	unordered_map<string, InputData*>::iterator StartIter = m_MapInputData.begin();
	unordered_map<string, InputData*>::iterator EndIter = m_MapInputData.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if (NULLPTR != StartIter->second)
		{
			if (NULLPTR != StartIter->second)
			{
				delete StartIter->second;
				StartIter->second = NULLPTR;
			}
		}
	}

	m_MapInputData.clear();
}


void KeyInput::Update()
{
	unordered_map<string, InputData*>::iterator StartIter = m_MapInputData.begin();
	unordered_map<string, InputData*>::iterator EndIter = m_MapInputData.end();

	for (; StartIter != EndIter; StartIter++)
	{
		if (NULLPTR != StartIter->second)
		{
			StartIter->second->Update();
		}
	}
}

bool KeyInput::KeyUp(const string& Name)
{
	InputData* pData = FindKey(Name);

	if (NULLPTR == pData)
	{
		return false;
	}

	return pData->m_bUp;
}

bool KeyInput::KeyDown(const string& Name)
{
	InputData* pData = FindKey(Name);

	if (NULLPTR == pData)
		return false;

	return pData->m_bDown;
}

bool KeyInput::KeyPress(const string& Name)
{
	InputData* pData = FindKey(Name);

	if (NULLPTR == pData)
		return false;

	return pData->m_bDownStay;
}