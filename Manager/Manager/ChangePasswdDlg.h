#pragma once
#include "afxwin.h"


// CChangePasswdDlg �Ի���

class CChangePasswdDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChangePasswdDlg)

public:
	CChangePasswdDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangePasswdDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1_CHANGE_PASSWD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strOld;
	CString m_strNew2;
	CString m_strNew1;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
