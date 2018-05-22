
// HomebrewCalcView.h : interface of the CHomebrewCalcView class
//

#pragma once

#include "HomeBrewWnd.h"







class CHomebrewCalcView : public CView
{
protected: // create from serialization only
	CHomebrewCalcView();
	DECLARE_DYNCREATE(CHomebrewCalcView)

// Attributes
public:
	CHomebrewCalcDoc* GetDocument() const;

// Operations
public: 
	
	
	CRect m_rectSquere[3];
	CRect m_rectSquereText[3];
	CString c_ProgrammName[3];
	CBrush m_brush;
	
	
	CWort* m_pWort_dlg;
	CRinsing* m_pRinsing_dlg;
	CHop* m_pHop_dlg;

	const int m_BmpId[3] = {1001, 1002, 1000};
	int m_nColor;
	HBITMAP m_phBmp[3];
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	void GetBitmapFromDll(HINSTANCE hDll, int* resID, HBITMAP* hbmp);

// Implementation
public:
	virtual ~CHomebrewCalcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in HomebrewCalcView.cpp
inline CHomebrewCalcDoc* CHomebrewCalcView::GetDocument() const
   { return reinterpret_cast<CHomebrewCalcDoc*>(m_pDocument); }
#endif

