
// Z90GetPasswordDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CZ90GetPasswordDlg �Ի���
class CZ90GetPasswordDlg : public CDialogEx
{
// ����
public:
	CZ90GetPasswordDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_Z90GETPASSWORD_DIALOG };

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
	CListBox m_list;
	afx_msg void OnBnClickedInit();
};
