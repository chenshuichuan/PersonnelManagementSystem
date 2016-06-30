#pragma once
#include "afxcmn.h"
#include"RemindReceiveDlg.h"

// CReceiveBoxDlg 对话框 收信箱对话框
class CReceiveBoxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReceiveBoxDlg)

public:
	CReceiveBoxDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReceiveBoxDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_RECEIVEBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtrRead();
	afx_msg void OnBnClickedBtrDelete();
	afx_msg void OnBnClickedBtrRefrash();
	CListCtrl m_ctrlList;
	virtual BOOL OnInitDialog();

	//初始化控件数据
	void InitDialogCtrl();
	//将数据添加到list中
	void  AddInforToListBox(long id, CString signer,
		CTime start, CString infor, CString level, BOOL noRead);
	int m_haveNoRead;//存在未读信息，收件箱初始化时判读是否显示提醒用户

	//右键菜单的编辑功能
	void RMRead();
	//右键菜单的删除功能
	void RMDelete();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);

	CRemindReceiveDlg *m_dlg;
};
