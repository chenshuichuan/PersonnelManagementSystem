#pragma once
#include "afxcmn.h"


// CAdminDlg 对话框 管理员管理对话框类
class CAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminDlg)

public:
	CAdminDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdminDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	//右键菜单的添加功能
	void RMAdd();
	//右键菜单的编辑功能
	void RMEdit();
	//右键菜单的删除功能
	void RMDelete();
	//在控件上加载数据
	void InitDialogCtrl();
	void AddInforToListBox(CString name,
		CString telephone, BOOL sex, CString academy, CString major, CString grade,
		CString depart,  CString extra, CString introduction);

	CListCtrl m_ctrlList;
	afx_msg void OnBnClickedBtaExport();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};
