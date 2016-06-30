#pragma once
#include "afxwin.h"


// CAddUserDlg 对话框

class CAddUserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddUserDlg)

public:
	CAddUserDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddUserDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_ADDUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlName;
	CString m_strName;
	CString m_strID;
	CComboBox m_ctrlSex;
	CString m_strSex;
	CString m_strJoinDate;
	CComboBox m_ctrlDepart;
	CComboBox m_ctrlPost;
	CString m_strPost;
	CString m_strDepart;
	CString m_strAcademy;
	CString m_strMajor;
	CString m_strPhone;
	CString m_strPasswd;
	CComboBox m_ctrlPrivilige;
	CString m_strPrivilige;
	CString m_strIntroduction;

	bool is_edit;
	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};
