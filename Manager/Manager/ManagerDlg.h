
// ManagerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CManagerDlg 对话框 登录对话框类
class CManagerDlg : public CDialogEx
{
// 构造
public:
	CManagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 用户输入的密码
	CString m_strPasswd;
	// 用户列表
	CComboBox m_ctrUser;
	// 用户名
	CString m_strUserName;
    //初始化控件
	void InitCtrl();
	afx_msg void OnCbnSelchangeCblUser();
	afx_msg void OnBnClickedBtlLogin();
	afx_msg void OnClose();
	virtual void OnCancel();

	//检查上班签到情况，发现有问题的数据即锁定
	void CheckSign();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

public:
	void InitOpenGL();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void myfog();
	void mylist();
	void hehuac(int k);
	void hehua();
	void heiye();
	void moon();
	BOOL lkey;
	int listi;
	float jd;
	float bh[10][3];
	CClientDC *my_pDC;
	CRect my_oldRect;
	BOOL mytbar;
	BOOL mysbar;
	void myfirst();
	void mydraw();
	BOOL mypixelformat();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnOK();
};
