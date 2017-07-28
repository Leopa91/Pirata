
// Z90ContactCPUTestDlg.h : 头文件
//

#pragma once


// CZ90ContactCPUTestDlg 对话框
class CZ90ContactCPUTestDlg : public CDialogEx
{
// 构造
public:
	CZ90ContactCPUTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_Z90CONTACTCPUTEST_DIALOG };

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
	afx_msg void OnBnClickedSetcard();
	afx_msg void OnBnClickedRest();
	afx_msg void OnBnClickedApdu();
	afx_msg void OnBnClickedInit();
};
