
// Z90LCDTestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CZ90LCDTestDlg �Ի���
class CZ90LCDTestDlg : public CDialogEx
{
// ����
public:
	CZ90LCDTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_Z90LCDTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
