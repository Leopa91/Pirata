
// Z90GetPasswordDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CZ90GetPasswordDlg 对话框
class CZ90GetPasswordDlg : public CDialogEx
{
// 构造
public:
	CZ90GetPasswordDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_Z90GETPASSWORD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list;
	afx_msg void OnBnClickedInit();
};
