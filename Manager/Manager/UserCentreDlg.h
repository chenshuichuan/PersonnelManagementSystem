#pragma once
#include "afxwin.h"


// CUserCentreDlg �Ի��� ������Ϣ����
class CUserCentreDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserCentreDlg)

public:
	CUserCentreDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserCentreDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_USERCENTRE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_strName;
	CString m_strId;
	CString m_strSex;
	CString m_strJoinDate;
	CString m_strDepart;
	CString m_strAcademy;
	CString m_strMajor;
	CString m_strPhone;
	CString m_strExtra;
	afx_msg void OnBnClickedBtuModify();
	afx_msg void OnBnClickedBtuSave();
	afx_msg void OnBnClickedBtuPasswd();
	CEdit m_ctrlAcademy;
	CEdit m_ctrlMajor;
	CEdit m_ctrlPhone;
	CEdit m_ctrlExtra;
};
