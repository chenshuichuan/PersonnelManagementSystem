#pragma once
#include "afxcmn.h"


// CSendBoxDlg �Ի��� ����Ϣ�Ի���
class CSendBoxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSendBoxDlg)

public:
	CSendBoxDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSendBoxDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SENDBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ctrlList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtsRead();
	afx_msg void OnBnClickedBtsDelete();
	afx_msg void OnBnClickedBtsSeng();
	//��ʼ���ؼ�����
	void InitDialogCtrl();
	//��������ӵ�list��
	void  AddInforToListBox(long id, CString signer,
		CTime start, CString infor, CString level );
	//�Ҽ��˵��Ĳ鿴����
	void RMRead();
	//�Ҽ��˵���ɾ������
	void RMDelete();

	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
