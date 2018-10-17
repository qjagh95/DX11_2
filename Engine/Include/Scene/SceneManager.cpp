#include "SceneManager.h"
#include "Scene.h"
JEONG_USING
SINGLETON_VAR_INIT(SceneManager)

SceneManager::SceneManager()
	:m_CurScene(NULLPTR), m_NextScene(NULLPTR)
{
}


SceneManager::~SceneManager()
{
	SAFE_RELEASE(m_CurScene);
	SAFE_RELEASE(m_NextScene);
}

bool SceneManager::Init()
{
	m_CurScene = new Scene();

	if (m_CurScene->Init() == false)
		return false;

	return true;
}

int SceneManager::Input(float DeltaTime)
{
	m_CurScene->Input(DeltaTime);
	return 0;
}

int SceneManager::Update(float DeltaTime)
{
	m_CurScene->Update(DeltaTime);
	return 0;
}

int SceneManager::LateUpdate(float DeltaTime)
{
	m_CurScene->LateUpdate(DeltaTime);
	return 0;
}

void SceneManager::Collision(float DeltaTime)
{
	m_CurScene->Collision(DeltaTime);
}

void SceneManager::CollsionLateUpdate(float DeltaTime)
{
	m_CurScene->CollisionLateUpdate(DeltaTime);
}

void SceneManager::Render(float DeltaTime)
{
	m_CurScene->Render(DeltaTime);
}

Scene * SceneManager::GetCurScene() const
{
	m_CurScene->AddRefCount();

	return m_CurScene;
}

Scene * SceneManager::GetNextScene() const
{
	m_NextScene->AddRefCount();

	return m_NextScene;
}

void SceneManager::AddLayer(const string & TagName, int ZOrder, bool isCurrent)
{
	if (isCurrent == true)
		m_CurScene->AddLayer(TagName, ZOrder);
	else
		m_NextScene->AddLayer(TagName, ZOrder);
}

void SceneManager::ChangeLayerZOrder(const string & TagName, int ZOrder, bool isCurrent)
{
	if (isCurrent == true)
		m_CurScene->ChangeLayerZOrder(TagName, ZOrder);
	else
		m_NextScene->ChangeLayerZOrder(TagName, ZOrder);
}

Layer * SceneManager::FindLayer(const string & TagName, bool isCurrent)
{
	if (isCurrent == true)
		return m_CurScene->FindLayer(TagName);
	else
		return m_NextScene->FindLayer(TagName);
}

GameObject * SceneManager::FindObject(const string & TagName)
{
	return m_CurScene->FindObject(TagName);
}
