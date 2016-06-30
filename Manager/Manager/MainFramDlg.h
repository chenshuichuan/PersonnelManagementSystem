#pragma once
#include"SignDlg.h"
#include"RecordDlg.h"
#include"ReceiveBoxDlg.h"
#include"SendBoxDlg.h"
#include"CourseDlg.h"
#include"UserCentreDlg.h"
#include"AdminDlg.h"
#include "afxcmn.h"


// CMainFramDlg 对话框 主界面对话框类
class CMainFramDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainFramDlg)

public:
	CMainFramDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainFramDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_MAINFRAM };
public:
	CSignDlg m_signDlg;
	CRecordDlg m_recordDlg;
	CReceiveBoxDlg m_receiveDlg;
	CSendBoxDlg m_sendDlg;
	CCourseDlg m_courseDlg;
	CUserCentreDlg m_userDlg;
	CAdminDlg m_adminDlg;

	int m_nowIndex;//当前选择的tab项

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// tab控件
	CTabCtrl m_ctrlTab;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	void ShowWelcome();
	// 登录欢迎信息
	CString m_strLoginInfo;
	afx_msg void OnClose();
	afx_msg void OnPaint();
	
};
