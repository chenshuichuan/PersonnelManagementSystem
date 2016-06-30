// EditSignDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "EditSignDlg.h"
#include "afxdialogex.h"


// CEditSignDlg 对话框

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


// CEditSignDlg 消息处理程序


void CEditSignDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	UpdateData(TRUE);
	if (m_intEndDay > 31 || m_intEndDay<1 || m_intStartDay>31 || m_intStartDay < 1
		|| m_intEndHour<7 || m_intEndHour>22 || m_intEndMin<0 || m_intEndMin>59
		|| m_intStartHour<7 || m_intStartHour>22 || m_intStartMin<0 || m_intStartMin>59
		|| m_intEndHour<m_intStartHour || m_intEndHour - m_intStartHour > 4)
	{
		MessageBoxA("时间数据格式错误！请重新输入!", "出错",
			MB_ICONQUESTION | MB_OK);
		return;
	}
	if (m_intEndDay != m_intStartDay)
	{
		MessageBoxA("上下班的签到时间必须在同一天！请重新输入!", "出错",
			MB_ICONQUESTION | MB_OK);
		return;
	}

	if (MessageBoxA("您输入的下班签到时间有效，点击\"确定\"按钮,该信息将成为签到记录？", "请确定",
		MB_ICONQUESTION | MB_YESNO) == IDNO) return;

	CDialogEx::OnOK();
}
