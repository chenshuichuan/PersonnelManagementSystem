#pragma once


// CReadInforDlg 对话框

class CReadInforDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReadInforDlg)

public:
	CReadInforDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReadInforDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_READ_INFOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSenderOrRecever;
	CString m_strName;
	CString m_strInforId;
	CString m_strTime;
	CString m_strLevel;
	CString m_strInfor;
	virtual void OnOK();
};
