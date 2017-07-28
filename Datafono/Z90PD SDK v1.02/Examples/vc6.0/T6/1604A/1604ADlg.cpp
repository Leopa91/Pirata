// 1604ADlg.cpp : implementation file
//

#include "stdafx.h"
#include "1604A.h"
#include "1604ADlg.h"
#include "dcic32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy1604ADlg dialog

CMy1604ADlg::CMy1604ADlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy1604ADlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy1604ADlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1604ADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy1604ADlg)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy1604ADlg, CDialog)
	//{{AFX_MSG_MAP(CMy1604ADlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy1604ADlg message handlers

BOOL CMy1604ADlg::OnInitDialog()
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

void CMy1604ADlg::OnPaint() 
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
HCURSOR CMy1604ADlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMy1604ADlg::OnButton1() 
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
	//给卡型号：1604A卡（160）

    st=IC_InitType(icdev,160);
	if (st<0)
	{
		m_list1.AddString("IC_InitType Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		m_list1.AddString("IC_InitType OK ,1604A card");
	}
	m_list1.SetCurSel(m_list1.GetCount()-1);	
}

void CMy1604ADlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	
	//Test 1604A card
    m_list1.AddString("1604A Test Begin,Please Waiting....");
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
	
	
	//核对密码：f0f0,读错误计数器 
    
	st=IC_ReadCount_1604(icdev,0);
	if (st<0)
	{
		m_list1.AddString("IC_ReadCount_1604A Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		CString strst;
		strst.Format("%d",st);
		m_list1.AddString("IC_ReadCount_1604 OK ,Count is "+strst);
	}

	char Password[5]="F0F0";
	
	
    st=IC_CheckPass_1604hex(icdev,0,(unsigned char *)Password);
	if (st<0)
	{
		m_list1.AddString("IC_CheckPass_1604hex Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		m_list1.AddString("IC_CheckPass_1604hex(f0f0) OK ");
	}

	//读写卡，1604卡在写之前必须先擦除，然后比较读数据与写数据

	int offset;
	int length;
	offset=30;
	length=16;
	char WrData[17]="abcdefghijklmnop";
	char ReData[17];
	st=IC_Erase(icdev,offset,length);
	if (st<0)
	{
		m_list1.AddString("IC_Erase_1604 Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		m_list1.AddString("IC_Erase_1604 OK ");
	}
	st=IC_Write(icdev,offset,length,(unsigned char *)WrData);
	if (st<0)
	{
		m_list1.AddString("IC_Write Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		m_list1.AddString("IC_Write OK ");
	}
	st=IC_Read(icdev,offset,length,(unsigned char *)ReData);
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

	//修改密码

	char NewPassword[5]="F0F0";
	
    st=IC_ChangePass_1604hex(icdev,0,(unsigned char *)NewPassword);
	if (st<0)
	{
		m_list1.AddString("IC_ChangePass_1604hex Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		m_list1.AddString("IC_ChangePass_1604hex(f0f0) OK ");
	}

	//下电操作
	
	st=IC_Down(icdev);
    if (st<0)
	{
		m_list1.AddString("IC_Down Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		m_list1.AddString("IC_Down OK ,1604A card");
	}
    m_list1.SetCurSel(m_list1.GetCount()-1);	
}

void CMy1604ADlg::OnButton3() 
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
