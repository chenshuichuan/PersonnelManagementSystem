// ReadInforDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "ReadInforDlg.h"
#include "afxdialogex.h"


// CReadInforDlg �Ի���

IMPLEMENT_DYNAMIC(CReadInforDlg, CDialogEx)

CReadInforDlg::CReadInforDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReadInforDlg::IDD, pParent)
	, m_strSenderOrRecever(_T(""))
	, m_strName(_T(""))
	, m_strInforId(_T(""))
	, m_strTime(_T(""))
	, m_strLevel(_T(""))
	, m_strInfor(_T(""))
{

}

CReadInforDlg::~CReadInforDlg()
{
}

void CReadInforDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_RSNER, m_strSenderOrRecever);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_strInforId);
	DDX_Text(pDX, IDC_EDIT3, m_strTime);
	DDX_Text(pDX, IDC_EDIT4, m_strLevel);
	DDX_Text(pDX, IDC_EDIT5, m_strInfor);
}


BEGIN_MESSAGE_MAP(CReadInforDlg, CDialogEx)
END_MESSAGE_MAP()


// CReadInforDlg ��Ϣ�������


void CReadInforDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}
