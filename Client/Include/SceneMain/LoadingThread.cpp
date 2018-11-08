#include "ClientHeader.h"
#include "LoadingThread.h"
#include "MainScene.h"
#include "ThreadManager.h"
#include "Sync.h"

#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

LoadingThread::LoadingThread()
	:m_LoadingMaxCount(7), m_LoadingCount(0)
{
	ThreadManager::Get()->CritcalCreate("LoadingCritcal");
}

LoadingThread::~LoadingThread()
{
}

void LoadingThread::Run()
{
	SceneManager::Get()->CreateNextScene(false);
	SceneManager::Get()->AddSceneComponent<MainScene>("MainScene", false);
}

void LoadingThread::AddLoadingCount()
{
	CRITICAL_SECTION* getCri = ThreadManager::Get()->FindCritcal("LoadingCritcal");
	Sync sync = Sync(getCri);

	m_LoadingCount++;

	Sleep(100);
}

int LoadingThread::GetLoadingCount() const
{
	CRITICAL_SECTION* getCri = ThreadManager::Get()->FindCritcal("LoadingCritcal");
	Sync sync = Sync(getCri);

	return m_LoadingCount;
}

float LoadingThread::GetPersent() const
{
	CRITICAL_SECTION* getCri = ThreadManager::Get()->FindCritcal("LoadingCritcal");
	Sync sync = Sync(getCri);

	return (float)m_LoadingCount / (float)m_LoadingMaxCount;
}

