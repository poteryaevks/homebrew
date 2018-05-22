
// HomebrewCalcView.cpp : implementation of the CHomebrewCalcView class
//

#include "stdafx.h"

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HomebrewCalc.h"
#endif
#include "MainFrm.h"
#include "HomebrewCalcDoc.h"
#include "HomebrewCalcView.h"
#include "resource.h"
#include "windef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHomebrewCalcView

IMPLEMENT_DYNCREATE(CHomebrewCalcView, CView)

BEGIN_MESSAGE_MAP(CHomebrewCalcView, CView)
	// Standard printing commands
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CHomebrewCalcView construction/destruction

CHomebrewCalcView::CHomebrewCalcView() : m_brush(GRAY_BRUSH)
{
	m_pWort_dlg = new CWort(this);
	m_pHop_dlg = new CHop(this);
	m_pRinsing_dlg = new CRinsing(this);


	//CWnd* p = m_pWort_dlg->GetParent();
	
	HINSTANCE HandleDll;
	
	try
	{
		HandleDll = LoadLibraryEx(_T("res.dll"), 0, LOAD_LIBRARY_AS_DATAFILE);
		if (HandleDll == 0)
		{
			DWORD error = GetLastError();
			std::wstring str1 = std::to_wstring(error);
			std::wstring str2 = _T("error ");
			str2 = str2 + str1;
			throw str2;
		}
	}
	
	catch(std::wstring err)
	{
		MessageBox(_T("Не удалось загрузить библиотеку! "), (LPCTSTR)err.c_str(), MB_ICONWARNING);
		((CMainFrame*)AfxGetMainWnd())->SendMessage(WM_CLOSE, 0, 0);
	}
	
	try
	{
		GetBitmapFromDll(HandleDll, ( int*)&m_BmpId[0], &m_phBmp[0]);
	}
	catch (std::wstring err)
	{
		MessageBox(_T("Не удалось загрузить ресурс! "), (LPCTSTR)err.c_str(), MB_ICONWARNING);
		((CMainFrame*)AfxGetMainWnd())->SendMessage(WM_CLOSE, 0, 0);
	}

	FreeLibrary(HandleDll);

	c_ProgrammName[0] = CString("Расчет затора");
	c_ProgrammName[1] = CString("Расчет промывки");
	c_ProgrammName[2] = CString("Расчет хмеля");

	int a = 230,
		b = 50,
		c = 339,
		d = 122,
		hight = d - b,
		shift = 50;

	for ( size_t i = 0; i < 3; i++ )
	{
		m_rectSquere[i].SetRect(a, b, c, d);
		m_rectSquereText[i].SetRect(a - 150, b + 30, c - 100, d - 20);
		b = d + shift;
		d = d + hight + shift;
	}
	
	
}

CHomebrewCalcView::~CHomebrewCalcView()
{	
	delete	m_pWort_dlg;
	delete	m_pHop_dlg;
	delete	m_pRinsing_dlg;	
}

BOOL CHomebrewCalcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying

	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

// CHomebrewCalcView drawing

void CHomebrewCalcView::OnDraw(CDC* pDC)
{
	CPoint m_Ppnt;
	CSize* m_pSsize = &m_rectSquere[1].Size();
	
	

	for (size_t i = 0; i < 3; i++)
	{
		pDC->SetBkMode(TRANSPARENT);   //текст без фона
		pDC->DrawTextW(c_ProgrammName[i], m_rectSquereText[i], (DT_CENTER | DT_BOTTOM ));
		m_Ppnt.x = m_rectSquere[i].left;
		m_Ppnt.y = m_rectSquere[i].top;
		pDC->DrawState(m_Ppnt, *m_pSsize, m_phBmp[i], 0, NULL);
	}
	
	m_nColor = GRAY_BRUSH;


	CHomebrewCalcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	AfxGetApp()->GetMainWnd()->SetWindowText(_T("Beer brew calculator"));
	
	// TODO: add draw code for native data here
}


// CHomebrewCalcView printing

BOOL CHomebrewCalcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHomebrewCalcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHomebrewCalcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CHomebrewCalcView diagnostics

#ifdef _DEBUG
void CHomebrewCalcView::AssertValid() const
{
	CView::AssertValid();
}

void CHomebrewCalcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHomebrewCalcDoc* CHomebrewCalcView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHomebrewCalcDoc)));
	return (CHomebrewCalcDoc*)m_pDocument;
}
#endif //_DEBUG


// CHomebrewCalcView message handlers
// CWort message handlers
// CMainFrame message handlers
BOOL CHomebrewCalcView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	// Set brush to desired background color
	CBrush backBrush(RGB(209, 180, 107));

	// Save old brush
	CBrush* pOldBrush = pDC->SelectObject(&backBrush);

	CRect rect;
	pDC->GetClipBox(&rect);     // Erase the area needed
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);

	return TRUE;
}



void CHomebrewCalcView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	if (m_rectSquere[0].PtInRect(point))
	{
		if (m_pWort_dlg->GetSafeHwnd() == 0) 
		{
			m_pWort_dlg->Create(); // показывает диалоговое окно на экране
		}
	}
		
	if (m_rectSquere[1].PtInRect(point))
	{
		m_pRinsing_dlg->Create(); // показывает диалоговое окно на экране
	}

	if (m_rectSquere[2].PtInRect(point))
	{
		m_pHop_dlg->Create(); // показывает диалоговое окно на экране
	}

	CView::OnLButtonDown(nFlags, point);
}


void CHomebrewCalcView::GetBitmapFromDll(HINSTANCE hDll,
	                  int* resID,     
	                  HBITMAP* hbmp)
{
	for (size_t i = 0; i < 3; i++)
	{
		HRSRC hResource = FindResource(hDll, MAKEINTRESOURCE(*resID), RT_BITMAP);  //MAKEINTRESOURCE(1000)
		if (!hResource)
		{
			const DWORD lastError = ::GetLastError();
			std::wstring str1 = std::to_wstring(lastError);
			std::wstring str2 = _T("error ");
			throw str2;
		}

		HGLOBAL hGlobal = ::LoadResource(hDll, hResource);
		if (!hGlobal)
		{
			const DWORD lastError = ::GetLastError();
			std::wstring str1 = std::to_wstring(lastError);
			std::wstring str2 = _T("error ");
			throw str2;
		}
		/*для gitcscscscscsc*/
		*hbmp = LoadBitmap(hDll, MAKEINTRESOURCE(*resID));
		if (!*hbmp)
		{
			const DWORD lastError = ::GetLastError();
			std::wstring str1 = std::to_wstring(lastError);
			std::wstring str2 = _T("error ");
			throw str2;
		}
		hbmp++;
		resID++;
	}
	
}