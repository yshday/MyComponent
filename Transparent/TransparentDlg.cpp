
// TransparentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Transparent.h"
#include "TransparentDlg.h"
#include "afxdialogex.h"

#pragma comment(lib, "atls")
#include <atlbase.h>
#include <atlhost.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTransparentDlg dialog



CTransparentDlg::CTransparentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRANSPARENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransparentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
}

BEGIN_MESSAGE_MAP(CTransparentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTransparentDlg::OnBnClickedButton1)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CTransparentDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTransparentDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTransparentDlg message handlers

BOOL CTransparentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	MoveWindow(0, 0, 800, 415);
	CenterWindow();

	CRect rc;
	GetClientRect(&rc);


	// TODO: Add extra initialization here
	m_btn.SetImage(IDB_PNG1, IDB_PNG1, IDB_PNG1, IDB_PNG1, L"PNG");

	/*
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_list.InsertColumn(0, L"", LVCFMT_LEFT, 500, 0);
	m_list.InsertItem(0, L"");
	m_list.SetItemText(0, 0, L"2018.10.09 문서보안 작업 공지");
	m_list.InsertItem(1, L"");
	m_list.SetItemText(1, 0, L"2018.05.30 문서보안 작업 공지");
	m_list.InsertItem(2, L"");
	m_list.SetItemText(2, 0, L"랜섬웨어 주의 안내");
	m_list.InsertItem(3, L"");
	m_list.SetItemText(3, 0, L"정보보안 세미나 개최");

	m_list.MoveWindow(0, 0, 500, 500);
	m_btn.SetWindowPos(NULL, 0, 0, 50, 50, SWP_NOMOVE | SWP_NOZORDER);
	
	CImageList imgList;
	imgList.Create(1, 42, ILC_COLOR32, 1, 0);
	m_list.SetImageList(&imgList, LVSIL_SMALL);
	m_btn2.MoveWindow(rc.Width() - 30, rc.Height() - 30, 30, 30);
	*/

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTransparentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTransparentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTransparentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CComModule g_module;
void CTransparentDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	//MessageBox(L"TEST", L"TEST", MB_OK);
	auto handle = AfxGetInstanceHandle();
	g_module.Init(NULL, handle);
	AtlAxWinInit();

	HWND browser = CreateWindow(TEXT(ATLAXWIN_CLASS),
		TEXT("mshtml:<html><html><head><meta http-equiv=\"X-UA-Compatible\" content=\"IE=11\"></head><body>Hello world!</body></html>"),
		WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, m_hWnd, 0,
		handle,
	0);
	::MoveWindow(browser, 0, 0, 500, 500, 1);

}


BOOL CTransparentDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rc;
	GetClientRect(&rc);

	Gdiplus::Bitmap bitmap(rc.Width(), rc.Height());
	Gdiplus::Graphics graphics(*pDC);
	Gdiplus::Graphics memDC(&bitmap);

	Gdiplus::SolidBrush br(Gdiplus::Color(255, 255, 255));
	memDC.FillRectangle(&br, 0, 0, rc.Width(), rc.Height());

	Gdiplus::Image img(L"C:\\Users\\yshaa\\source\\repos\\MyComponent\\Transparent\\res\\bg.png");
	memDC.DrawImage(&img, 0, 0, img.GetWidth(), img.GetHeight());

	graphics.DrawImage(&bitmap, 0, 0);

	return TRUE;

}


void CTransparentDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnTimer(nIDEvent);
}


void CTransparentDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	//m_btn.ShowWindow(SW_SHOW);
	//m_btn.Invalidate();
}


void CTransparentDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	m_list.ModifyStyle(0, WS_CLIPSIBLINGS/* | WS_CLIPCHILDREN*/, 0);
}
