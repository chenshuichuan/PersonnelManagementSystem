#pragma once
#include "afxcmn.h"


// CSendBoxDlg 对话框 发信息对话框
class CSendBoxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSendBoxDlg)

public:
	CSendBoxDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSendBoxDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SENDBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ctrlList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtsRead();
	afx_msg void OnBnClickedBtsDelete();
	afx_msg void OnBnClickedBtsSeng();
	//初始化控件数据
	void InitDialogCtrl();
	//将数据添加到list中
	void  AddInforToListBox(long id, CString signer,
		CTime start, CString infor, CString level );
	//右键菜单的查看功能
	void RMRead();
	//右键菜单的删除功能
	void RMDelete();

	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
