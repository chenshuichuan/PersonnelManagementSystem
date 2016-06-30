#pragma once
#include "afxwin.h"


// CTotalWorkDlg 对话框

class CTotalWorkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTotalWorkDlg)

public:
	CTotalWorkDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTotalWorkDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_TOTALWORK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrlComb;
	CString m_strComb;
	CString m_Monday12;
	CString m_Monday34;
	CString m_Monday56;
	CString m_Monday78;
	CString m_Tuesday12;
	CString m_Tuesday34;
	CString m_Tuesday56;
	CString m_Tuesday78;
	CString m_Wednesday12;
	CString m_Wednesday34;
	CString m_Wednesday56;
	CString m_Wednesday78;
	CString m_Thursday12;
//	CString m_Thursday56;
	CString m_Thursday34;
	CString m_Thursday56;
	CString m_Thursday78;
//	CEdit m_Sunday12;
	CString m_Friday12;
	CString m_Friday34;
	CString m_Friday56;
	CString m_Friday78;
	CString m_Saturday12;
	CString m_Saturday34;
	CString m_Saturday56;
	CString m_Saturday78;
	CString m_Sunday12;
	CString m_Sunday34;
	CString m_Sunday56;
	CString m_Sunday78;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();

	int m_intWeek;//选择的周数
	void ShowSheet();//显示空余时间表
	CString m_strExtra;
	afx_msg void OnBnClickedButton1();
};
