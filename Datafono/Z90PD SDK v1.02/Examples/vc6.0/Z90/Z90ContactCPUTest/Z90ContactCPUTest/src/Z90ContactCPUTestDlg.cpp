
// Z90ContactCPUTestDlg.cpp : ʵ���ļ�
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


// CZ90ContactCPUTestDlg �Ի���



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


// CZ90ContactCPUTestDlg ��Ϣ�������

BOOL CZ90ContactCPUTestDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CZ90ContactCPUTestDlg::OnPaint()
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
HCURSOR CZ90ContactCPUTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CZ90ContactCPUTestDlg::OnBnClickedSetcard()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	icdev = IC_InitComm_Baud(100, 115200);
	if ((int)icdev <= 0)
	{
		MessageBoxEx(NULL, "Failed to initialize the port!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	IC_DevBeep(icdev, 10);
}
