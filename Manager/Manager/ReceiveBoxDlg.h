#pragma once
#include "afxcmn.h"
#include"RemindReceiveDlg.h"

// CReceiveBoxDlg �Ի��� ������Ի���
class CReceiveBoxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReceiveBoxDlg)

public:
	CReceiveBoxDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReceiveBoxDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_RECEIVEBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtrRead();
	afx_msg void OnBnClickedBtrDelete();
	afx_msg void OnBnClickedBtrRefrash();
	CListCtrl m_ctrlList;
	virtual BOOL OnInitDialog();

	//��ʼ���ؼ�����
	void InitDialogCtrl();
	//��������ӵ�list��
	void  AddInforToListBox(long id, CString signer,
		CTime start, CString infor, CString level, BOOL noRead);
	int m_haveNoRead;//����δ����Ϣ���ռ����ʼ��ʱ�ж��Ƿ���ʾ�����û�

	//�Ҽ��˵��ı༭����
	void RMRead();
	//�Ҽ��˵���ɾ������
	void RMDelete();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);

	CRemindReceiveDlg *m_dlg;
};
