#pragma once
#include"SignDlg.h"
#include"RecordDlg.h"
#include"ReceiveBoxDlg.h"
#include"SendBoxDlg.h"
#include"CourseDlg.h"
#include"UserCentreDlg.h"
#include"AdminDlg.h"
#include "afxcmn.h"


// CMainFramDlg �Ի��� ������Ի�����
class CMainFramDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainFramDlg)

public:
	CMainFramDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainFramDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_MAINFRAM };
public:
	CSignDlg m_signDlg;
	CRecordDlg m_recordDlg;
	CReceiveBoxDlg m_receiveDlg;
	CSendBoxDlg m_sendDlg;
	CCourseDlg m_courseDlg;
	CUserCentreDlg m_userDlg;
	CAdminDlg m_adminDlg;

	int m_nowIndex;//��ǰѡ���tab��

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// tab�ؼ�
	CTabCtrl m_ctrlTab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	void ShowWelcome();
	// ��¼��ӭ��Ϣ
	CString m_strLoginInfo;
	afx_msg void OnClose();
	afx_msg void OnPaint();
	
};
