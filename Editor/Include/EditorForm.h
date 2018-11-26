#pragma once
#include <Component/Stage2D_Com.h>
// EditorForm 폼 뷰입니다.
JEONG_USING
class EditorForm : public CFormView
{
	DECLARE_DYNCREATE(EditorForm)

protected:
	EditorForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~EditorForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EDIT };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	Vector3 m_Scale;
	Vector3 m_Rot;
	Vector3 m_Pos;
	int m_ScaleX;
	int m_ScaleY;
	int m_ScaleZ;
	int m_RotationX;
	int m_RotationY;
	int m_RotationZ;
	int m_PosX;
	int m_PosY;
	int m_PosZ;

	CString m_TagName;
	int m_TileCountX;
	int m_TileCountY;
	int m_TileSizeX;
	int m_TileSizeY;
	float m_StartPosX;
	float m_StartPosY;
	float m_StartPosZ;

	GameObject* m_StageObject;
	Stage2D_Com* m_StageCom;
	Transform_Com* m_StageTransform;

	int m_BackColorR;
	int m_BackColorG;
	int m_BackColorB;
	int m_BackColorA;

	GameObject* GetStageObject() const { return m_StageObject; }
	Stage2D_Com* GetStageComponent() const { return m_StageCom; }
	Transform_Com* GetStageTransform() const { return m_StageTransform; }
	void AddWorkText(const wstring& Text);
	void AddWorkText(const string& Text);
	void AddWorkText(wchar_t* Text);
	void AddWorkText(char* Text);

	CComboBox m_TileTypeBox;
	CComboBox m_TileOptionBox;
	CComboBox m_BackColorBox;
	CComboBox m_TileImageBox;
	CListBox m_WorkList;

	CEdit m_StartPosXControl;
	CEdit m_StartPosYControl;
	CEdit m_StartPosZControl;

	virtual void OnInitialUpdate();
	afx_msg void OnEnChangeScalex();
	afx_msg void OnEnChangeRotationx();
	afx_msg void OnEnChangePositionx();
	afx_msg void OnEnChangeScaley();
	afx_msg void OnEnChangeRotationy();
	afx_msg void OnEnChangePositiony();
	afx_msg void OnEnChangeScalez();
	afx_msg void OnEnChangeRotationz();
	afx_msg void OnEnChangePositionz();
	afx_msg void OnCbnSelchangeTileselect();
	afx_msg void OnCbnSelchangeTileoptionselect();
	afx_msg void OnCbnSelchangeBackcolorselect();
	afx_msg void OnCbnSelchangeTileimageselect();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedTilecreatebutton();

	afx_msg void OnLbnSelchangeWork();
	afx_msg void OnBnClickedColorsave();

	afx_msg void OnEnChangeColorr();
	afx_msg void OnEnChangeColorg();
	afx_msg void OnEnChangeColorb();
	afx_msg void OnEnChangeColora();
};


