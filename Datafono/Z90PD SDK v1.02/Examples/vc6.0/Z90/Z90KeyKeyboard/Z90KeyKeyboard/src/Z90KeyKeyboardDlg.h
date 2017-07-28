
// Z90KeyKeyboardDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CZ90KeyKeyboardDlg �Ի���
class CZ90KeyKeyboardDlg : public CDialogEx
{
// ����
public:
	CZ90KeyKeyboardDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_Z90KEYKEYBOARD_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	int m_time;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};