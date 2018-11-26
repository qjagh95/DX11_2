
// EditorView.cpp : EditorView Ŭ������ ����
//

#include "EditorHeader.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Editor.h"
#endif

#include "EditorDoc.h"
#include "EditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//EditorView

IMPLEMENT_DYNCREATE(EditorView, CView)

BEGIN_MESSAGE_MAP(EditorView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

//EditorView ����/�Ҹ�

EditorView::EditorView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

EditorView::~EditorView()
{
}

BOOL EditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// EditorView �׸���

void EditorView::OnDraw(CDC* /*pDC*/)
{
	EditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// EditorView �μ�

BOOL EditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void EditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void EditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// EditorView ����

#ifdef _DEBUG
void EditorView::AssertValid() const
{
	CView::AssertValid();
}

void EditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

EditorDoc* EditorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(EditorDoc)));
	return (EditorDoc*)m_pDocument;
}
#endif //_DEBUG


// EditorView �޽��� ó����


void EditorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//AfxGetInstanceHandle
	//Window HISTANCE�� ������ �Լ�
	Core::Get()->Init(AfxGetInstanceHandle(), m_hWnd, 1280, 720);
	Core::Get()->SetGameMode(GM_2D);
}
