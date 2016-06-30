// DeletePersonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "DeletePersonDlg.h"
#include "afxdialogex.h"


// CDeletePersonDlg 对话框

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


// CDeletePersonDlg 消息处理程序


void CDeletePersonDlg::OnBnClickedRadio1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_intOne = 1;
	m_intTwo = 0;
	UpdateData(FALSE);
}


void CDeletePersonDlg::OnBnClickedRadio2()
{
	// TODO:  在此添加控件通知处理程序代码
	m_intOne = 0;
	m_intTwo = 1;
	UpdateData(FALSE);
}


BOOL CDeletePersonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_intOne = 1;
	m_intTwo = 0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
