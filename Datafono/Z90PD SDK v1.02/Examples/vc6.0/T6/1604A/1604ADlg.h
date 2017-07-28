// 1604ADlg.h : header file
//

#if !defined(AFX_1604ADLG_H__2B2BF6D9_143F_4084_8D9C_6FB7AA9E7758__INCLUDED_)
#define AFX_1604ADLG_H__2B2BF6D9_143F_4084_8D9C_6FB7AA9E7758__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy1604ADlg dialog

class CMy1604ADlg : public CDialog
{
// Construction
public:
	int st;
	HANDLE icdev;
	CMy1604ADlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy1604ADlg)
	enum { IDD = IDD_MY1604A_DIALOG };
	CListBox	m_list1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy1604ADlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy1604ADlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_1604ADLG_H__2B2BF6D9_143F_4084_8D9C_6FB7AA9E7758__INCLUDED_)
