// DeletePersonDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "DeletePersonDlg.h"
#include "afxdialogex.h"


// CDeletePersonDlg �Ի���

IMPLEMENT_DYNAMIC(CDeletePersonDlg, CDialogEx)

CDeletePersonDlg::CDeletePersonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDeletePersonDlg::IDD, pParent)
	, m_strName(_T(""))
	, m_intOne(1)
	, m_intTwo(0)
{
	//UpdateData(FALSE);
}

CDeletePersonDlg::~CDeletePersonDlg()
{
}

void CDeletePersonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
}


BEGIN_MESSAGE_MAP(CDeletePersonDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CDeletePersonDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDeletePersonDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CDeletePersonDlg ��Ϣ�������


void CDeletePersonDlg::OnBnClickedRadio1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_intOne = 1;
	m_intTwo = 0;
	UpdateData(FALSE);
}


void CDeletePersonDlg::OnBnClickedRadio2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_intOne = 0;
	m_intTwo = 1;
	UpdateData(FALSE);
}


BOOL CDeletePersonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_intOne = 1;
	m_intTwo = 0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
