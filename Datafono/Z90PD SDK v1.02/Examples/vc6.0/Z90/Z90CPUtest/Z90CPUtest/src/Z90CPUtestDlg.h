
// Z90CPUtestDlg.h : 头文件
//

#pragma once


// CZ90CPUtestDlg 对话框
class CZ90CPUtestDlg : public CDialogEx
{
// 构造
public:
	CZ90CPUtestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_Z90CPUTEST_DIALOG };

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
	afx_msg void OnBnClickedInit();
	afx_msg void OnBnClickedRfreset();
	afx_msg void OnBnClickedCardreset();
	afx_msg void OnBnClickedApdu();
};
