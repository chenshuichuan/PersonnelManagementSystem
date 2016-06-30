#pragma once
#include "afxwin.h"


// CSetWorkDlg 对话框

class CSetWorkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetWorkDlg)

public:
	CSetWorkDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetWorkDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SETWORK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrlWeek;
	afx_msg void OnBnClickedBtSetAtwork();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtSetExport();

	CString m_strExtra;

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

	int m_intWeek;//选择的周数
	void ShowSheet();
	afx_msg void OnCbnSelchangeCombo1();
	CString m_strWeek;
	CString m_strSetInfor;
	afx_msg void OnBnClickedSetDelete();
};
