#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "atltime.h"


// CRecordDlg �Ի��� ֵ����Ϣ��¼��
class CRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRecordDlg)

public:
	CRecordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRecordDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_RECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ctrlList;

	virtual BOOL OnInitDialog();

	//�ڿؼ��ϼ�������
	void InitDialogCtrl(CString strSQL);
	void InitFindCtrl();
	void AddInforToListBox(long id, CString signer,
		CTime start, CTime end,double hours,long week, CString extra);
	//�Ҽ��˵��ı༭����
	void RMEdit();
	//�Ҽ��˵���ɾ������
	void RMDelete();

	void GetStrSql();

	BOOL m_boolName;
	BOOL m_boolMonth;
	BOOL m_boolWeek;
	BOOL m_boolDay;
	CString m_strName;
	CComboBox m_ctrlName;
	CComboBox m_ctrlMonth;
	CString m_strMonth;
	CComboBox m_ctrlWeek;
	CString m_strWeek;
	CTime m_ctimeDay;
	CString m_strSQL;
	int m_intTotalTime;
	CString m_strTotalHours;
	int m_month;
	int m_week;

	afx_msg void OnBnClickedBtrecordFind();
	afx_msg void OnBnClickedBtrecordExport();
	afx_msg void OnBnClickedBtrecordRefrash();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo3();
	
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	CButton m_ctrlCheckMonth;
	CButton m_ctrlCheckWeek;
	CButton m_ctrlCheckDay;
};
