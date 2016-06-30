#pragma once
#include "afxwin.h"


// CChangePasswdDlg 对话框

class CChangePasswdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangePasswdDlg)

public:
	CChangePasswdDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangePasswdDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1_CHANGE_PASSWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strOld;
	CString m_strNew2;
	CString m_strNew1;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
