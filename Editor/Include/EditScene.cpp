#include "EditorHeader.h"
#include "EditScene.h"
#include "MainFrame.h"
#include "EditorForm.h"

EditScene::EditScene()
{
}

EditScene::~EditScene()
{
	SAFE_RELEASE(m_BackColorCom);
}

bool EditScene::Init()
{
	Camera_Com*	pCamera = m_Scene->GetMainCamera();
	pCamera->SetCameraType(CT_ORTHO);
	pCamera->SetNear(0.0f);

	Layer* BackLayer = m_Scene->FindLayer("BackGround");
	Layer* Default = m_Scene->FindLayer("Default");
	Layer* UILayer = m_Scene->FindLayer("UI");
	Layer* TileLayer = m_Scene->FindLayer("Tile");

	GameObject* BackObject = GameObject::CreateObject("BackObject", BackLayer);
	m_BackColorCom = BackObject->AddComponent<BackColor_Com>("BackColor");

	SAFE_RELEASE(BackObject);

	SAFE_RELEASE(BackLayer);
	SAFE_RELEASE(Default);
	SAFE_RELEASE(TileLayer);
	SAFE_RELEASE(UILayer);

	return true;
}

int EditScene::Update(float DeltaTime)
{
	MainFrame* mainFrame = (MainFrame*)AfxGetMainWnd();
	EditorForm*	editorForm = mainFrame->GetEditorForm();

	m_BackColorCom->SetBackColor(Vector4((float)editorForm->m_BackColorR, (float)editorForm->m_BackColorG, (float)editorForm->m_BackColorB, (float)editorForm->m_BackColorA));

	Stage2D_Com* TileStage = editorForm->GetStageComponent();

	if (TileStage != NULLPTR)
	{
		if (KeyInput::Get()->KeyPress("LButton"))
		{
			// 마우스의 월드위치를 얻어온다.
			Vector2	MouseWorld = KeyInput::Get()->GetMouseWorldPos();

			TileStage->SetTileOption(Vector3(MouseWorld.x, MouseWorld.y, 0.0f), (TILE2D_OPTION)editorForm->GetTileOption());

			if (editorForm->GetTileOption() == STT_TILE)
				TileStage->SetMoveMesh(Vector3(MouseWorld.x, MouseWorld.y, 0.0f));
			else
				TileStage->SetNoMoveMesh(Vector3(MouseWorld.x, MouseWorld.y, 0.0f));
		}
	}

	return 0;
}
