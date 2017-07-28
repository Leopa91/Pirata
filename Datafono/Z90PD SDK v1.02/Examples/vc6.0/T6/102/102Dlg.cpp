// 102Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "102.h"
#include "102Dlg.h"
#include "dcic32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy102Dlg dialog

CMy102Dlg::CMy102Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy102Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMy102Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy102Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMy102Dlg)
	DDX_Control(pDX, IDC_LIST1, m_list1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMy102Dlg, CDialog)
	//{{AFX_MSG_MAP(CMy102Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy102Dlg message handlers

BOOL CMy102Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy102Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy102Dlg::OnPaint() 
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
HCURSOR CMy102Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMy102Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	
	//初始化串口
	unsigned char ver[10]={0};
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
	//给卡型号：102卡（32）

    st=IC_InitType(icdev,32);
	if (st<0)
	{
		m_list1.AddString("IC_InitType Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		m_list1.AddString("IC_InitType OK ,102 card");
	}
	st=IC_DevBeep(icdev,20);
	if (st)
	{
		m_list1.AddString("Beep Error");
	}
	else
	{
		m_list1.AddString("Beep Ok");
	}
	st=IC_ReadVer(icdev,ver);
	if (st)
	{
		m_list1.AddString("readver Error");
	}
	else
	{
		m_list1.AddString("ReadVer Ok");
		m_list1.AddString((const char *)ver);
	}

	
	m_list1.SetCurSel(m_list1.GetCount()-1);
}

void CMy102Dlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	
	//Test 102 card
	unsigned char ver[10];
    m_list1.AddString("102 Test Begin,Please Waiting....");
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
	
	
	st=IC_ReadVer(icdev,ver);
	if (st)
	{
		m_list1.AddString("readver Error");
	}
	else
	{
		m_list1.AddString("ReadVer Ok");
		m_list1.AddString((const char *)ver);
	}
	//核对密码：f0f0,读错误计数器 
    
	st=IC_ReadCount_102(icdev);
	if (st<0)
	{
		m_list1.AddString("IC_ReadCount_102 Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		CString strst;
		strst.Format("%d",st);
		m_list1.AddString("IC_ReadCount_102 OK ,Count is "+strst);
	}

	char Password[5]="F0F0";
	
    st=IC_CheckPass_102hex(icdev,(unsigned char *)Password);
	if (st<0)
	{
		m_list1.AddString("IC_CheckPass_102hex Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		m_list1.AddString("IC_CheckPass_102hex(f0f0) OK ");
	}

	//读写卡，102卡在写之前必须先擦除，然后比较读数据与写数据

	int offset;
	int length;
	offset=24;
	length=16;
	char WrData[17]="abcdefghijklmnop";
	char ReData[17];
	st=IC_Erase_102(icdev,offset,length);
	if (st<0)
	{
		m_list1.AddString("IC_Erase_102 Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		m_list1.AddString("IC_Erase_102 OK ");
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
return ;
	char NewPassword[5]="F0F0";
	
    st=IC_ChangePass_102hex(icdev,(unsigned char *)NewPassword);
	if (st<0)
	{
		m_list1.AddString("IC_ChangePass_102hex Error");
		m_list1.SetCurSel(m_list1.GetCount()-1);
		return;
	}
	else
	{
		m_list1.AddString("IC_ChangePass_102hex(f0f0) OK ");
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
		m_list1.AddString("IC_Down OK ,102 card");
	}
    m_list1.SetCurSel(m_list1.GetCount()-1);
}

void CMy102Dlg::OnButton3() 
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
