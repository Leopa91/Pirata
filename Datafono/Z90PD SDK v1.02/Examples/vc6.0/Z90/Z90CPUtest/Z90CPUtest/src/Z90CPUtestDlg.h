
// Z90CPUtestDlg.h : ͷ�ļ�
//

#pragma once


// CZ90CPUtestDlg �Ի���
class CZ90CPUtestDlg : public CDialogEx
{
// ����
public:
	CZ90CPUtestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_Z90CPUTEST_DIALOG };

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
	afx_msg void OnBnClickedInit();
	afx_msg void OnBnClickedRfreset();
	afx_msg void OnBnClickedCardreset();
	afx_msg void OnBnClickedApdu();
};
