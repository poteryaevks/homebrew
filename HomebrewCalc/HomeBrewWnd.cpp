// Wort.cpp : implementation file
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "HomebrewCalc.h"
#include "HomeBrewWnd.h"



// CWort dialog
IMPLEMENT_DYNAMIC(CWort, CDialog)

CWort::CWort(CView* pParent )
	: m_dHydromod(0)
	, m_strMalt1(_T(""))
	, m_strMalt2(_T(""))
	, m_strMalt3(_T(""))
	, m_strMalt4(_T(""))
	, m_dPlato(0)
	, m_dPC(0)
	, m_dWeight1(0)
	, m_dWeight2(0)
	, m_dWeight3(0)
	, m_dWeight4(0)
	, real_malt_array_size(0)
{
	m_pView = pParent;
}

CWort::CWort()
	: CDialog(IDD_WORT, NULL)
	, m_dHydromod(0)
	, m_strMalt1(_T(""))
	, m_strMalt2(_T(""))
	, m_strMalt3(_T(""))
	, m_strMalt4(_T(""))
	, m_dPlato(0)
	, m_dPC(0)
	, m_dWeight1(0)
	, m_dWeight2(0)
	, m_dWeight3(0)
	, m_dWeight4(0)
	, real_malt_array_size(0)
{
}


CWort::~CWort()
{	
}


void CWort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HYDROMOD, m_dHydromod);
	DDV_MinMaxFloat(pDX, m_dHydromod, 0, 1);
	DDX_Text(pDX, IDC_MALT_2, m_strMalt2);
	DDX_Text(pDX, IDC_MALT_1, m_strMalt1);
	DDX_Text(pDX, IDC_MALT_3, m_strMalt3);
	DDX_Text(pDX, IDC_MALT_4, m_strMalt4);
	DDX_Text(pDX, IDC_PLATO, m_dPlato);
	DDV_MinMaxFloat(pDX, m_dPlato, 0, 50);
	DDX_Text(pDX, IDC_PC, m_dPC);
	DDV_MinMaxFloat(pDX, m_dPC, 0, 2);
	DDX_Text(pDX, IDC_WIEGHT_1, m_dWeight1);
	DDX_Text(pDX, IDC_WIEGHT_2, m_dWeight2);
	DDX_Text(pDX, IDC_WIEGHT_3, m_dWeight3);
	DDX_Text(pDX, IDC_WIEGHT_4, m_dWeight4);
}

unsigned short CWort::maltfunction()
{
	for (size_t i = 0; i < MAX_MALT_ARRAY; i++)
	{
		Malt_arr[i] = _T("\0");
	}

	unsigned short j = 0;

	if (wcscmp(m_strMalt1, _T(" ")) != 0)
	{
		Malt_arr[j] = m_strMalt1;
		j++;
	}
	if (wcscmp(m_strMalt2, _T(" ")) != 0)
	{
		Malt_arr[j] = m_strMalt2;
		j++;
	}
	if (wcscmp(m_strMalt3, _T(" ")) != 0)
	{
		Malt_arr[j] = m_strMalt3;
		j++;
	}
	if (wcscmp(m_strMalt4, _T(" ")) != 0)
	{
		Malt_arr[j] = m_strMalt4;
		j++;
	}
	return j;
}

void CWort::weightfunction()
{
	for (size_t i = 0; i < MAX_MALT_ARRAY; i++)
	{
		Weight_arr[i] = 0;
	}

	unsigned short j = 0;

	if (m_dWeight1)
	{
		Weight_arr[j] = m_dWeight1;
		j++;
	}
	if (m_dWeight2)
	{
		Weight_arr[j] = m_dWeight2;
		j++;
	}
	if (m_dWeight3)
	{
		Weight_arr[j] = m_dWeight3;
		j++;
	}
	if (m_dWeight4)
	{
		Weight_arr[j] = m_dWeight4;
		j++;
	}
}




void CWort::initlocals()
{
	real_malt_array_size = maltfunction();
	weightfunction();
	m_dWater = 0;
	m_dPC = 0;
	m_dWeight = 0;

	for (size_t i = 0; i < MAX_MALT_ARRAY; i++)
	{
		EFG[i] = 0;
	}

	for (size_t i = 0; i < MAX_MALT_ARRAY; i++)
	{
		HWE[i] = 0;
	}
}



void CWort::OnBnClickedCalculate()
{
	UpdateData(TRUE);
	initlocals();


	if (m_dHydromod > 0.5)
	{
		MessageBox(_T("Гидромодуль не может быть больше 0.5"), _T("Предупреждение!"), MB_ICONWARNING);
		m_dHydromod = 0.5;
	}

	if ( m_dHydromod < 0.2 )
	{
		MessageBox(_T("Гидромодуль не может быть меньше 0.2"), _T("Предупреждение!"), MB_ICONWARNING);
		m_dHydromod = 0.2;
	}

	for (size_t i = 0; i < real_malt_array_size; i++)
	{
		p_malt[i] = new CMalt(Malt_arr[i], Weight_arr[i]);
	}

	//расчет максимального выхода 
	//зерна на объем воды

	for (unsigned short i = 0; i < real_malt_array_size; i++)
	{
		m_dWeight += p_malt[i]->getweight();
	}


	m_dWater = m_dWeight / m_dHydromod;

	for (unsigned short i = 0; i < real_malt_array_size; i++)
	{
		m_dPC += p_malt[i]->getHWE() * p_malt[i]->getweight() / m_dWater;
	}

	m_dPC = round(((1000 + m_dPC) / 1000) * 1000) / 1000;
	
	for (size_t i = 0; i < real_malt_array_size; i++)
	{
		delete p_malt[i];
	}

	p_solution = new CSolutionParam(m_dPC);

	m_dPlato = p_solution->getPlato();
	m_dPC = p_solution->getPC();
	
	delete p_solution;

	UpdateData(FALSE);
}





//по нажатию кнопки происходит расчет и сохранение параметров в 
//реестр сцелью их последующей инициализации при повторном открытии модального окна 
void CWort::OnBnClickedOk()
{
 	UpdateData(TRUE);
	regwrite();
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
	this->DestroyWindow();
}


//инициализации при открытии модального окна 
BOOL CWort::OnInitDialog()
{
	regread();
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


template<class T> T CWort::from_string(const std::string &str)
{
    T t;
	std::stringstream ss(str);
	ss >> t;
	return t;
}




void CWort::regwrite()
{
	HKEY hKey;
	wchar_t wbuff[1024];

	hKey = Reg.CBrewRegCreate(_T("SOFTWARE\\WOW6432Node\\HomeBrewCalc\\"));

	ft.CharArray_To_LPCWSTR(ft.to_string(m_dHydromod).c_str(), wbuff);
	Reg.CBrewRegSetStr(hKey, _T("Гидромодуль"), &wbuff[0], sizeof(wbuff));

	ft.CharArray_To_LPCWSTR(ft.to_string(m_dWeight1).c_str(), wbuff);
	Reg.CBrewRegSetStr(hKey, _T("Масса_солода_1"), &wbuff[0], sizeof(wbuff));

	ft.CharArray_To_LPCWSTR(ft.to_string(m_dWeight2).c_str(), wbuff);
	Reg.CBrewRegSetStr(hKey, _T("Масса_солода_2"), &wbuff[0], sizeof(wbuff));

	ft.CharArray_To_LPCWSTR(ft.to_string(m_dWeight3).c_str(), wbuff);
	Reg.CBrewRegSetStr(hKey, _T("Масса_солода_3"), &wbuff[0], sizeof(wbuff));

	ft.CharArray_To_LPCWSTR(ft.to_string(m_dWeight4).c_str(), wbuff);
	Reg.CBrewRegSetStr(hKey, _T("Масса_солода_4"), &wbuff[0], sizeof(wbuff));

	ft.CharArray_To_LPCWSTR(ft.to_string(m_dPC).c_str(), wbuff);
	Reg.CBrewRegSetStr(hKey, _T("Плотность_ПК"), &wbuff[0], sizeof(wbuff));

	ft.CharArray_To_LPCWSTR(ft.to_string(m_dPlato).c_str(), wbuff);
	Reg.CBrewRegSetStr(hKey, _T("Плотность_по_ареометру"), &wbuff[0], sizeof(wbuff));

	Reg.CBrewRegSetStr(hKey, _T("Солод_1"), m_strMalt1, MAX_STRING);
	Reg.CBrewRegSetStr(hKey, _T("Солод_2"), m_strMalt2, MAX_STRING);
	Reg.CBrewRegSetStr(hKey, _T("Солод_3"), m_strMalt3, MAX_STRING);
	Reg.CBrewRegSetStr(hKey, _T("Солод_4"), m_strMalt4, MAX_STRING);

	Reg.CBrewCloseKey(hKey);
}


void CWort::regread()
{
	HKEY hKey;
	char buff[MAX_STRING];

	hKey = Reg.CBrewRegCreate(_T("SOFTWARE\\WOW6432Node\\HomeBrewCalc\\"));
	m_strMalt1.SetString(Reg.CBrewRegGetStr(hKey, _T("Солод_1")));
	m_strMalt2.SetString(Reg.CBrewRegGetStr(hKey, _T("Солод_2")));
	m_strMalt3.SetString(Reg.CBrewRegGetStr(hKey, _T("Солод_3")));
	m_strMalt4.SetString(Reg.CBrewRegGetStr(hKey, _T("Солод_4")));

	ft.LPCWSTR_To_CharArray(Reg.CBrewRegGetStr(hKey, _T("Гидромодуль")), -1, &buff[0], sizeof(buff));
	m_dHydromod = from_string<float>(&buff[0]);
	m_dHydromod = round(m_dHydromod * 100) / 100;

	ft.LPCWSTR_To_CharArray(Reg.CBrewRegGetStr(hKey, _T("Масса_солода_1")), -1, &buff[0], sizeof(buff));
	m_dWeight1 = from_string<float>(&buff[0]);
	m_dWeight1 = round(m_dWeight1 * 1000) / 1000;

	ft.LPCWSTR_To_CharArray(Reg.CBrewRegGetStr(hKey, _T("Масса_солода_2")), -1, &buff[0], sizeof(buff));
	m_dWeight2 = from_string<float>(&buff[0]);
	m_dWeight2 = round(m_dWeight2 * 1000) / 1000;

	ft.LPCWSTR_To_CharArray(Reg.CBrewRegGetStr(hKey, _T("Масса_солода_3")), -1, &buff[0], sizeof(buff));
	m_dWeight3 = from_string<float>(&buff[0]);
	m_dWeight3 = round(m_dWeight3 * 1000) / 1000;

	ft.LPCWSTR_To_CharArray(Reg.CBrewRegGetStr(hKey, _T("Масса_солода_4")), -1, &buff[0], sizeof(buff));
	m_dWeight4 = from_string<float>(&buff[0]);
	m_dWeight4 = round(m_dWeight4 * 1000) / 1000;

	ft.LPCWSTR_To_CharArray(Reg.CBrewRegGetStr(hKey, _T("Плотность_ПК")), -1, &buff[0], sizeof(buff));
	m_dPC = from_string<float>(&buff[0]);
	m_dPC = round(m_dPC*1000) / 1000;

	ft.LPCWSTR_To_CharArray(Reg.CBrewRegGetStr(hKey, _T("Плотность_по_ареометру")), -1, &buff[0], sizeof(buff));
	m_dPlato = from_string<float>(&buff[0]);
	m_dPlato = round(m_dPlato * 100) / 100;

	Reg.CBrewCloseKey(hKey);
}




//исходные данные для затора: 
//гидромодуль, солод 

BEGIN_MESSAGE_MAP(CWort, CDialog)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDOK, &CWort::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CALCULATE, &CWort::OnBnClickedCalculate)
END_MESSAGE_MAP()


BOOL CWort::OnEraseBkgnd(CDC* pDC)
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




////////////////////////
// Rinsing.cpp : implementation file
//

// CRinsing dialog

IMPLEMENT_DYNAMIC(CRinsing, CDialog)

CRinsing::CRinsing(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_RINSING, pParent)
{

}

CRinsing::~CRinsing()
{
}

void CRinsing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRinsing, CDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CRinsing message handlers
BOOL CRinsing::OnEraseBkgnd(CDC* pDC)
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





/////////////////////
// Hop.cpp : implementation file
//

// CHop dialog

IMPLEMENT_DYNAMIC(CHop, CDialog)

CHop::CHop(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_HOP, pParent)
{

}

CHop::~CHop()
{
}

void CHop::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHop, CDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CHop message handlers

BOOL CHop::OnEraseBkgnd(CDC* pDC)
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


BOOL CWort::Create()
{
	// TODO: Add your specialized code here and/or call the base class
		return CDialog::Create(IDD_WORT);
}


void CWort::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	this->DestroyWindow();
	//CDialog::OnCancel();
}


BOOL CHop::Create()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::Create(IDD_HOP);
}


void CHop::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	this->DestroyWindow();
}

BOOL CRinsing::Create()
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::Create(IDD_RINSING);
}


void CRinsing::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	this->DestroyWindow();
}
