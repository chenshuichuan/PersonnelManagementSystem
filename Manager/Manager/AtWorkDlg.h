#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CAtWorkDlg �Ի���

class CAtWorkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAtWorkDlg)

public:
	CAtWorkDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAtWorkDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ATWORK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ֵ���
	virtual BOOL OnInitDialog();
	CComboBox m_ctrlWeek;
	CString m_strWeek;
	CString m_strExtra;

	CString m_Monday12;
	CString m_Monday34;
	CString m_Monday56;
	CString m_Monday78;
	CString m_Tuesday12;
	CString m_Tuesday34;
	CString m_Tuesday56;
	CString m_Tuesday78;
	CString m_Wednesday12;
	CString m_Wednesday34;
	CString m_Wednesday56;
	CString m_Wednesday78;
	CString m_Thursday12;
	//	CString m_Thursday56;
	CString m_Thursday34;
	CString m_Thursday56;
	CString m_Thursday78;
	//	CEdit m_Sunday12;
	CString m_Friday12;
	CString m_Friday34;
	CString m_Friday56;
	CString m_Friday78;
	CString m_Saturday12;
	CString m_Saturday34;
	CString m_Saturday56;
	CString m_Saturday78;
	CString m_Sunday12;
	CString m_Sunday34;
	CString m_Sunday56;
	CString m_Sunday78;

	afx_msg void OnCbnSelchangeCombo1();

	int m_intWeek;//ѡ�������
	void ShowSheet();
};
