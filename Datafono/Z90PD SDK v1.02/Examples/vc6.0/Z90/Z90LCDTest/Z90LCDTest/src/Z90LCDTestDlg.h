
// Z90LCDTestDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CZ90LCDTestDlg 对话框
class CZ90LCDTestDlg : public CDialogEx
{
// 构造
public:
	CZ90LCDTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_Z90LCDTEST_DIALOG };

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
	CComboBox m_combo;
	CString m_buff;
	int m_line;
	int m_offset;
	afx_msg void OnBnClickedInit();
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedClear();
	afx_msg void OnBnClickedShow();
	afx_msg void OnBnClickedDispaly();
};
