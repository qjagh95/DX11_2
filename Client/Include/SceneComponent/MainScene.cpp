#include "MainScene.h"
#include "GameObject.h"

#include "Scene/Scene.h"
#include "scene/Layer.h"

#include "Component/Component_Base.h"
#include "Component/Transform_Com.h"
#include "Component/Renderer_Com.h"
#include "Component/Camera_Com.h"

#include "../UserComponent/Player_Com.h"
#include "../UserComponent/Bullet_Com.h"
#include "../UserComponent/BulletRot_Com.h"
#include "../UserComponent/BulletBoom_Com.h"

#include "../UserComponent/Monster_Com.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

bool MainScene::Init()
{
	Camera_Com* mainCamera = m_Scene->GetMainCamera();
	mainCamera->SetCameraType(CT_ORTHO);
	mainCamera->SetNear(0.0f);

	Layer* Default = m_Scene->FindLayer("Default");

	GameObject* PlayerObject = GameObject::CreateObject("Player", Default);
	Player_Com* player_Com = PlayerObject->AddComponent<Player_Com>("Player_Com");

	GameObject* BulletObject = GameObject::CreateProtoType("Bullet_Clone");
	Bullet_Com* bullet_Com = BulletObject->AddComponent<Bullet_Com>("Bullet_Com");

	GameObject* BulletObject2 = GameObject::CreateProtoType("BulletRot_Clone");
	BulletRot_Com* bullet_Com2 = BulletObject2->AddComponent<BulletRot_Com>("BulletRot_Com");

	GameObject* MonsterObject = GameObject::CreateObject("Monster", Default);
	Monster_Com* monster_Com = MonsterObject->AddComponent<Monster_Com>("Monster_Com");

	GameObject* BoomObject = GameObject::CreateProtoType("Boom", Default);
	BulletBoom_Com* bulletBoom_Com = BoomObject->AddComponent<BulletBoom_Com>("Boom_Com");

	SAFE_RELEASE(BoomObject);
	SAFE_RELEASE(bulletBoom_Com);
	SAFE_RELEASE(BulletObject2);
	SAFE_RELEASE(bullet_Com2);
	SAFE_RELEASE(MonsterObject);
	SAFE_RELEASE(monster_Com);
	SAFE_RELEASE(bullet_Com);
	SAFE_RELEASE(BulletObject);
	SAFE_RELEASE(player_Com);
	SAFE_RELEASE(PlayerObject);
	SAFE_RELEASE(Default);

	return true;
}

int MainScene::Input(float DeltaTime)
{
	return 0;
}

int MainScene::Update(float DeltaTime)
{
	return 0;
}

int MainScene::LateUpdate(float DeltaTime)
{
	return 0;
}

void MainScene::Collision(float DeltaTime)
{
}

void MainScene::CollisionLateUpdate(float DeltaTime)
{
}

void MainScene::Render(float DeltaTime)
{
}