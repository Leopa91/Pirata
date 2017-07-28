// 102Dlg.h : header file
//

#if !defined(AFX_102DLG_H__3A0010B3_7AF9_44DF_89A5_2FA189ACA3F8__INCLUDED_)
#define AFX_102DLG_H__3A0010B3_7AF9_44DF_89A5_2FA189ACA3F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy102Dlg dialog

class CMy102Dlg : public CDialog
{
// Construction
public:
	CMy102Dlg(CWnd* pParent = NULL);	// standard constructor
    int st;
	HANDLE icdev;

// Dialog Data
	//{{AFX_DATA(CMy102Dlg)
	enum { IDD = IDD_MY102_DIALOG };
	CListBox	m_list1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy102Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy102Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
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

#endif // !defined(AFX_102DLG_H__3A0010B3_7AF9_44DF_89A5_2FA189ACA3F8__INCLUDED_)
