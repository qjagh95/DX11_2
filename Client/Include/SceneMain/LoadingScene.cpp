#include "ClientHeader.h"
#include "LoadingScene.h"
#include "StartScene.h"
#include "GameObject.h"
#include "MainScene.h"
#include "LoadingThread.h"
#include "Device.h"

#include "Thread.h"
#include "ThreadManager.h"

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

LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}

bool LoadingScene::Init()
{
	Layer*	pLayer = m_Scene->FindLayer("Default");
	GameObject*	pBackObj = GameObject::CreateObject("LoadingBack", pLayer);
	Renderer_Com* pRenderer = pBackObj->AddComponent<Renderer_Com>("BackRenderer");
	pRenderer->SetMesh("TextureRect");
	pRenderer->SetRenderState(ALPHA_BLEND);
	pRenderer->SetShader(STANDARD_UV_SHADER);
	SAFE_RELEASE(pRenderer);

	Material_Com* pMaterial = pBackObj->FindComponentFromType<Material_Com>(CT_MATERIAL);
	pMaterial->SetDiffuseTexture(0, "LoadingBack", TEXT("Nasus.jpg"));
	SAFE_RELEASE(pMaterial);

	Transform_Com*	pTransform = pBackObj->GetTransform();
	pTransform->SetWorldScale((float)Device::Get()->GetWinSize().Width, (float)Device::Get()->GetWinSize().Height, 1.f);
	SAFE_RELEASE(pBackObj);

	GameObject*	pBarObj = GameObject::CreateObject("Bar", pLayer);
	pTransform = pBarObj->GetTransform();
	pTransform->SetWorldPos(240.0f, 50.0f, 0.0f);

	m_LoadingBar = pBarObj->AddComponent<Bar_Com>("Bar");
	m_LoadingBar->SetScale(800.f, 30.0f, 1.0f);
	m_LoadingBar->SetDir(BD_LEFT);
	m_LoadingBar->SetValue(0.0f);

	pMaterial = pBarObj->FindComponentFromType<Material_Com>(CT_MATERIAL);
	pMaterial->SetDiffuseTexture(0, "LoadingBar", TEXT("Bar/mainBar.status.gauge.mp.layer.png"));
	SAFE_RELEASE(pMaterial);
	SAFE_RELEASE(pBarObj);
	SAFE_RELEASE(pLayer);

	LoadingThread*	pThread = ThreadManager::Get()->ThreadCreate<LoadingThread>("LoadingThread");

	Camera_Com* getCamera = m_Scene->GetMainCamera();
	getCamera->SetCameraType(CT_ORTHO);
	getCamera->SetNear(0.0f);
	SAFE_RELEASE(getCamera);

	return true;
}

int LoadingScene::Input(float DeltaTime)
{
	return 0;
}

int LoadingScene::Update(float DeltaTime)
{
	LoadingThread*	pThread = (LoadingThread*)ThreadManager::Get()->FindThread("LoadingThread");
	pThread->Awake();

	m_LoadingBar->SetValue(100.0f * pThread->GetPersent());

	if (pThread->GetPersent() >= 0.99999f)
		SceneManager::Get()->SetIsChange(true);

	return 0;
}

int LoadingScene::LateUpdate(float DeltaTime)
{
	return 0;
}

void LoadingScene::Collision(float DeltaTime)
{
}

void LoadingScene::CollisionLateUpdate(float DeltaTime)
{
}

void LoadingScene::Render(float DeltaTime)
{
}
