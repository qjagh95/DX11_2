#include "ClientHeader.h"
#include "StaticTestScene.h"
#include "MainScene.h"

StaticTestScene::StaticTestScene()
{
}

StaticTestScene::~StaticTestScene()
{
}

bool StaticTestScene::Init()
{
	return true;
}

int StaticTestScene::Input(float DeltaTime)
{
	return 0;
}

int StaticTestScene::Update(float DeltaTime)
{
	if (GetAsyncKeyState(VK_NEXT) & 0x8000)
	{
		SceneManager::Get()->CreateNextScene();
		SceneManager::Get()->AddSceneComponent<MainScene>("MainScene", false);
	}

	return 0;
}

int StaticTestScene::LateUpdate(float DeltaTime)
{
	return 0;
}

void StaticTestScene::Collision(float DeltaTime)
{
}

void StaticTestScene::CollisionLateUpdate(float DeltaTime)
{
}

void StaticTestScene::Render(float DeltaTime)
{
}
