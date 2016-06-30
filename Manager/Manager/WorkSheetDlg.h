#pragma once
#include "afxcmn.h"
#include"SetWorkDlg.h"
#include"TotalWorkDlg.h"
#include"AtWorkDlg.h"

// CWorkSheetDlg 对话框

class CWorkSheetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkSheetDlg)

public:
	CWorkSheetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWorkSheetDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_WORKSHEET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_ctrlTab;
	int m_nowTabIndex;//当前选择的tab项
	CAtWorkDlg m_atWorkDlg;//值班表 对话框
	CTotalWorkDlg m_totalWorkDlg;//空余时间表对话框
	CSetWorkDlg m_setWorkDlg;//设置值班表对话框

	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
