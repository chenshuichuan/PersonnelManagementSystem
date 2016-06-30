
// ManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CManagerDlg �Ի��� ��¼�Ի�����
class CManagerDlg : public CDialogEx
{
// ����
public:
	CManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �û����������
	CString m_strPasswd;
	// �û��б�
	CComboBox m_ctrUser;
	// �û���
	CString m_strUserName;
    //��ʼ���ؼ�
	void InitCtrl();
	afx_msg void OnCbnSelchangeCblUser();
	afx_msg void OnBnClickedBtlLogin();
	afx_msg void OnClose();
	virtual void OnCancel();

	//����ϰ�ǩ���������������������ݼ�����
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
