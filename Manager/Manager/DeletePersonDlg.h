#pragma once


// CDeletePersonDlg �Ի���

class CDeletePersonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeletePersonDlg)

public:
	CDeletePersonDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeletePersonDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_DELETE_PERSON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	int m_intOne;
	int m_intTwo;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	virtual BOOL OnInitDialog();
};
