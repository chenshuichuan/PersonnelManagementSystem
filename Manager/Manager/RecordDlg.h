#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "atltime.h"


// CRecordDlg 对话框 值班信息记录框
class CRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRecordDlg)

public:
	CRecordDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRecordDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_RECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ctrlList;

	virtual BOOL OnInitDialog();

	//在控件上加载数据
	void InitDialogCtrl(CString strSQL);
	void InitFindCtrl();
	void AddInforToListBox(long id, CString signer,
		CTime start, CTime end,double hours,long week, CString extra);
	//右键菜单的编辑功能
	void RMEdit();
	//右键菜单的删除功能
	void RMDelete();

	void GetStrSql();

	BOOL m_boolName;
	BOOL m_boolMonth;
	BOOL m_boolWeek;
	BOOL m_boolDay;
	CString m_strName;
	CComboBox m_ctrlName;
	CComboBox m_ctrlMonth;
	CString m_strMonth;
	CComboBox m_ctrlWeek;
	CString m_strWeek;
	CTime m_ctimeDay;
	CString m_strSQL;
	int m_intTotalTime;
	CString m_strTotalHours;
	int m_month;
	int m_week;

	afx_msg void OnBnClickedBtrecordFind();
	afx_msg void OnBnClickedBtrecordExport();
	afx_msg void OnBnClickedBtrecordRefrash();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	CButton m_ctrlCheckMonth;
	CButton m_ctrlCheckWeek;
	CButton m_ctrlCheckDay;
};
