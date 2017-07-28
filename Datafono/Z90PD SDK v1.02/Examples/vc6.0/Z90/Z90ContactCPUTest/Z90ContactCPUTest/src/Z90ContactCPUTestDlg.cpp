
// Z90ContactCPUTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Z90ContactCPUTest.h"
#include "Z90ContactCPUTestDlg.h"
#include "afxdialogex.h"
#include "dcic32.h"

#pragma comment(lib, "dcic32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE icdev;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CZ90ContactCPUTestDlg 对话框



CZ90ContactCPUTestDlg::CZ90ContactCPUTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZ90ContactCPUTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZ90ContactCPUTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CZ90ContactCPUTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SETCARD, &CZ90ContactCPUTestDlg::OnBnClickedSetcard)
	ON_BN_CLICKED(IDC_REST, &CZ90ContactCPUTestDlg::OnBnClickedRest)
	ON_BN_CLICKED(IDC_APDU, &CZ90ContactCPUTestDlg::OnBnClickedApdu)
	ON_BN_CLICKED(IDC_INIT, &CZ90ContactCPUTestDlg::OnBnClickedInit)
END_MESSAGE_MAP()


// CZ90ContactCPUTestDlg 消息处理程序

BOOL CZ90ContactCPUTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	SetDlgItemText(IDC_EDIT_APDU, "0084000008");
	icdev = IC_InitComm_Baud(100, 115200);
	if ((int)icdev <= 0)
	{
		MessageBoxEx(NULL, "Failed to initialize the port!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return FALSE;
	}
	if ((int)icdev > 0)
	{
		GetDlgItem(IDC_INIT)->EnableWindow(FALSE);
		IC_DevBeep(icdev, 10);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZ90ContactCPUTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CZ90ContactCPUTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CZ90ContactCPUTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CZ90ContactCPUTestDlg::OnBnClickedSetcard()
{
	// TODO:  在此添加控件通知处理程序代码
	int st = -1;
	if (IsDlgButtonChecked(IDC_RADIO1) == BST_CHECKED)
	{
		st = IC_InitType(icdev, 12);
	}
	if (IsDlgButtonChecked(IDC_RADIO2) == BST_CHECKED)
	{
		st = IC_InitType(icdev, 13);
	}
	if ((IsDlgButtonChecked(IDC_RADIO1) == BST_UNCHECKED) && (IsDlgButtonChecked(IDC_RADIO2) == BST_UNCHECKED))
	{
		MessageBoxEx(NULL, "Selcet the card slot which will be operated", "Warnning", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	if (st)
	{
		MessageBoxEx(NULL, "Failed to set the card slot!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	MessageBoxEx(NULL, "Succeed to set the card slot!", "Information", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
}


void CZ90ContactCPUTestDlg::OnBnClickedRest()
{
	// TODO:  在此添加控件通知处理程序代码
	int st = -1;
	unsigned char rlen;
	unsigned char redata[200] = "\0";
	st = IC_CpuReset_Hex(icdev, &rlen, redata);
	if (st)
	{
		MessageBoxEx(NULL, "Failed to reset the card!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	SetDlgItemText(IDC_RESETINFO, (char *)redata);
}


void CZ90ContactCPUTestDlg::OnBnClickedApdu()
{
	// TODO:  在此添加控件通知处理程序代码
	int st = -1;
	CString str;
	unsigned char slen;
	unsigned char sdata[200] = "\0";
	unsigned char rlen = 0;
	unsigned char rdata[400] = "\0";

	GetDlgItemText(IDC_EDIT_APDU, str);
	memcpy(sdata, str, str.GetLength());
	slen = str.GetLength() / 2;

	st = IC_CpuApdu_Hex(icdev, slen, sdata, &rlen, rdata);
	if (st)
	{
		MessageBoxEx(NULL, "Failed to send APDU!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	SetDlgItemText(IDC_EDIT_RESPONSE, (char *)rdata);
}


void CZ90ContactCPUTestDlg::OnBnClickedInit()
{
	// TODO:  在此添加控件通知处理程序代码
	icdev = IC_InitComm_Baud(100, 115200);
	if ((int)icdev <= 0)
	{
		MessageBoxEx(NULL, "Failed to initialize the port!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	IC_DevBeep(icdev, 10);
}
