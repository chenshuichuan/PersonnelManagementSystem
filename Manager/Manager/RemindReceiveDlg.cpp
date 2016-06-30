// RemindReceiveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "RemindReceiveDlg.h"
#include "afxdialogex.h"


// CRemindReceiveDlg 对话框

IMPLEMENT_DYNAMIC(CRemindReceiveDlg, CDialogEx)

CRemindReceiveDlg::CRemindReceiveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRemindReceiveDlg::IDD, pParent)
	, m_intNumberOfMessage(0)
{

}

CRemindReceiveDlg::~CRemindReceiveDlg()
{
}

void CRemindReceiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_intNumberOfMessage);
	DDX_Text(pDX, IDC_EDIT1, m_intNumberOfMessage);
}


BEGIN_MESSAGE_MAP(CRemindReceiveDlg, CDialogEx)
END_MESSAGE_MAP()


// CRemindReceiveDlg 消息处理程序
