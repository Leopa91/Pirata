
// Z90CPUtestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Z90CPUtest.h"
#include "Z90CPUtestDlg.h"
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


// CZ90CPUtestDlg �Ի���



CZ90CPUtestDlg::CZ90CPUtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CZ90CPUtestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZ90CPUtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CZ90CPUtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INIT, &CZ90CPUtestDlg::OnBnClickedInit)
	ON_BN_CLICKED(IDC_RFRESET, &CZ90CPUtestDlg::OnBnClickedRfreset)
	ON_BN_CLICKED(IDC_CARDRESET, &CZ90CPUtestDlg::OnBnClickedCardreset)
	ON_BN_CLICKED(IDC_APDU, &CZ90CPUtestDlg::OnBnClickedApdu)
END_MESSAGE_MAP()


// CZ90CPUtestDlg ��Ϣ�������

BOOL CZ90CPUtestDlg::OnInitDialog()
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
	SetDlgItemText(IDC_EDIT2, "0084000008");
	icdev = IC_InitComm_Baud(100, 115200);
	if ((int)icdev <= 0)
	{
		MessageBoxEx(NULL, "Failed to initialize the port!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	}
	if ((int)icdev > 0)
	{
		GetDlgItem(IDC_INIT)->EnableWindow(FALSE);
		IC_DevBeep(icdev, 10);
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CZ90CPUtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CZ90CPUtestDlg::OnPaint()
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
HCURSOR CZ90CPUtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CZ90CPUtestDlg::OnBnClickedInit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	icdev = IC_InitComm_Baud(100, 115200);
	if ((int)icdev <= 0)
	{
		MessageBoxEx(NULL, "Failed to  initiialize the port!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	IC_DevBeep(icdev, 10);
}


void CZ90CPUtestDlg::OnBnClickedRfreset()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int st = -1;
	st = IC_ResetMifare(icdev, 1);
	if (st)
	{
		MessageBoxEx(NULL, " failed to reset the RF module!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	MessageBoxEx(NULL, "Succeed to reset the RF module!", "Information", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
}


void CZ90CPUtestDlg::OnBnClickedCardreset()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int st = -1;
	unsigned char len = 0;
	unsigned char re_data[100] = "\0";
	unsigned char snr[20] = "\0";
	st = IC_Card_Hex(icdev, 0, snr);
	if (st)
	{
		MessageBoxEx(NULL, "Failed to find card!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	IC_Config_Card(icdev, 'A');
	st = IC_Pro_Resethex(icdev, &len, re_data);
	if (st)
	{
		MessageBoxEx(NULL, "Card reset error!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	SetDlgItemText(IDC_EDIT1, (char *)re_data);
}


void CZ90CPUtestDlg::OnBnClickedApdu()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int st = -1;
	CString str;
	unsigned char sendata[1024] = "\0";
	unsigned char recdata[1024] = "\0";
	unsigned int slen;
	unsigned int rlen;
	GetDlgItemText(IDC_EDIT2, str);
	memcpy(sendata, str, str.GetLength());
	slen = str.GetLength() / 2;
	st = IC_Pro_Commandlinkhex(icdev, slen, sendata, &rlen, recdata, 7, 48);
	if (st)
	{
		MessageBoxEx(NULL, "Failed to send APDU to the device!", "Error", MB_OK, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
		return;
	}
	SetDlgItemText(IDC_EDIT3, (char *)recdata);
}
