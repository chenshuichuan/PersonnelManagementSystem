// WorkSheetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "WorkSheetDlg.h"
#include "afxdialogex.h"

// CWorkSheetDlg �Ի���

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


// CWorkSheetDlg ��Ϣ�������


BOOL CWorkSheetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect tabRect;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С   
	m_ctrlTab.InsertItem(0, _T("ֵ���"));   // �����һ����ǩ  
	m_ctrlTab.InsertItem(1, _T("����ʱ���")); 

	//���˵������Щ�ֶԻ���ĸ�������tab �ؼ���������mainfram ���ڣ�����������

	m_atWorkDlg.Create(IDD_DIALOG_ATWORK, &m_ctrlTab);
	m_totalWorkDlg.Create(IDD_DIALOG_TOTALWORK, &m_ctrlTab);    // ������һ����ǩҳ   

	m_ctrlTab.GetClientRect(&tabRect);    // ��ȡ��ǩ�ؼ��ͻ���Rect   
	// ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ   
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	// ���ݵ����õ�tabRect�����ӶԻ��򣬲�����Ϊ��ʾ 
	m_atWorkDlg.SetWindowPos(NULL,
		tabRect.left, tabRect.top, tabRect.Width(),
		tabRect.Height(), SWP_SHOWWINDOW);
	m_totalWorkDlg.SetWindowPos(NULL,
		tabRect.left, tabRect.top, tabRect.Width(),
		tabRect.Height(), SWP_HIDEWINDOW);
	
	//��Ȩ�޲�������ֵ���
	if (theApp.m_privilege)
	{
		m_ctrlTab.InsertItem(2, _T("����ֵ���"));
		m_setWorkDlg.Create(IDD_DIALOG_SETWORK, &m_ctrlTab);
		m_setWorkDlg.SetWindowPos(NULL,
			tabRect.left, tabRect.top, tabRect.Width(),
			tabRect.Height(), SWP_HIDEWINDOW);
	}

	m_nowTabIndex = 0;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CWorkSheetDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect   
	// ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
	m_ctrlTab.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	switch (m_nowTabIndex)//�ر���һ��ǩ�Ի���
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

	switch (m_nowTabIndex)//�򿪵�ǰѡ���ǩ
	{
		// �����ǩ�ؼ���ǰѡ���ǩΪ�Ի������ضԻ���   
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
