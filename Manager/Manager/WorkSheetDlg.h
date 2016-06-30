#pragma once
#include "afxcmn.h"
#include"SetWorkDlg.h"
#include"TotalWorkDlg.h"
#include"AtWorkDlg.h"

// CWorkSheetDlg �Ի���

class CWorkSheetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWorkSheetDlg)

public:
	CWorkSheetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWorkSheetDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_WORKSHEET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_ctrlTab;
	int m_nowTabIndex;//��ǰѡ���tab��
	CAtWorkDlg m_atWorkDlg;//ֵ��� �Ի���
	CTotalWorkDlg m_totalWorkDlg;//����ʱ���Ի���
	CSetWorkDlg m_setWorkDlg;//����ֵ���Ի���

	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
