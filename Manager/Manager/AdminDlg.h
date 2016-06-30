#pragma once
#include "afxcmn.h"


// CAdminDlg �Ի��� ����Ա����Ի�����
class CAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdminDlg)

public:
	CAdminDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdminDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADMIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	//�Ҽ��˵�����ӹ���
	void RMAdd();
	//�Ҽ��˵��ı༭����
	void RMEdit();
	//�Ҽ��˵���ɾ������
	void RMDelete();
	//�ڿؼ��ϼ�������
	void InitDialogCtrl();
	void AddInforToListBox(CString name,
		CString telephone, BOOL sex, CString academy, CString major, CString grade,
		CString depart,  CString extra, CString introduction);

	CListCtrl m_ctrlList;
	afx_msg void OnBnClickedBtaExport();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
};
