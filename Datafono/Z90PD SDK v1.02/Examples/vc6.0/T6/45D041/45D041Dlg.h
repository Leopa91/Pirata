// 45D041Dlg.h : header file
//

#if !defined(AFX_45D041DLG_H__02D2518A_B0EC_41A6_BA93_0692A7D2B279__INCLUDED_)
#define AFX_45D041DLG_H__02D2518A_B0EC_41A6_BA93_0692A7D2B279__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy45D041Dlg dialog

class CMy45D041Dlg : public CDialog
{
// Construction
public:
	int st;
	HANDLE icdev;
	CMy45D041Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy45D041Dlg)
	enum { IDD = IDD_MY45D041_DIALOG };
	CListBox	m_list1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy45D041Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy45D041Dlg)
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

#endif // !defined(AFX_45D041DLG_H__02D2518A_B0EC_41A6_BA93_0692A7D2B279__INCLUDED_)
