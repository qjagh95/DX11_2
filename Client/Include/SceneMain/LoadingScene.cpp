#include "LoadingScene.h"
#include "StartScene.h"
#include "GameObject.h"
#include "MainScene.h"
#include "LoadingThread.h"
#include "Device.h"
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
