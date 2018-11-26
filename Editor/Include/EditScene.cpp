#include "EditorHeader.h"
#include "EditScene.h"
#include "MainFrame.h"
#include "EditorForm.h"
#include <Component/Stage2D_Com.h>

EditScene::EditScene()
{
}

EditScene::~EditScene()
{
}

bool EditScene::Init()
{
	Camera_Com*	pCamera = m_Scene->GetMainCamera();
	pCamera->SetCameraType(CT_ORTHO);
	pCamera->SetNear(0.0f);

	return true;
}

int EditScene::Update(float DeltaTime)
{
	MainFrame* mainFrame = (MainFrame*)AfxGetMainWnd();
	EditorForm*	editorForm = mainFrame->GetEditorForm();
	//Stage2D_Com* TileStage = editorForm->GetStage();

	//if (TileStage != NULLPTR)
	//{
	//	if (KeyInput::Get()->KeyPress("LButton"))
	//	{
	//		// 마우스의 월드위치를 얻어온다.
	//		Vector2	MouseWorld = KeyInput::Get()->GetMouseWorldPos();
	//		TileStage->SetTileOption(Vector3(MouseWorld.x, MouseWorld.y, 0.0f), (TILE2D_OPTION)editorForm->GetTileOption());
	//	}
	//}

	return 0;
}
