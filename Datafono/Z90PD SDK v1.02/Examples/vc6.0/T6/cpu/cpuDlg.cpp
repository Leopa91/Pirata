// cpuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cpu.h"
#include "cpuDlg.h"
#include "dcic32.h"

#pragma comment(lib, "dcic32.lib");

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCpuDlg dialog

CCpuDlg::CCpuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCpuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCpuDlg)
	m_type = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCpuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCpuDlg)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Radio(pDX, IDC_RADIO1, m_type);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCpuDlg, CDialog)
	//{{AFX_MSG_MAP(CCpuDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCpuDlg message handlers

BOOL CCpuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
    m_type=0;
	UpdateData(FALSE);
	ic_type=12;
	icdev = (HANDLE)-1;
	st=0;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCpuDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCpuDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCpuDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	//³õÊ¼»¯´®¿Ú    wfl 2003.12.10
	icdev = IC_InitComm_Baud(100,119200);
	if ((int)icdev<0)
	{
		m_list1.AddString ("IC_InitComm Error");
		return;
	}
	m_list1.AddString ("IC_InitComm ok");
}

void CCpuDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	st=IC_InitType(icdev,ic_type);
	if (st!=0)
	{
		m_list1.AddString ("IC_InitType Error");
		return;
	}
	int relen = -1;
	unsigned char redata[64] = "\0";

	st=IC_CpuReset_Hex(icdev,(unsigned char *)&relen,redata);
	if (st!=0)
	{
		CString temp;
		temp.Format("%d",st);
		m_list1.AddString ("IC_CpuReset_Hex Error,Error Number is "+temp);
		return;
	}
	m_list1.AddString ("IC_CpuReset_Hex ok");
	m_list1.AddString ((const char *)redata);
	unsigned char sedata[64]={"00A4040008A00000033301010100"};
	relen = -1;
	memset(redata,0,sizeof(redata));
	st=IC_CpuApduEXT_Hex(icdev,14,sedata,(__int16 *)&relen,redata);
	if (st!=0)
	{
		CString temp;
		temp.Format("%d",st);
		m_list1.AddString ("IC_CpuApdu_Hex Error,Error Number is "+temp);
		return;
	}
	m_list1.AddString ("IC_CpuApdu_Hex ok");
	m_list1.AddString ((const char *)redata);
	
}

void CCpuDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	if ((int)icdev>0)
	{
		IC_ExitComm(icdev);
		icdev=0;
	}
	OnOK();
}

void CCpuDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	ic_type=12;
}

void CCpuDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	ic_type=13;
	
}

void CCpuDlg::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	ic_type=14;
	
}

void CCpuDlg::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	ic_type=15;
	
}

BOOL CCpuDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	if ((int)icdev>0)
		IC_ExitComm(icdev);
	return CDialog::DestroyWindow();
}
