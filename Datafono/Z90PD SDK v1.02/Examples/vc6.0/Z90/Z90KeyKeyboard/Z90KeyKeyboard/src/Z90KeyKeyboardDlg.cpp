
// Z90KeyKeyboardDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Z90KeyKeyboard.h"
#include "Z90KeyKeyboardDlg.h"
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


// CZ90KeyKeyboardDlg 对话框



CZ90KeyKeyboardDlg::CZ90KeyKeyboardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZ90KeyKeyboardDlg::IDD, pParent)
	, m_time(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZ90KeyKeyboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT3, m_time);
}

BEGIN_MESSAGE_MAP(CZ90KeyKeyboardDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CZ90KeyKeyboardDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CZ90KeyKeyboardDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CZ90KeyKeyboardDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CZ90KeyKeyboardDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CZ90KeyKeyboardDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CZ90KeyKeyboardDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CZ90KeyKeyboardDlg 消息处理程序

BOOL CZ90KeyKeyboardDlg::OnInitDialog()
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
	m_time = 20;
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
	icdev = IC_InitComm_Baud(100, 115200);
	if ((int)icdev <= 0)
	{
		MessageBoxEx(NULL, "Failed to initialize the port!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return FALSE;
	}
	IC_DevBeep(icdev, 10);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CZ90KeyKeyboardDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CZ90KeyKeyboardDlg::OnPaint()
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
HCURSOR CZ90KeyKeyboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CZ90KeyKeyboardDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	int st;

	//Download the master work key"91B0E58976438068"
	st = IC_InstallKbKey(icdev, 0, 8, (unsigned char *)"\x91\xB0\xE5\x89\x76\x43\x80\x68");
	if (st != 0)
	{
		MessageBoxEx(NULL, "Failed to download the mster key!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	//Download the work key "3B08B007FECD6DB5",the encrypted data with master key is "3a2c8094c22b0ab4"
	st = IC_InstallKbKey(icdev, 1, 8, (unsigned char *)"\x3a\x2c\x80\x94\xc2\x2b\x0a\xb4");
	if (st != 0)
	{
		MessageBoxEx(NULL, "Failed to download the work key", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	//Download the work key "9243fe1cd6d34a75",the encrypted data with master key is "E5D3668980DD1293"
	st = IC_InstallKbKey(icdev, 2, 8, (unsigned char *)"\xE5\xD3\x66\x89\x80\xDD\x12\x93");
	if (st != 0)
	{
		MessageBoxEx(NULL, "Failed to download the MAC key!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	IC_DevBeep(icdev, 10);
}


void CZ90KeyKeyboardDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	icdev = IC_InitComm_Baud(100, 115200);
	if ((int)icdev <= 0)
	{
		MessageBoxEx(NULL, "Failed to initialize the port!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	IC_DevBeep(icdev, 10);
	MessageBoxEx(NULL, "Succeed to initialize the port!", "Information", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
}


void CZ90KeyKeyboardDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	int st;

	st = IC_InstallKbKeyPro(icdev, 0xf0, 16, (unsigned char *)"\x91\xB0\xE5\x89\x76\x43\x80\x68\x11\x22\x33\x44\x55\x66\x77\x88", 1);
	if (st == 0)
	{
		MessageBoxEx(NULL, "SUcceed to clear the key!", "Information", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	else
	{
		MessageBoxEx(NULL, "Failed to clear the key!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
}


void CZ90KeyKeyboardDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	int st;
	CString str;
	unsigned char rlen, cpass[40];
	UpdateData(TRUE);

	//Card number is 5759990123456789（last 9 numbers are check words）Get PIN
	//Test user data: 0000003238006250
	memset(cpass, 0, 40);
	st = IC_GetEnPass(icdev, m_time, 16, (unsigned char *)"0000003238006250", &rlen, cpass);
	if (st != 0)
	{
		MessageBoxEx(NULL, "Failed to get PINBLOCK!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	switch (st)
	{
	case 0xa1:
		str = "user cancel to input";
		MessageBoxEx(NULL, str, "information", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		break;
	case 0xa2:
		str = "inputting time out";
		MessageBoxEx(NULL, str, "information", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		break;
	case 0x0:
		cpass[rlen] = '\0';
		SetDlgItemText(IDC_EDIT1, (char *)cpass);
		st = IC_DispLcd(icdev, 7);
		break;
	default:
		MessageBoxEx(NULL, "Failed to get the Encrypted key!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	}

	return;
}


void CZ90KeyKeyboardDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	int st;
	unsigned char slen;
	unsigned char tempdata[512], senddata[512], recdata[512];
	CString Cstr;
	UpdateData(TRUE);
	((CEdit *)GetDlgItem(IDC_EDIT2))->GetWindowText(Cstr);
	memcpy(tempdata, Cstr, Cstr.GetLength());
	slen = Cstr.GetLength() / 2;
	hex2asc(tempdata, senddata, slen);

	st = IC_CreatMacECB(icdev, slen, senddata, recdata);
	if (st != 0)
	{
		MessageBoxEx(NULL, "Failed to create MAC", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}

	recdata[8] = '\0';
	((CEdit *)GetDlgItem(IDC_EDIT4))->SetWindowText((char *)recdata);
	UpdateData(FALSE);
	return;
}


void CZ90KeyKeyboardDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	int keyid = m_combo.GetCurSel();
	int st;

	st = IC_SetKbKeyID(icdev, keyid);
	if (st == 0)
	{
		MessageBoxEx(NULL, "Succeed to set the key type!", "information", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	else
	{
		MessageBoxEx(NULL, "Failed to set the key type!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}

}
