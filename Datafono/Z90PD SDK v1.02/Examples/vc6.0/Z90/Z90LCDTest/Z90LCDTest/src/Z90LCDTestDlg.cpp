
// Z90LCDTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Z90LCDTest.h"
#include "Z90LCDTestDlg.h"
#include "afxdialogex.h"
#include "dcic32.h"

#pragma comment(lib, "dcic32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE icdev;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CZ90LCDTestDlg �Ի���



CZ90LCDTestDlg::CZ90LCDTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZ90LCDTestDlg::IDD, pParent)
	, m_buff(_T(""))
	, m_line(0)
	, m_offset(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZ90LCDTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT_BUFFER, m_buff);
	DDX_Text(pDX, IDC_EDIT_LINE, m_line);
	DDX_Text(pDX, IDC_EDIT_OFFSET, m_offset);
}

BEGIN_MESSAGE_MAP(CZ90LCDTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INIT, &CZ90LCDTestDlg::OnBnClickedInit)
	ON_BN_CLICKED(IDC_OPEN, &CZ90LCDTestDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_CLOSE, &CZ90LCDTestDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_CLEAR, &CZ90LCDTestDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_SHOW, &CZ90LCDTestDlg::OnBnClickedShow)
	ON_BN_CLICKED(IDC_DISPALY, &CZ90LCDTestDlg::OnBnClickedDispaly)
END_MESSAGE_MAP()


// CZ90LCDTestDlg ��Ϣ�������

BOOL CZ90LCDTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_combo.SetCurSel(0);
	m_line = 0;
	m_offset = 0;
	m_buff = "abc123";
	UpdateData(FALSE);
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CZ90LCDTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CZ90LCDTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CZ90LCDTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CZ90LCDTestDlg::OnBnClickedInit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	icdev = IC_InitComm_Baud(100, 115200);
	if ((int)icdev <= 0)
	{
		MessageBoxEx(NULL, "Failed to initialize the port!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	IC_DevBeep(icdev, 10);
}


void CZ90LCDTestDlg::OnBnClickedOpen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int st = IC_CtlBackLight(icdev, 1);
	if (st)
	{
		MessageBoxEx(NULL, "Failed to open the backlight!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	MessageBoxEx(NULL, "Succeed to  open the backlight!", "Information", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
}


void CZ90LCDTestDlg::OnBnClickedClose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int st = IC_CtlBackLight(icdev, 0);
	if (st)
	{
		MessageBoxEx(NULL, "Failed to close the backlight!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	MessageBoxEx(NULL, "Succeed to close the backlight!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
}


void CZ90LCDTestDlg::OnBnClickedClear()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int st = IC_LcdClrScrn(icdev, 2);
	if (st)
	{
		MessageBoxEx(NULL, "Failed to clear the screen!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	MessageBoxEx(NULL, "Succeed to close the backlight!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
}


void CZ90LCDTestDlg::OnBnClickedShow()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int st = -1;
	char buffer[20] = "\0";
	memcpy(buffer, m_buff, m_buff.GetLength());
	st = IC_DispInfo(icdev, m_line, m_offset, buffer);
	if (st)
	{
		MessageBoxEx(NULL, "Failed to display the specific buffer!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	IC_DevBeep(icdev, 10);
}


void CZ90LCDTestDlg::OnBnClickedDispaly()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int st = -1;
	int index = m_combo.GetCurSel();
	switch (index)
	{
	case 0:
		st = IC_DispLcd(icdev, index + 1);
		break;
	case 6:
		st = IC_DispLcd(icdev, index + 3);
		break;
	default:
		st = IC_DispLcd(icdev, index + 2);
		break;
	}
	if (st)
	{
		MessageBoxEx(NULL, "Failed to display the system information!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	IC_DevBeep(icdev, 10);
}
