#pragma once


// CRemindReceiveDlg �Ի���

class CRemindReceiveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRemindReceiveDlg)

public:
	CRemindReceiveDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRemindReceiveDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_REMIND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CString m_intNumberOfMessage;
	int m_intNumberOfMessage;
};
