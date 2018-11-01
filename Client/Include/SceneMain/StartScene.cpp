#include "StartScene.h"
#include "GameObject.h"
#include "MainScene.h"
#include "LoadingScene.h"
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
#include "Component/RadioButton_Com.h"

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
	newButton->GetTransform()->SetWorldScale(200.0f, 50.0f, 0.0f);

	Button_Com* buttonCom = newButton->AddComponent<Button_Com>("StartButton");
	buttonCom->SetCallBack(&StartScene::StartButtonActive, this);
	buttonCom->SetStateColor(BS_CLICK, Vector4::Red);
	buttonCom->SetStateColor(BS_MOUSEOVER, Vector4::White * 2.0f);

	GameObject* newCheck = GameObject::CreateObject("CheckBox", UILayer);
	newCheck->GetTransform()->SetWorldPos(300.0f, 360.0f, 0.0f);
	CheckBox_Com* CheckCom = newCheck->AddComponent<CheckBox_Com>("CheckBox");

	GameObject* newCheck1 = GameObject::CreateObject("CheckBox", UILayer);
	newCheck1->GetTransform()->SetWorldPos(500.0f, 360.0f, 0.0f);
	CheckBox_Com* newCheck1Com = newCheck1->AddComponent<CheckBox_Com>("CheckBox");

	CheckCom->SetCallBack([p1 = CheckCom, p2 = newCheck1Com](float _time)
	{
		p1->SetCheckState(CBS_TRUE);
		p2->SetCheckState(CBS_FALSE);
	});

	newCheck1Com->SetCallBack([p1 = CheckCom, p2 = newCheck1Com](float _time)
	{
		p1->SetCheckState(CBS_FALSE);
		p2->SetCheckState(CBS_TRUE);
	});

	//newCheck1Com->SetCallBack([p1 = CheckCom, p2 = newCheck1Com](float _time)
	//{
	//	p1->SetCheckState(CBS_FALSE);
	//	p2->SetCheckState(CBS_TRUE);
	//});

	//GameObject* newRadio1 = GameObject::CreateObject("RadioButton1", UILayer);
	//RadioButton_Com* newRadioCom1 = newRadio1->AddComponent<RadioButton_Com>("RadioButton1");
	//newRadio1->GetTransform()->SetWorldPos(100.0f, 100.0f, 0.0f);

	//GameObject* newRadio2 = GameObject::CreateObject("RadioButton2", UILayer);
	//RadioButton_Com* newRadioCom2 = newRadio2->AddComponent<RadioButton_Com>("RadioButton2");
	//newRadio2->GetTransform()->SetWorldPos(200.0f, 100.0f, 0.0f);

	//GameObject* newRadio3 = GameObject::CreateObject("RadioButton3", UILayer);
	//RadioButton_Com* newRadioCom3 = newRadio3->AddComponent<RadioButton_Com>("RadioButton3");
	//newRadio3->GetTransform()->SetWorldPos(300.0f, 100.0f, 0.0f);

	////newRadioCom1->SetCallBack([p1 = newRadioCom1, p2 = newRadioCom2, p3 = newRadioCom3](float _time)
	////{
	////	p1->SetCheckState(CBS_TRUE); p2->SetCheckState(CBS_FALSE); p3->SetCheckState(CBS_FALSE);
	////});
	////newRadioCom2->SetCallBack([p1 = newRadioCom1, p2 = newRadioCom2, p3 = newRadioCom3](float _time)
	////{
	////	p1->SetCheckState(CBS_FALSE); p2->SetCheckState(CBS_TRUE); p3->SetCheckState(CBS_FALSE);
	////});
	////newRadioCom3->SetCallBack([p1 = newRadioCom1, p2 = newRadioCom2, p3 = newRadioCom3](float _time)
	////{
	////	p1->SetCheckState(CBS_FALSE); p2->SetCheckState(CBS_FALSE); p3->SetCheckState(CBS_TRUE);
	////});

	//SAFE_RELEASE(newRadio1);
	//SAFE_RELEASE(newRadioCom1);

	//SAFE_RELEASE(newRadio2);
	//SAFE_RELEASE(newRadioCom2);

	//SAFE_RELEASE(newRadio3);
	//SAFE_RELEASE(newRadioCom3);

	SAFE_RELEASE(Default);
	SAFE_RELEASE(UILayer);
	SAFE_RELEASE(newButton);
	SAFE_RELEASE(buttonCom);
	SAFE_RELEASE(mainCamera);
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
	SceneManager::Get()->AddSceneComponent<LoadingScene>("LoadingScene", false);
}
