// EditSignDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "EditSignDlg.h"
#include "afxdialogex.h"


// CEditSignDlg �Ի���

IMPLEMENT_DYNAMIC(CEditSignDlg, CDialogEx)

CEditSignDlg::CEditSignDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditSignDlg::IDD, pParent)
	, m_strSigner(_T(""))
	, m_strLock(FALSE)
	, m_strYearMonth(_T(""))
	, m_strStartYM(_T(""))
	, m_intStartDay(0)
	, m_intStartHour(0)
	, m_intStartMin(0)
	, m_intEndDay(0)
	, m_intEndHour(0)
	, m_intEndMin(0)
{

}

CEditSignDlg::~CEditSignDlg()
{
}

void CEditSignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strSigner);
	//  DDX_Text(pDX, IDC_EDIT3, m_strEndTime);
	DDX_Text(pDX, IDC_EDIT5, m_strYearMonth);
	DDX_Text(pDX, IDC_EDIT6, m_strStartYM);
	DDX_Text(pDX, IDC_EDIT7, m_intStartDay);
	DDX_Text(pDX, IDC_EDIT8, m_intStartHour);
	DDX_Text(pDX, IDC_EDIT11, m_intStartMin);
	DDX_Text(pDX, IDC_EDIT9, m_intEndDay);
	DDX_Text(pDX, IDC_EDIT10, m_intEndHour);
	//  DDX_Control(pDX, IDC_EDIT13, m_intEndMin);
	DDX_Text(pDX, IDC_EDIT13, m_intEndMin);
}


BEGIN_MESSAGE_MAP(CEditSignDlg, CDialogEx)
END_MESSAGE_MAP()


// CEditSignDlg ��Ϣ�������


void CEditSignDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	UpdateData(TRUE);
	if (m_intEndDay > 31 || m_intEndDay<1 || m_intStartDay>31 || m_intStartDay < 1
		|| m_intEndHour<7 || m_intEndHour>22 || m_intEndMin<0 || m_intEndMin>59
		|| m_intStartHour<7 || m_intStartHour>22 || m_intStartMin<0 || m_intStartMin>59
		|| m_intEndHour<m_intStartHour || m_intEndHour - m_intStartHour > 4)
	{
		MessageBoxA("ʱ�����ݸ�ʽ��������������!", "����",
			MB_ICONQUESTION | MB_OK);
		return;
	}
	if (m_intEndDay != m_intStartDay)
	{
		MessageBoxA("���°��ǩ��ʱ�������ͬһ�죡����������!", "����",
			MB_ICONQUESTION | MB_OK);
		return;
	}

	if (MessageBoxA("��������°�ǩ��ʱ����Ч�����\"ȷ��\"��ť,����Ϣ����Ϊǩ����¼��", "��ȷ��",
		MB_ICONQUESTION | MB_YESNO) == IDNO) return;

	CDialogEx::OnOK();
}
