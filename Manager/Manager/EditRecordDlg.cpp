// EditRecordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "EditRecordDlg.h"
#include "afxdialogex.h"


// CEditRecordDlg �Ի���

IMPLEMENT_DYNAMIC(CEditRecordDlg, CDialogEx)

CEditRecordDlg::CEditRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditRecordDlg::IDD, pParent)
	, m_intStartDay(0)
	, m_strName(_T(""))
	, m_strYearMonth(_T(""))
	, m_strEndYM(_T(""))
	, m_intStartHour(0)
	, m_intStartMin(0)
	, m_intEndDay(0)
	, m_intEndHour(0)
	, m_intEndMin(0)
	, m_strWorkHour(_T(""))
	, m_intWeek(0)
	, m_strExtraInfor(_T(""))
{

}

CEditRecordDlg::~CEditRecordDlg()
{
}

void CEditRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT7, m_intStartDay);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT5, m_strYearMonth);
	DDX_Text(pDX, IDC_EDIT6, m_strEndYM);
	DDX_Text(pDX, IDC_EDIT8, m_intStartHour);
	DDX_Text(pDX, IDC_EDIT11, m_intStartMin);
	DDX_Text(pDX, IDC_EDIT9, m_intEndDay);
	DDX_Text(pDX, IDC_EDIT10, m_intEndHour);
	DDX_Text(pDX, IDC_EDIT13, m_intEndMin);
	DDX_Text(pDX, IDC_EDIT3, m_strWorkHour);
	DDX_Text(pDX, IDC_EDIT2, m_intWeek);
	DDX_Text(pDX, IDC_EDIT4, m_strExtraInfor);
}


BEGIN_MESSAGE_MAP(CEditRecordDlg, CDialogEx)
END_MESSAGE_MAP()


// CEditRecordDlg ��Ϣ�������


void CEditRecordDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	UpdateData(TRUE);
	if (m_intEndDay>31 || m_intEndDay<0 
		|| m_intEndHour<7 || m_intEndHour>22 || m_intEndMin<0 || m_intEndMin>59
		|| m_intStartHour<7 || m_intStartHour>22 || m_intStartMin<0 || m_intStartMin>59
		|| m_intEndHour<m_intStartHour || m_intEndHour - m_intStartHour > 4
		||m_intEndDay != m_intStartDay)
	{
		MessageBoxA("ʱ�����ݸ�ʽ��������������!", "����", MB_ICONQUESTION | MB_OK);
		return;

	}
	if (m_intWeek <0||m_intWeek>23)
	{
		MessageBoxA("���������Ӧ��0~23֮�䣡����������!", "����", MB_ICONQUESTION | MB_OK);
			return;
	}
	CDialogEx::OnOK();
}
