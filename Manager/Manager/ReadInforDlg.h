#pragma once


// CReadInforDlg �Ի���

class CReadInforDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReadInforDlg)

public:
	CReadInforDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReadInforDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_READ_INFOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSenderOrRecever;
	CString m_strName;
	CString m_strInforId;
	CString m_strTime;
	CString m_strLevel;
	CString m_strInfor;
	virtual void OnOK();
};
