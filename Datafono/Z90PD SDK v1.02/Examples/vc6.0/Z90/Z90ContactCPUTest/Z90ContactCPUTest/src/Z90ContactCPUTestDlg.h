
// Z90ContactCPUTestDlg.h : ͷ�ļ�
//

#pragma once


// CZ90ContactCPUTestDlg �Ի���
class CZ90ContactCPUTestDlg : public CDialogEx
{
// ����
public:
	CZ90ContactCPUTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_Z90CONTACTCPUTEST_DIALOG };

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
	afx_msg void OnBnClickedSetcard();
	afx_msg void OnBnClickedRest();
	afx_msg void OnBnClickedApdu();
	afx_msg void OnBnClickedInit();
};
