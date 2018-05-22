#pragma once


// CWort dialog

#include "BrewDataBase.h"
#include "BrewReg.h"
#include "FormatText.h"
#include "Malt.h"
#include "Array.cpp"

using namespace kp;

#define MAX_STRING 1024
#define MAX_ARRAY 16
#define MAX_MALT_ARRAY 4


#define WM_GOODBYE WM_USER


class CWort : public CDialog
{
	DECLARE_DYNAMIC(CWort)

public:
	CWort(CView* pParent);   // non-modal constructor
	CWort();   // modal constructor
	virtual ~CWort();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORT };
#endif

protected:
	CView * m_pView;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	
	CSolutionParam* p_solution;
	CFormatText ft;
	CBrewReg Reg;  //для работы с реестром 
	CMalt* p_malt[MAX_MALT_ARRAY];

	void regwrite();
	void regread();
	unsigned short maltfunction();  //функция записи в Malt(ов) массив 
	void weightfunction(); //функция записи в Weight(ов) массив 
	void initlocals();

	
	virtual BOOL OnInitDialog();
	template<class T> T from_string(const std::string &str);

	CString Malt_arr[MAX_MALT_ARRAY]; //массив Malt(ов)  
	double Weight_arr[MAX_MALT_ARRAY]; //массив Weight(ов)

//расчетнаый данные
	double m_dWeight;  //общий вес солода
	double m_dWater;  //объем воды
	double EFG[MAX_MALT_ARRAY]; //среднее
	double HWE[MAX_MALT_ARRAY]; //среднее 
	unsigned short real_malt_array_size;

	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCalculate();

public:
	double m_dWeight1;
	double m_dWeight2;
	double m_dWeight3;
	double m_dWeight4;

	CString m_strMalt1;
	CString m_strMalt2;
	CString m_strMalt3;
	CString m_strMalt4;

	double m_dHydromod;
	double m_dPlato;
	double m_dPC;
	virtual BOOL Create();
	virtual void OnCancel();
};



/////////////////////////////////////////
// CHop dialog

class CHop : public CDialog
{
	DECLARE_DYNAMIC(CHop)

public:
	CHop(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHop();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOP };
#endif

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CView * m_pView;
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
public:
	virtual BOOL Create();
	virtual void OnCancel();
};





/////////////////////////////////
// CRinsing dialog

class CRinsing : public CDialog
{
	DECLARE_DYNAMIC(CRinsing)

public:
	CRinsing(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRinsing();
	CView * m_pView;
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RINSING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:
	virtual BOOL Create();
	virtual void OnCancel();
};



