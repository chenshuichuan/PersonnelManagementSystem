#pragma once
#include "afxcmn.h"


// CSignDlg 对话框 上班签到对话框
class CSignDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSignDlg)

public:
	CSignDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSignDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SIGN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 上班签到信息表
	CListCtrl m_ctrlList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();

	void InitDialogCtrl();
	void AddInforToListBox(long id, CString signer, 
		CTime start, CTime end, double hours,BOOL lock, CString extra);
	//sys=true显示上班签到成功的信息，false 显示下班签到成功的信息
	void SignSucceed(bool sys);
	//右键菜单的编辑功能
	void RMEdit();
	//右键菜单的删除功能
	void RMDelete();
	//右键菜单的解锁锁定功能
	void LockAddUnLock(bool lock);

	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
