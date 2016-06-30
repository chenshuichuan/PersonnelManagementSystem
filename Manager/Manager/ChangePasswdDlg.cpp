// ChangePasswdDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "ChangePasswdDlg.h"
#include "afxdialogex.h"


// CChangePasswdDlg 对话框

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


// CChangePasswdDlg 消息处理程序


BOOL CChangePasswdDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CChangePasswdDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	UpdateData(TRUE);
	if (m_strOld != theApp.m_strPasswd)
	{
		MessageBoxA("您输入的密码不正确，请重新输入！", "输入错误", MB_OK);
		m_strOld = "";
		UpdateData(FALSE);
		return;
	}
	if (m_strNew1.GetLength()<6)
	{
		MessageBoxA("您输入的密码的少于6个字符，请重新输入！", "输入错误", MB_OK);
		m_strNew1 = "";
		m_strNew2 = "";
		UpdateData(FALSE);
		return;
	}
	if (m_strNew1 != m_strNew2)
	{
		MessageBoxA("您两次输入的新密码不一致，请重新输入！", "输入错误", MB_OK);
		m_strNew1 = "";
		m_strNew2 = "";
		UpdateData(FALSE);
		return;
	}
	CDialogEx::OnOK();
}
