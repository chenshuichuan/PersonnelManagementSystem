#pragma once
#include "afxwin.h"


// CSendInforDlg �Ի���

class CSendInforDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSendInforDlg)

public:
	CSendInforDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSendInforDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SEND_INFOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSender;
	CString m_strSendTime;
	CComboBox m_ctrlLevel;
	CString m_strLevel;
	CComboBox m_ctrlDepart;
	CString m_strDepart;
	CComboBox m_ctrlPerson;
	CString m_strPerson;
	CString m_strInfor;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};
