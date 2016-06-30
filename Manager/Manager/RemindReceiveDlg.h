#pragma once


// CRemindReceiveDlg 对话框

class CRemindReceiveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRemindReceiveDlg)

public:
	CRemindReceiveDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRemindReceiveDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_REMIND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString m_intNumberOfMessage;
	int m_intNumberOfMessage;
};
