#pragma once
#include "afxcmn.h"


// CSignDlg �Ի��� �ϰ�ǩ���Ի���
class CSignDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSignDlg)

public:
	CSignDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSignDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SIGN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �ϰ�ǩ����Ϣ��
	CListCtrl m_ctrlList;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();

	void InitDialogCtrl();
	void AddInforToListBox(long id, CString signer, 
		CTime start, CTime end, double hours,BOOL lock, CString extra);
	//sys=true��ʾ�ϰ�ǩ���ɹ�����Ϣ��false ��ʾ�°�ǩ���ɹ�����Ϣ
	void SignSucceed(bool sys);
	//�Ҽ��˵��ı༭����
	void RMEdit();
	//�Ҽ��˵���ɾ������
	void RMDelete();
	//�Ҽ��˵��Ľ�����������
	void LockAddUnLock(bool lock);

	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
};
