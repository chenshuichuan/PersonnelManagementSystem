#pragma once


// CDeletePersonDlg 对话框

class CDeletePersonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeletePersonDlg)

public:
	CDeletePersonDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeletePersonDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_DELETE_PERSON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	int m_intOne;
	int m_intTwo;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	virtual BOOL OnInitDialog();
};
