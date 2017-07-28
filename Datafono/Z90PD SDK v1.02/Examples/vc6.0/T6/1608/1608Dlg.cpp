// 1608Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "1608.h"
#include "1608Dlg.h"
#include "dcic32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy1608Dlg dialog

CMy1608Dlg::CMy1608Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy1608Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy1608Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1608Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy1608Dlg)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy1608Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy1608Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy1608Dlg message handlers

BOOL CMy1608Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	icdev=0;
	st=-1;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy1608Dlg::OnPaint() 
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
HCURSOR CMy1608Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMy1608Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	icdev=IC_InitComm(1);
	if ((int)icdev<=0)
	{
		m_list1.AddString ("IC_InitComm Error");
		return;
	}
	m_list1.AddString ("IC_InitComm OK");
	st=IC_InitType(icdev,208);
	if (st<0)
	{
		m_list1.AddString ("IC_InitType Error");
		return;
	}
	m_list1.AddString ("IC_InitType ok");
}

void CMy1608Dlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	unsigned char password[4]={0};
	unsigned char redata[256]={0};
	unsigned char wrdata[256]={"abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789"};
	
	st=IC_Status(icdev);
	if (st<0)
	{
		m_list1.AddString ("IC_Status Error");
		return;
	}
	if(st==1)
	{
		m_list1.AddString ("NO card");
		return;
	}
	m_list1.AddString ("IC_Status OK");	
	password[0]=0x34;
	password[1]=0x34;
	password[2]=0x34;
	st=IC_CheckWPassword(icdev,7,password);	
	if (st<0)
	{
		m_list1.AddString ("IC_CheckWPassword 7 Error");
		return;
	}
	m_list1.AddString("IC_CheckWPassword 7 ok");

	st=IC_ReadConfigZone_Hex(icdev,20,100,redata);
	if (st<0)
	{
		m_list1.AddString ("IC_ReadConfigZone_Hex Error");
		return;
	}
	m_list1.AddString("IC_ReadConfigZone_Hex ok");
	m_list1.AddString((const char*)redata);
	
	st=IC_SetUserZone(icdev,0);
	if (st<0)
	{
		m_list1.AddString ("IC_SetUserZone Error");
		return;
	}
	m_list1.AddString("IC_SetUserZone ok");

	st=IC_WriteUserZone(icdev,20,100,wrdata);
	if (st<0)
	{
		m_list1.AddString ("IC_WriteUserZone Error");
		return;
	}
	m_list1.AddString("IC_WriteUserZone ok");

	st=IC_ReadUserZone(icdev,20,100,redata);
	if (st<0)
	{
		m_list1.AddString ("IC_ReadUserZone Error");
		return;
		EndDialog(0);
	}
	m_list1.AddString("IC_ReadUserZone ok");
	m_list1.AddString((const char*)redata);
	
}

void CMy1608Dlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	IC_ExitComm(icdev);
	OnOK();
}
