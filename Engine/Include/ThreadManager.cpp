#include "ThreadManager.h"

JEONG_USING
SINGLETON_VAR_INIT(ThreadManager)

ThreadManager::ThreadManager()
{
}

ThreadManager::~ThreadManager()
{
	Safe_Delete_Map(m_ThreadMap);
}

bool ThreadManager::Init()
{
	return true;
}

Thread * ThreadManager::FindThread(const string & ThreadName)
{
	unordered_map<string, Thread*>::iterator FindIter = m_ThreadMap.find(ThreadName);

	if (FindIter == m_ThreadMap.end())
		return NULLPTR;

	return FindIter->second;
}

bool ThreadManager::DeleteThread(const string & ThreadName)
{
	unordered_map<string, Thread*>::iterator FindIter = m_ThreadMap.find(ThreadName);

	if (FindIter == m_ThreadMap.end())
		return NULLPTR;

	SAFE_DELETE(FindIter->second);
	m_ThreadMap.erase(FindIter);

	return false;
}
