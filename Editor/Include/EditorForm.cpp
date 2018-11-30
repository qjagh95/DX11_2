// EditorForm.cpp : 구현 파일입니다.
//
#include "EditorHeader.h"
#include "Editor.h"
#include "EditorForm.h"
#include "afxwin.h"

//로그를 텍스트파일로 시간입력해서. (엑셀)
//Control Z 되돌리기..?

// EditorForm

IMPLEMENT_DYNCREATE(EditorForm, CFormView)
int EditorForm::m_MaxStrLenth = 70;

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
	, m_BackColorR(0)
	, m_BackColorG(0)
	, m_BackColorB(0)
	, m_BackColorA(0)
	, m_TextCount(0)
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
	DDX_Control(pDX, IDC_STARTPOSX, m_StartPosXControl);
	DDX_Control(pDX, IDC_STARTPOSY, m_StartPosYControl);
	DDX_Text(pDX, IDC_COLORR, m_BackColorR);
	DDX_Text(pDX, IDC_COLORG, m_BackColorG);
	DDX_Text(pDX, IDC_COLORB, m_BackColorB);
	DDX_Text(pDX, IDC_COLORA, m_BackColorA);


	if (m_TileTypeBox.GetCurSel() == 0)
	{
		GetDlgItem(IDC_STARTPOSX)->EnableWindow(true);
		GetDlgItem(IDC_STARTPOSY)->EnableWindow(true);
	}
	else if(m_TileTypeBox.GetCurSel() == 1)
	{
		GetDlgItem(IDC_STARTPOSX)->EnableWindow(false);
		GetDlgItem(IDC_STARTPOSY)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_STARTPOSX)->EnableWindow(true);
		GetDlgItem(IDC_STARTPOSY)->EnableWindow(true);
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
	ON_BN_CLICKED(IDC_COLORSAVE, &EditorForm::OnBnClickedColorsave)
	ON_EN_CHANGE(IDC_COLORR, &EditorForm::OnEnChangeColorr)
	ON_EN_CHANGE(IDC_COLORG, &EditorForm::OnEnChangeColorg)
	ON_EN_CHANGE(IDC_COLORB, &EditorForm::OnEnChangeColorb)
	ON_EN_CHANGE(IDC_COLORA, &EditorForm::OnEnChangeColora)
	ON_EN_CHANGE(IDC_TILECOUNTX, &EditorForm::OnEnChangeTilecountx)
	ON_EN_CHANGE(IDC_TILECOUNTY, &EditorForm::OnEnChangeTilecounty)
	ON_EN_CHANGE(IDC_TILESIZEX, &EditorForm::OnEnChangeTilesizex)
	ON_EN_CHANGE(IDC_TILESIZEY, &EditorForm::OnEnChangeTilesizey)
	ON_EN_CHANGE(IDC_TAGNAME, &EditorForm::OnEnChangeTagname)
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


void EditorForm::AddWorkText(const wstring& Text, int Index)
{
	CTime Time = CTime::GetTickCount();

	wstring Temp2;
	
	Temp2 += to_wstring(Time.GetYear());
	Temp2 += L"년 ";
	Temp2 += to_wstring(Time.GetMonth());
	Temp2 += L"월 ";
	Temp2 += to_wstring(Time.GetDay());
	Temp2 += L"일 ";
	Temp2 += to_wstring(Time.GetHour());
	Temp2 += L"시 ";
	Temp2 += to_wstring(Time.GetMinute());
	Temp2 += L"분 ";
	Temp2 += to_wstring(Time.GetSecond());
	Temp2 += L"초 ";

	m_WorkList.InsertString(Index, Text.c_str());
	ExcelManager::Get()->WriteData("EditorLog", 0, m_TextCount, Text);
	ExcelManager::Get()->WriteData("EditorLog", 6, m_TextCount, Temp2);

	m_TextCount++;
}

void EditorForm::AddWorkText(const string & Text, int Index)
{
	CTime Time = CTime::GetTickCount();

	wstring Temp2;

	Temp2 += to_wstring(Time.GetYear());
	Temp2 += L"년 ";
	Temp2 += to_wstring(Time.GetMonth());
	Temp2 += L"월 ";
	Temp2 += to_wstring(Time.GetDay());
	Temp2 += L"일 ";
	Temp2 += to_wstring(Time.GetHour());
	Temp2 += L"시 ";
	Temp2 += to_wstring(Time.GetMinute());
	Temp2 += L"분 ";
	Temp2 += to_wstring(Time.GetSecond());
	Temp2 += L"초 ";

	wstring Temp = CA2W(Text.c_str());
	m_WorkList.InsertString(Index, Temp.c_str());
	ExcelManager::Get()->WriteData("EditorLog", 0, m_TextCount, Text);
	ExcelManager::Get()->WriteData("EditorLog", 6, m_TextCount, Temp2);

	m_TextCount++;
}

void EditorForm::AddWorkText(const CString & Text, int Index)
{
	CTime Time = CTime::GetTickCount();
	string Temp3;

	Temp3 += to_string(Time.GetYear());
	Temp3 += "년 ";
	Temp3 += to_string(Time.GetMonth());
	Temp3 += "월 ";
	Temp3 += to_string(Time.GetDay());
	Temp3 += "일 ";
	Temp3 += to_string(Time.GetHour());
	Temp3 += "시 ";
	Temp3 += to_string(Time.GetMinute());
	Temp3 += "분 ";
	Temp3 += to_string(Time.GetSecond());
	Temp3 += "초 ";

	string	Temp = CT2CA(Text);
	wstring Temp2 = CA2W(Temp.c_str());

	m_WorkList.InsertString(Index, Temp2.c_str());
	ExcelManager::Get()->WriteData("EditorLog", 0, m_TextCount, Text);
	ExcelManager::Get()->WriteData("EditorLog", 6, m_TextCount, Temp3);

	m_TextCount++;
}

void EditorForm::AddWorkText(wchar_t * Text, int Index)
{
	wstring Temp = Text;
	AddWorkText(Temp, Index);
}

void EditorForm::AddWorkText(char * Text, int Index)
{
	string Temp = Text;
	AddWorkText(Temp, Index);
}

int EditorForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void EditorForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//초기화
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_TileTypeBox.SetCurSel(1);
	m_TileOptionBox.SetCurSel(0);
}

void EditorForm::OnEnChangeScalex()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"SacleX : %d 변경", m_ScaleX);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeScaley()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"SacleY : %d 변경", m_ScaleY);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeScalez()
{
	UpdateData(TRUE);

	if (RenderManager::Get()->GetGameMode() == GM_2D)
	{
		m_ScaleZ = 0;

		wchar_t Buffer[255];
		wsprintf(Buffer, L"2D 모드일땐 ScaleZ값 변경불가");
		AddWorkText(Buffer);

		UpdateData(FALSE);
		return;
	}

	wchar_t Buffer[255];
	wsprintf(Buffer, L"SacleZ : %d 변경", m_ScaleZ);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeRotationx()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"RotationX : %d 변경", m_RotationX);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeRotationy()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"RotationY : %d 변경", m_RotationY);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeRotationz()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"RotationZ : %d 변경", m_RotationZ);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangePositionx()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"PosX : %d 변경", m_PosX);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangePositiony()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"PosY : %d 변경", m_PosY);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangePositionz()
{
	UpdateData(TRUE);

	if (RenderManager::Get()->GetGameMode() == GM_2D)
	{
		m_PosZ = 0;

		wchar_t Buffer[255];
		wsprintf(Buffer, L"2D 모드일땐 PosZ값 변경불가");
		AddWorkText(Buffer);

		UpdateData(FALSE);
		return;
	}

	wchar_t Buffer[255];
	wsprintf(Buffer, L"PosZ : %d 변경", m_PosZ);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}


//컨트롤박스
////////////////////////////////////////////////////////////////////////
void EditorForm::OnCbnSelchangeTileselect()
{
	UpdateData(TRUE);

	CString Buffer;
	m_TileTypeBox.GetLBText(m_TileTypeBox.GetCurSel(),Buffer);
	Buffer += " 선택";

	m_StartPosX = 0;
	m_StartPosY = 0;

	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnCbnSelchangeTileoptionselect()
{
	UpdateData(TRUE);

	CString Buffer;
	m_TileOptionBox.GetLBText(m_TileOptionBox.GetCurSel(), Buffer);
	Buffer += " 옵션 선택";

	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnCbnSelchangeTileimageselect()
{
	UpdateData(TRUE);

	CString Buffer;
	m_TileImageBox.GetLBText(m_TileImageBox.GetCurSel(), Buffer);
	Buffer += " 타일 이미지 선택";

	AddWorkText(Buffer);

	//여기서 Path추가 후 타일 가져와서 Texture변경

	UpdateData(FALSE);
}

void EditorForm::OnBnClickedTilecreatebutton()
{
	if (m_StageObject != NULLPTR)
		return;

	UpdateData(TRUE);

	if (m_TileCountX == 0 || m_TileCountY == 0 || m_TileSizeX == 0 || m_TileSizeY == 0)
	{
		wchar_t Buffer[255];
		wsprintf(Buffer, L" 타일갯수와 사이즈를 정확히 입력하세요");

		AddWorkText(Buffer);
		UpdateData(TRUE);

		return;
	}

	Scene* getScene = SceneManager::Get()->GetCurScene();
	Layer* TileLayer = getScene->FindLayer("Tile");

	m_StageObject = GameObject::CreateObject("StageObject", TileLayer);

	Renderer_Com* stageRender = m_StageObject->AddComponent<Renderer_Com>("StageRender");
	stageRender->SetMesh("TextureRect");
	SAFE_RELEASE(stageRender);

	Material_Com* stageMat = m_StageObject->FindComponentFromType<Material_Com>(CT_MATERIAL);
	stageMat->SetMaterial(Vector4::Black);
	
	SAFE_RELEASE(stageMat);

	m_StageCom = m_StageObject->AddComponent<Stage2D_Com>("Stage");

	int	TileType = m_TileTypeBox.GetCurSel();
	Vector3	TileScale = Vector3((float)m_TileSizeX, (float)m_TileSizeY, 1.0f);

	m_StageCom->CreateTileMap(m_TileCountX, m_TileCountY, Vector3((float)m_StartPosX, (float)m_StartPosY, 0.0f), TileScale, (STAGE2D_TILE_TYPE)TileType);
	m_StageTransform = m_StageObject->GetTransform();

	SAFE_RELEASE(getScene);
	SAFE_RELEASE(TileLayer);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"타일 X : %d, 타일 Y : %d, 총 타일 : %d 추가", m_TileCountX, m_TileCountY, m_TileCountX * m_TileCountY);
	AddWorkText(Buffer);

	UpdateData(FALSE);
}

void EditorForm::OnBnClickedColorsave()
{
	UpdateData(TRUE);

	wchar_t Buffer[255];
	wsprintf(Buffer, L"배경색 %d, %d, %d, %d 값 저장", m_BackColorR, m_BackColorG, m_BackColorB, m_BackColorA);
	AddWorkText(Buffer);

	ExcelManager::Get()->WriteData("BackColor", 0, 0, Vector4((float)m_BackColorR, (float)m_BackColorG, (float)m_BackColorB, (float)m_BackColorA));

	UpdateData(FALSE);
}


void EditorForm::OnEnChangeColorr()
{
	UpdateData(TRUE);

	if (m_BackColorR < 0)
		m_BackColorR = 0;
	else if (m_BackColorR > 255)
		m_BackColorR = 255;

	wchar_t Buffer[255];
	wsprintf(Buffer, L"R값 %d 입력", m_BackColorR);
	AddWorkText(Buffer);

	wchar_t Buffer2[255];
	wsprintf(Buffer2, L"R : %d, G : %d, B : %d, A : %d", m_BackColorR, m_BackColorG, m_BackColorB, m_BackColorA);
	AddWorkText(Buffer2, 1);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeColorg()
{
	UpdateData(TRUE);

	if (m_BackColorG < 0)
		m_BackColorG = 0;
	else if (m_BackColorG > 255)
		m_BackColorG = 255;

	wchar_t Buffer[255];
	wsprintf(Buffer, L"G값 %d 입력", m_BackColorG);
	AddWorkText(Buffer);

	wchar_t Buffer2[255];
	wsprintf(Buffer2, L"R : %d, G : %d, B : %d, A : %d \n", m_BackColorR, m_BackColorG, m_BackColorB, m_BackColorA);
	AddWorkText(Buffer2, 1);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeColorb()
{
	UpdateData(TRUE);

	if (m_BackColorB < 0)
		m_BackColorB = 0;
	else if (m_BackColorB > 255)
		m_BackColorB = 255;

	wchar_t Buffer[255];
	wsprintf(Buffer, L"B값 %d 입력", m_BackColorB);
	AddWorkText(Buffer);

	wchar_t Buffer2[255];
	wsprintf(Buffer2, L"R : %d, G : %d, B : %d, A : %d \n", m_BackColorR, m_BackColorG, m_BackColorB, m_BackColorA);
	AddWorkText(Buffer2, 1);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeColora()
{
	UpdateData(TRUE);

	if (m_BackColorA < 0)
		m_BackColorA = 0;
	else if (m_BackColorA > 255)
		m_BackColorA = 255;

	wchar_t Buffer[255];
	wsprintf(Buffer, L"A값 %d 입력", m_BackColorA);
	AddWorkText(Buffer);

	wchar_t Buffer2[255];
	wsprintf(Buffer2, L"R : %d, G : %d, B : %d, A : %d \n", m_BackColorR, m_BackColorG, m_BackColorB, m_BackColorA);
	AddWorkText(Buffer2, 1);

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeTilecountx()
{
	UpdateData(TRUE);

	if (m_TileCountX > 10000)
		m_TileCountX = 10000;
	else if (m_TileCountX < 0)
		m_TileCountX = 0;

	wchar_t Buffer[255];
	wsprintf(Buffer, L"X축 타일 갯수 : %d 입력", m_TileCountX);
	AddWorkText(Buffer);

	if (m_TileTypeBox.GetCurSel() == 0)
	{
		m_StartPosX = (int)(m_TileCountX * m_TileSizeX / 2.0f);
		m_StartPosY = (int)(m_TileCountY * m_TileSizeY / 2.0f);

		wchar_t Buffer2[255];
		wsprintf(Buffer2, L"타일 시작위치 X : %d ,Y : %d 자동입력 \n", m_StartPosX, m_StartPosY);
		AddWorkText(Buffer2, 1);
	}
	else
	{
		m_StartPosX = 0;
		m_StartPosY = 0;
	}

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeTilecounty()
{
	UpdateData(TRUE);

	if (m_TileCountY > 10000)
		m_TileCountY = 10000;
	else if (m_TileCountY < 0)
		m_TileCountY = 0;

	wchar_t Buffer[255];
	wsprintf(Buffer, L"Y축 타일 갯수 : %d 입력", m_TileCountY);
	AddWorkText(Buffer);

	if (m_TileTypeBox.GetCurSel() == 0)
	{
		m_StartPosX = (int)(m_TileCountX * m_TileSizeX / 2.0f);
		m_StartPosY = (int)(m_TileCountY * m_TileSizeY / 2.0f);

		wchar_t Buffer2[255];
		wsprintf(Buffer2, L"타일 시작위치 X : %d ,Y : %d 자동입력 \n", m_StartPosX, m_StartPosY);
		AddWorkText(Buffer2);
	}
	else
	{
		m_StartPosX = 0;
		m_StartPosY = 0;
	}

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeTilesizex()
{
	UpdateData(TRUE);

	if (m_TileSizeX > 500)
		m_TileSizeX = 500;

	wchar_t Buffer[255];
	wsprintf(Buffer, L"타일 사이즈X : %d 입력", m_TileSizeX);
	AddWorkText(Buffer);

	if (m_TileTypeBox.GetCurSel() == 0)
	{
		m_StartPosX = (int)(m_TileCountX * m_TileSizeX / 2.0f);
		m_StartPosY = (int)(m_TileCountY * m_TileSizeY / 2.0f);

		wchar_t Buffer2[255];
		wsprintf(Buffer2, L"타일 시작위치 X : %d ,Y : %d 자동입력 \n", m_StartPosX, m_StartPosY);
		AddWorkText(Buffer2);
	}
	else
	{
		m_StartPosX = 0;
		m_StartPosY = 0;
	}

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeTilesizey()
{
	UpdateData(TRUE);

	if (m_TileSizeY > 500)
		m_TileSizeY = 500;

	wchar_t Buffer[255];
	wsprintf(Buffer, L"타일 사이즈Y : %d 입력", m_TileSizeY);
	AddWorkText(Buffer);

	if (m_TileTypeBox.GetCurSel() == 0)
	{
		if (m_TileSizeY > m_TileSizeX / 2)
			m_TileSizeY = m_TileSizeX / 2;

		m_StartPosX = (int)(m_TileCountX * m_TileSizeX / 2.0f);
		m_StartPosY = (int)(m_TileCountY * m_TileSizeY / 2.0f);

		wchar_t Buffer2[255];
		wsprintf(Buffer2, L"타일 시작위치 X : %d ,Y : %d 자동입력 \n", m_StartPosX, m_StartPosY);
		AddWorkText(Buffer2);
	}
	else
	{
		m_StartPosX = 0;
		m_StartPosY = 0;
	}

	UpdateData(FALSE);
}

void EditorForm::OnEnChangeTagname()
{
	UpdateData(TRUE);

	CString Buffer;
	Buffer = "TagName : ";
	Buffer += m_TagName;
	Buffer += " 설정";

	AddWorkText(Buffer);

	UpdateData(FALSE);
}