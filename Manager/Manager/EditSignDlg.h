#pragma once
#include "afxwin.h"


// CEditSignDlg 对话框

class CEditSignDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditSignDlg)

public:
	CEditSignDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEditSignDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_EDIT_SIGN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSigner;
	BOOL m_strLock;
	virtual void OnOK();
//	CString m_strEndTime;
	CString m_strYearMonth;
	CString m_strStartYM;
	int m_intStartDay;
	int m_intStartHour;
	int m_intStartMin;
	int m_intEndDay;
	int m_intEndHour;
//	CEdit m_intEndMin;
	int m_intEndMin;
};
