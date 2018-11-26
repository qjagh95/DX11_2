// EditorForm.cpp : 구현 파일입니다.
//
#include "EditorHeader.h"
#include "Editor.h"
#include "EditorForm.h"
#include "afxwin.h"



// EditorForm

IMPLEMENT_DYNCREATE(EditorForm, CFormView)

EditorForm::EditorForm()
	: CFormView(IDD_DIALOG_EDIT)
	, m_TileCountX(0)
	, m_TileCountY(0)
	, m_TileSizeX(0)
	, m_TileSizeY(0)
	, m_TagName(_T(""))
	, m_ScaleX(0)
	, m_ScaleY(0)
	, m_ScaleZ(0)
	, m_RotationX(0)
	, m_RotationY(0)
	, m_RotationZ(0)
	, m_PosX(0)
	, m_PosY(0)
	, m_PosZ(0)
	, m_StartPosX(0)
	, m_StartPosY(0)
	, m_StartPosZ(0)
	, m_BackColorR(0)
	, m_BackColorG(0)
	, m_BackColorB(0)
	, m_BackColorA(0)
{
	m_TileCountX = 0;
	m_TileCountY = 0;
	m_TileSizeX = 0;
	m_TileSizeY = 0;

	m_StageObject = NULLPTR;
	m_StageCom = NULLPTR;
	m_StageTransform = NULLPTR;
}

EditorForm::~EditorForm()
{
	SAFE_RELEASE(m_StageObject);
	SAFE_RELEASE(m_StageCom);
	SAFE_RELEASE(m_StageTransform);
}

void EditorForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TILESELECT, m_TileTypeBox);
	DDX_Control(pDX, IDC_TILEOPTIONSELECT, m_TileOptionBox);
	DDX_Control(pDX, IDC_TILEIMAGESELECT, m_TileImageBox);

	DDX_Text(pDX, IDC_SCALEX2, m_TileCountX);
	DDX_Text(pDX, IDC_SCALEX3, m_TileCountY);
	DDX_Text(pDX, IDC_SCALEX4, m_TileSizeX);
	DDX_Text(pDX, IDC_SCALEX5, m_TileSizeY);
	DDX_Text(pDX, IDC_TAGNAME, m_TagName);
	DDX_Text(pDX, IDC_SCALEX, m_ScaleX);
	DDX_Text(pDX, IDC_SCALEY, m_ScaleY);
	DDX_Text(pDX, IDC_SCALEZ, m_ScaleZ);
	DDX_Text(pDX, IDC_ROTATIONX, m_RotationX);
	DDX_Text(pDX, IDC_ROTATIONY, m_RotationY);
	DDX_Text(pDX, IDC_ROTATIONZ, m_RotationZ);
	DDX_Text(pDX, IDC_POSITIONX, m_PosX);
	DDX_Text(pDX, IDC_POSITIONY, m_PosY);
	DDX_Text(pDX, IDC_POSITIONZ, m_PosZ);
	DDX_Control(pDX, IDC_WORK, m_WorkList);
	DDX_Text(pDX, IDC_STARTPOSX, m_StartPosX);
	DDX_Text(pDX, IDC_STARTPOSY, m_StartPosY);
	DDX_Text(pDX, IDC_STARTPOSZ, m_StartPosZ);
	DDX_Control(pDX, IDC_STARTPOSX, m_StartPosXControl);
	DDX_Control(pDX, IDC_STARTPOSY, m_StartPosYControl);
	DDX_Control(pDX, IDC_STARTPOSZ, m_StartPosZControl);
	DDX_Text(pDX, IDC_COLORR, m_BackColorR);
	DDX_Text(pDX, IDC_COLORG, m_BackColorG);
	DDX_Text(pDX, IDC_COLORB, m_BackColorB);
	DDX_Text(pDX, IDC_COLORA, m_BackColorA);

	int a = m_TileTypeBox.GetCurSel();

	if (m_TileTypeBox.GetCurSel() == 0)
	{
		GetDlgItem(IDC_STARTPOSX)->EnableWindow(true);
		GetDlgItem(IDC_STARTPOSY)->EnableWindow(true);
		GetDlgItem(IDC_STARTPOSZ)->EnableWindow(true);
	}
	else
	{
		GetDlgItem(IDC_STARTPOSX)->EnableWindow(false);
		GetDlgItem(IDC_STARTPOSY)->EnableWindow(false);
		GetDlgItem(IDC_STARTPOSZ)->EnableWindow(false);
	}

}

BEGIN_MESSAGE_MAP(EditorForm, CFormView)
	ON_EN_CHANGE(IDC_SCALEX, &EditorForm::OnEnChangeScalex)
	ON_EN_CHANGE(IDC_ROTATIONX, &EditorForm::OnEnChangeRotationx)
	ON_EN_CHANGE(IDC_POSITIONX, &EditorForm::OnEnChangePositionx)
	ON_EN_CHANGE(IDC_SCALEY, &EditorForm::OnEnChangeScaley)
	ON_EN_CHANGE(IDC_ROTATIONY, &EditorForm::OnEnChangeRotationy)
	ON_EN_CHANGE(IDC_POSITIONY, &EditorForm::OnEnChangePositiony)
	ON_EN_CHANGE(IDC_SCALEZ, &EditorForm::OnEnChangeScalez)
	ON_EN_CHANGE(IDC_ROTATIONZ, &EditorForm::OnEnChangeRotationz)
	ON_EN_CHANGE(IDC_POSITIONZ, &EditorForm::OnEnChangePositionz)
	ON_CBN_SELCHANGE(IDC_TILESELECT, &EditorForm::OnCbnSelchangeTileselect)
	ON_CBN_SELCHANGE(IDC_TILEOPTIONSELECT, &EditorForm::OnCbnSelchangeTileoptionselect)
	ON_CBN_SELCHANGE(IDC_TILEIMAGESELECT, &EditorForm::OnCbnSelchangeTileimageselect)
	ON_BN_CLICKED(IDC_TILECREATEBUTTON, &EditorForm::OnBnClickedTilecreatebutton)
	ON_LBN_SELCHANGE(IDC_WORK, &EditorForm::OnLbnSelchangeWork)
	ON_BN_CLICKED(IDC_COLORSAVE, &EditorForm::OnBnClickedColorsave)
	ON_EN_CHANGE(IDC_COLORR, &EditorForm::OnEnChangeColorr)
	ON_EN_CHANGE(IDC_COLORG, &EditorForm::OnEnChangeColorg)
	ON_EN_CHANGE(IDC_COLORB, &EditorForm::OnEnChangeColorb)
	ON_EN_CHANGE(IDC_COLORA, &EditorForm::OnEnChangeColora)
END_MESSAGE_MAP()


// EditorForm 진단입니다.

#ifdef _DEBUG
void EditorForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void EditorForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


int EditorForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
// EditorForm 메시지 처리기입니다.

void EditorForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_TileTypeBox.SetCurSel(0);
	m_TileOptionBox.SetCurSel(0);
}

void EditorForm::OnEnChangeScalex()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeScaley()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeScalez()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeRotationx()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeRotationy()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeRotationz()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangePositionx()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangePositiony()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangePositionz()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}


//컨트롤박스
////////////////////////////////////////////////////////////////////////
void EditorForm::OnCbnSelchangeTileselect()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void EditorForm::OnCbnSelchangeTileoptionselect()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void EditorForm::OnCbnSelchangeBackcolorselect()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void EditorForm::OnCbnSelchangeTileimageselect()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void EditorForm::OnBnClickedTilecreatebutton()
{
	if (m_StageObject != NULLPTR)
		return;

	UpdateData(TRUE);

	Scene* getScene = SceneManager::Get()->GetCurScene();
	Layer* TileLayer = getScene->FindLayer("Tile");

	m_StageObject = GameObject::CreateObject("StageObject", TileLayer);

	Renderer_Com* stageRender = m_StageObject->AddComponent<Renderer_Com>("StageRender");
	stageRender->SetMesh("TexRect");
	SAFE_RELEASE(stageRender);

	m_StageCom = m_StageObject->AddComponent<Stage2D_Com>("Stage");

	int	TileType = m_TileTypeBox.GetCurSel();
	Vector3	TileScale = Vector3((float)m_TileSizeX, (float)m_TileSizeY, 1.0f);

	m_StageCom->CreateTileMap(m_TileCountX, m_TileCountY, Vector3::Zero, TileScale, (STAGE2D_TILE_TYPE)TileType);
	m_StageTransform = m_StageObject->GetTransform();

	SAFE_RELEASE(getScene);
	SAFE_RELEASE(TileLayer);

	AddWorkText("타일 추가");

	UpdateData(FALSE);
}

void EditorForm::OnLbnSelchangeWork()
{
}

void EditorForm::OnBnClickedColorsave()
{
	wchar_t Buffer[255];
	wsprintf(Buffer, L"배경색 %d, %d, %d, %d 으로 설정", m_BackColorR, m_BackColorG, m_BackColorB, m_BackColorA);
	AddWorkText(Buffer);
}

void EditorForm::AddWorkText(const wstring& Text)
{
	m_WorkList.AddString(Text.c_str());
}

void EditorForm::AddWorkText(const string & Text)
{
	wstring Temp = CA2W(Text.c_str());

	m_WorkList.AddString(Temp.c_str());
}

void EditorForm::AddWorkText(wchar_t * Text)
{
	wstring Temp = Text;
	AddWorkText(Temp);
}

void EditorForm::AddWorkText(char * Text)
{
	string Temp = Text;
	AddWorkText(Temp);
}


void EditorForm::OnEnChangeColorr()
{
	
}

void EditorForm::OnEnChangeColorg()
{
}

void EditorForm::OnEnChangeColorb()
{
	
}

void EditorForm::OnEnChangeColora()
{
}
