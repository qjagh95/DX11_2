#include "EditorHeader.h"
#include "EditScene.h"
#include "MainFrame.h"
#include "EditorForm.h"
#include <Component/Tile2D_Com.h>

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

	KeyInput::Get()->AddKey("TileOption", VK_TAB);
	KeyInput::Get()->AddKey("MouseWhill", WM_MOUSEWHEEL);
	KeyInput::Get()->AddKey("TileOption", VK_TAB);

	m_CameraScale = Vector3::One;

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
			Vector3	MouseWorld = KeyInput::Get()->GetMouseWorldPos();

			if (editorForm->GetTileOption() == T2D_NORMAL)
			{
				TileStage->SetMoveMesh(MouseWorld);
				TileStage->SetTileOption(MouseWorld, T2D_NORMAL);
			}
			else
			{
				TileStage->SetNoMoveMesh(MouseWorld);
				TileStage->SetTileOption(MouseWorld, T2D_NOMOVE);
			}
		}

		if (KeyInput::Get()->KeyDown("TileOption"))
		{
			if (editorForm->m_TileOptionBox.GetCurSel() == 0)
				editorForm->m_TileOptionBox.SetCurSel(1);
			else 
				editorForm->m_TileOptionBox.SetCurSel(0);
		}
	}

	return 0;
}
