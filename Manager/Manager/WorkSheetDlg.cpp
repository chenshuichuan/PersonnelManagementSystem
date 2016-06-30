// WorkSheetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "WorkSheetDlg.h"
#include "afxdialogex.h"

// CWorkSheetDlg 对话框

IMPLEMENT_DYNAMIC(CWorkSheetDlg, CDialogEx)

CWorkSheetDlg::CWorkSheetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkSheetDlg::IDD, pParent)
{

}

CWorkSheetDlg::~CWorkSheetDlg()
{
}

void CWorkSheetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_ctrlTab);
}


BEGIN_MESSAGE_MAP(CWorkSheetDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CWorkSheetDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CWorkSheetDlg 消息处理程序


BOOL CWorkSheetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect tabRect;   // 标签控件客户区的位置和大小   
	m_ctrlTab.InsertItem(0, _T("值班表"));   // 插入第一个标签  
	m_ctrlTab.InsertItem(1, _T("空余时间表")); 

	//如此说来，这些字对话框的父窗口是tab 控件，而不是mainfram 窗口！！！？？？

	m_atWorkDlg.Create(IDD_DIALOG_ATWORK, &m_ctrlTab);
	m_totalWorkDlg.Create(IDD_DIALOG_TOTALWORK, &m_ctrlTab);    // 创建第一个标签页   

	m_ctrlTab.GetClientRect(&tabRect);    // 获取标签控件客户区Rect   
	// 调整tabRect，使其覆盖范围适合放置标签页   
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	// 根据调整好的tabRect放置子对话框，并设置为显示 
	m_atWorkDlg.SetWindowPos(NULL,
		tabRect.left, tabRect.top, tabRect.Width(),
		tabRect.Height(), SWP_SHOWWINDOW);
	m_totalWorkDlg.SetWindowPos(NULL,
		tabRect.left, tabRect.top, tabRect.Width(),
		tabRect.Height(), SWP_HIDEWINDOW);
	
	//有权限才能设置值班表
	if (theApp.m_privilege)
	{
		m_ctrlTab.InsertItem(2, _T("设置值班表"));
		m_setWorkDlg.Create(IDD_DIALOG_SETWORK, &m_ctrlTab);
		m_setWorkDlg.SetWindowPos(NULL,
			tabRect.left, tabRect.top, tabRect.Width(),
			tabRect.Height(), SWP_HIDEWINDOW);
	}

	m_nowTabIndex = 0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CWorkSheetDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	CRect tabRect;    // 标签控件客户区的Rect   
	// 获取标签控件客户区Rect，并对其调整，以适合放置标签页   
	m_ctrlTab.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	switch (m_nowTabIndex)//关闭上一标签对话框
	{
	case 0:
		m_atWorkDlg.SetWindowPos(NULL, tabRect.left,
			tabRect.top, tabRect.Width(),
			tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 1:
		m_totalWorkDlg.SetWindowPos(NULL, tabRect.left,
			tabRect.top, tabRect.Width(),
			tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 2:
		m_setWorkDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	
	default:
		break;
	}

	m_nowTabIndex = m_ctrlTab.GetCurSel();

	switch (m_nowTabIndex)//打开当前选择标签
	{
		// 如果标签控件当前选择标签为对话框，隐藏对话框   
	case 0:
		m_atWorkDlg.SetWindowPos(NULL, tabRect.left,
			tabRect.top, tabRect.Width(),
			tabRect.Height(), SWP_SHOWWINDOW);
		break;
	case 1:
		m_totalWorkDlg.SetWindowPos(NULL, tabRect.left,
			tabRect.top, tabRect.Width(),
			tabRect.Height(), SWP_SHOWWINDOW);
		break;
	case 2:
		m_setWorkDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	
	default:
		break;
	}
}
