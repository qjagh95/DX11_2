
// EditorView.h : EditorView Ŭ������ �������̽�
//

#pragma once


class EditorView : public CView
{
protected: // serialization������ ��������ϴ�.
	EditorView();
	DECLARE_DYNCREATE(EditorView)

// Ư���Դϴ�.
public:
	EditorDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~EditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // EditorView.cpp�� ����� ����
inline EditorDoc* EditorView::GetDocument() const
   { return reinterpret_cast<EditorDoc*>(m_pDocument); }
#endif

