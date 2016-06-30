// ChangePasswdDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "ChangePasswdDlg.h"
#include "afxdialogex.h"


// CChangePasswdDlg �Ի���

IMPLEMENT_DYNAMIC(CChangePasswdDlg, CDialogEx)

CChangePasswdDlg::CChangePasswdDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangePasswdDlg::IDD, pParent)
	, m_strOld(_T(""))
	, m_strNew2(_T(""))
	, m_strNew1(_T(""))
{

}

CChangePasswdDlg::~CChangePasswdDlg()
{
}

void CChangePasswdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strOld);
	DDX_Text(pDX, IDC_EDIT3, m_strNew2);
	DDX_Text(pDX, IDC_EDIT2, m_strNew1);
}


BEGIN_MESSAGE_MAP(CChangePasswdDlg, CDialogEx)
END_MESSAGE_MAP()


// CChangePasswdDlg ��Ϣ�������


BOOL CChangePasswdDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CChangePasswdDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	UpdateData(TRUE);
	if (m_strOld != theApp.m_strPasswd)
	{
		MessageBoxA("����������벻��ȷ�����������룡", "�������", MB_OK);
		m_strOld = "";
		UpdateData(FALSE);
		return;
	}
	if (m_strNew1.GetLength()<6)
	{
		MessageBoxA("����������������6���ַ������������룡", "�������", MB_OK);
		m_strNew1 = "";
		m_strNew2 = "";
		UpdateData(FALSE);
		return;
	}
	if (m_strNew1 != m_strNew2)
	{
		MessageBoxA("����������������벻һ�£����������룡", "�������", MB_OK);
		m_strNew1 = "";
		m_strNew2 = "";
		UpdateData(FALSE);
		return;
	}
	CDialogEx::OnOK();
}
