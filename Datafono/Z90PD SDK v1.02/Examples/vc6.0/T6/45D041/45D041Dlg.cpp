// 45D041Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "45D041.h"
#include "45D041Dlg.h"
#include "dcic32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy45D041Dlg dialog

CMy45D041Dlg::CMy45D041Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy45D041Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy45D041Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy45D041Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy45D041Dlg)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy45D041Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy45D041Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy45D041Dlg message handlers

BOOL CMy45D041Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy45D041Dlg::OnPaint() 
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
HCURSOR CMy45D041Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMy45D041Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	//初始化串口

	icdev=IC_InitComm(0);
	if((int)icdev<0) 
	{
		m_list1.AddString("IC_InitComm Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		m_list1.AddString("IC_InitCOmm ok");
		m_list1.SetCurSel(m_list1.GetCount()-1);
	}
	//给卡型号：45DB041卡（65）

    st=IC_InitType(icdev,65);
	if (st<0)
	{
		m_list1.AddString("IC_InitType Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		m_list1.AddString("IC_InitType OK ,45DB041 card");
	}
	m_list1.SetCurSel(m_list1.GetCount()-1);	
		
}

void CMy45D041Dlg::OnButton2() 
{
	// TODO: Add your control notification handler code here

	//Test 45DB041 card
    m_list1.AddString("45DB041 Test Begin,Please Waiting....");
	m_list1.SetCurSel(m_list1.GetCount()-1);
	
	MSG message;
		if(::PeekMessage(&message,NULL,0,0,PM_REMOVE))
		{
			::TranslateMessage(&message);
			::DispatchMessage(&message);
		}
	st=IC_Status(icdev);
	if (st<0)
	{
		m_list1.AddString ("IC_status error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
		m_list1.AddString ("IC_status OK");
	if (st==1)
	{
		m_list1.AddString ("Reader No card,Please Insert....");
		m_list1.SetCurSel(m_list1.GetCount()-1);
	    return;
	}
	if (st==0)
		m_list1.AddString ("Have card,Please Test");


	//读写卡，然后比较读数据与写数据

	int offset;
	int length;
	int page;
	page=2;
	offset=64;
	length=16;
	char WrData[17]="abcdefghijklmnop";
	char ReData[17];
	
	//st=IC_Write(icdev,offset,length,(unsigned char *)WrData);
	st=IC_DirectWrite(icdev,page,offset,length,(unsigned char *)WrData);
	if (st<0)
	{
		CString strst;
		strst.Format("%d",st);
		m_list1.AddString("IC_Write Error"+strst);
		m_list1.SetCurSel(m_list1.GetCount()-1);
		//return;
	}
	else
	{
		m_list1.AddString("IC_Write OK ");
	}
	//st=IC_Read(icdev,offset,length,(unsigned char *)ReData);
	st=IC_DirectRead(icdev,page,offset,length,(unsigned char *)ReData);
	if (st<0)
	{
		m_list1.AddString("IC_Read Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		m_list1.AddString("IC_Read OK ");
		ReData[16]=0;
		m_list1.AddString(ReData);
	}
	if(strncmp(ReData,WrData,16)==0)
	{
		m_list1.AddString("Comp Data OK");
    
	}
	else
	{
		m_list1.AddString("Comp Data Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}

    m_list1.AddString("45DB041 card Test OK");
    m_list1.SetCurSel(m_list1.GetCount()-1);		
}

void CMy45D041Dlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	
	//关闭串口
	if(int(icdev)>0)
	{
		st=IC_ExitComm(icdev);
		if(st!=0)
		{
			m_list1.AddString ("Exitcomm Error");
			m_list1.SetCurSel(m_list1.GetCount()-1);
		    return;
		}
		icdev=0;
	}
	OnOK();		
}
