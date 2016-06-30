#pragma once
#include "afxwin.h"


// CCourseDlg �Ի��� �α�Ի�����
class CCourseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCourseDlg)

public:
	CCourseDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCourseDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_COURSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrlPerson;
	CString m_strPerson;
	CComboBox m_ctrlWeek;
	CString m_strWeek;
	int m_intWeek;
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedBtcSave();
	virtual BOOL OnInitDialog();
	BOOL m_Monday12;
	BOOL m_Monday34;
	BOOL m_Monday56;
	BOOL m_Monday78;
	BOOL m_Tuesday12;
	BOOL m_Tuesday34;
	BOOL m_Tuesday56;
	BOOL m_Tuesday78;
	BOOL m_Wednesday12;
	BOOL m_Wednesday34;
	BOOL m_Wednesday56;
	BOOL m_Wednesday78;
	BOOL m_Thursday12;
	BOOL m_Thursday34;
	BOOL m_Thursday56;
	BOOL m_Thursday78;
	BOOL m_Friday12;
	BOOL m_Friday34;
	BOOL m_Friday56;
	BOOL m_Friday78;
	BOOL m_Saturday12;
	BOOL m_Saturday34;
	BOOL m_Saturday56;
	BOOL m_Saturday78;
	BOOL m_Sunday12;
	BOOL m_Sunday34;
	BOOL m_Sunday56;
	BOOL m_Sunday78;
	CString m_strState;

	void ShowCourse();//���ݵ�ǰ״̬��ʾ����ʱ���
	//void SetCourseCheck()
	CEdit m_ctrlExtra;
	CString m_strExtra;
	afx_msg void OnBnClickedBtcExport();
};
