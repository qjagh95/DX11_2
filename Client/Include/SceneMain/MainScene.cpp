#include "MainScene.h"
#include "StartScene.h"
#include "GameObject.h"

#include "Scene/Scene.h"
#include "scene/Layer.h"

#include "Component/Component_Base.h"
#include "Component/Transform_Com.h"
#include "Component/Renderer_Com.h"
#include "Component/Camera_Com.h"
#include "Component/ColliderPixel_Com.h"
#include "Component/Material_Com.h"
#include "Component/Button_Com.h"

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
	Layer* UILayer = m_Scene->FindLayer("UI");

	GameObject* MonsterObject = GameObject::CreateObject("Monster", Default);
	Monster_Com* monster_Com = MonsterObject->AddComponent<Monster_Com>("Monster_Com");

	GameObject* PlayerObject = GameObject::CreateObject("Player", Default);
	Player_Com* player_Com = PlayerObject->AddComponent<Player_Com>("Player_Com");

	GameObject* BulletObject = GameObject::CreateProtoType("Bullet_Clone");
	Bullet_Com* bullet_Com = BulletObject->AddComponent<Bullet_Com>("Bullet_Com");

	GameObject* BulletObject2 = GameObject::CreateProtoType("BulletRot_Clone");
	BulletRot_Com* bullet_Com2 = BulletObject2->AddComponent<BulletRot_Com>("BulletRot_Com");

	GameObject* BoomObject = GameObject::CreateProtoType("Boom", Default);
	BulletBoom_Com* bulletBoom_Com = BoomObject->AddComponent<BulletBoom_Com>("Boom_Com");

	GameObject*	TestPixelColl = GameObject::CreateObject("PixelColl", Default);
	Renderer_Com* Renderer = TestPixelColl->AddComponent<Renderer_Com>("PixelCollRenderer");
	Renderer->SetMesh("TextureRect");

	Material_Com* Material = TestPixelColl->FindComponentFromType<Material_Com>(CT_MATERIAL);
	Material->SetDiffuseTexture(0, "TestPixelColl", TEXT("PixelCollider.bmp"));

	ColliderPixel_Com* ColliderPixel = TestPixelColl->AddComponent<ColliderPixel_Com>("TestPixel");

	Pixel24	tPixel = { 255, 0, 255 };
	ColliderPixel->SetInfo(Vector3(0.0f, 0.0f, 0.0f), tPixel, "PixelCollider.bmp");

	Transform_Com* pTransform = TestPixelColl->GetTransform();
	pTransform->SetWorldPos(500.0f, 200.0f, 0.0f);
	pTransform->SetWorldScale(200.0f, 50.0f, 1.0f);

	SAFE_RELEASE(Renderer);
	SAFE_RELEASE(Material);
	SAFE_RELEASE(ColliderPixel);
	SAFE_RELEASE(TestPixelColl);
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