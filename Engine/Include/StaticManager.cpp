#include "stdafx.h"
#include "StaticManager.h"

JEONG_USING
SINGLETON_VAR_INIT(StaticManager)

StaticManager::StaticManager()
{
}

StaticManager::~StaticManager()
{
	Safe_Release_VecList(m_staticObjectList);
}

bool StaticManager::Init()
{
	return true;
}

void StaticManager::AddStaticObject(GameObject * object)
{
	list<GameObject*>::iterator	StartIter = m_staticObjectList.begin();
	list<GameObject*>::iterator	EndIter = m_staticObjectList.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (object == *StartIter)
			return;
	}

	object->AddRefCount();
	m_staticObjectList.push_back(object);
}

void StaticManager::ChangeScene(Scene * scene)
{
	list<GameObject*>::iterator	StartIter = m_staticObjectList.begin();
	list<GameObject*>::iterator	EndIter = m_staticObjectList.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		Layer* pLayer = scene->FindLayer((*StartIter)->GetLayerName());

		if (pLayer != NULLPTR)
		{
			scene->AddLayer((*StartIter)->GetLayerName(), (*StartIter)->GetLayerZOrder());
			pLayer = scene->FindLayer((*StartIter)->GetLayerName());
		}

		pLayer->AddObject(*StartIter);

		SAFE_RELEASE(pLayer);
	}
}

bool StaticManager::CheckStaticObject(const string & TagName)
{
	list<GameObject*>::iterator	StartIter = m_staticObjectList.begin();
	list<GameObject*>::iterator	EndIter = m_staticObjectList.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (TagName == (*StartIter)->GetTag())
			return true;
	}

	return false;
}

GameObject * StaticManager::FindStaticObject(const string & TagName)
{
	list<GameObject*>::iterator	StartIter = m_staticObjectList.begin();
	list<GameObject*>::iterator	EndIter = m_staticObjectList.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (TagName == (*StartIter)->GetTag())
		{
			(*StartIter)->AddRefCount();
			return *StartIter;
		}
	}
	return NULLPTR;
}
