#include "StartScene.h"
#include "GameObject.h"
#include "MainScene.h"
#include "Device.h"

#include "Scene/Scene.h"
#include "Scene/Layer.h"
#include "Scene/SceneManager.h"

#include "Component/Transform_Com.h"
#include "Component/Renderer_Com.h"
#include "Component/Camera_Com.h"
#include "Component/ColliderRect_Com.h"
#include "Component/ColliderPixel_Com.h"
#include "Component/Material_Com.h"
#include "Component/Button_Com.h"
#include "Component/CheckBox_Com.h"


StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::Init()
{
	Camera_Com* mainCamera = m_Scene->GetMainCamera();
	mainCamera->SetCameraType(CT_ORTHO);
	mainCamera->SetNear(0.0f);

	Layer* Default = m_Scene->FindLayer("Default");
	Layer* UILayer = m_Scene->FindLayer("UI");

	GameObject* newButton = GameObject::CreateObject("StartButton", UILayer);
	newButton->GetTransform()->SetWorldPos(640.0f, 360.0f, 0.0f);

	Button_Com* buttonCom = newButton->AddComponent<Button_Com>("StartButton");
	buttonCom->SetCallBack(&StartScene::StartButtonActive, this);
	
	GameObject* newCheck = GameObject::CreateObject("newCheck", UILayer);
	newCheck->GetTransform()->SetWorldPos(100.0f, 360.0f, 0.0f);

	CheckBox_Com* CheckCom = newCheck->AddComponent<CheckBox_Com>("newCheck");

	SAFE_RELEASE(Default);
	SAFE_RELEASE(UILayer);
	SAFE_RELEASE(newButton);
	SAFE_RELEASE(buttonCom);

	SAFE_RELEASE(newCheck);
	SAFE_RELEASE(CheckCom);

	return true;
}

int StartScene::Input(float DeltaTime)
{
	return 0;
}

int StartScene::Update(float DeltaTime)
{
	return 0;
}

int StartScene::LateUpdate(float DeltaTime)
{
	return 0;
}

void StartScene::Collision(float DeltaTime)
{
}

void StartScene::CollisionLateUpdate(float DeltaTime)
{
}

void StartScene::Render(float DeltaTime)
{
}

void StartScene::StartButtonActive(float DeltaTime)
{
	SceneManager::Get()->CreateNextScene();
	SceneManager::Get()->AddSceneComponent<MainScene>("MainScene", false);
}
