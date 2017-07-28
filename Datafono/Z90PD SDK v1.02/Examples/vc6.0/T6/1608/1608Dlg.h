// 1608Dlg.h : header file
//

#if !defined(AFX_1608DLG_H__090B418E_60AB_4AC2_8F18_CC5F58D3D6D4__INCLUDED_)
#define AFX_1608DLG_H__090B418E_60AB_4AC2_8F18_CC5F58D3D6D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMy1608Dlg dialog

class CMy1608Dlg : public CDialog
{
// Construction
public:
	CMy1608Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMy1608Dlg)
	enum { IDD = IDD_MY1608_DIALOG };
	CListBox	m_list1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy1608Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMy1608Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int st;
	HANDLE icdev;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_1608DLG_H__090B418E_60AB_4AC2_8F18_CC5F58D3D6D4__INCLUDED_)
