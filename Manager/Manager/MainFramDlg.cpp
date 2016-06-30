// MainFramDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "MainFramDlg.h"
#include "afxdialogex.h"
#include"start_work.h"
#include"person.h"
#include"ManagerDlg.h"
// CMainFramDlg 对话框

IMPLEMENT_DYNAMIC(CMainFramDlg, CDialogEx)

CMainFramDlg::CMainFramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainFramDlg::IDD, pParent)
	, m_strLoginInfo(_T(""))
{

}

CMainFramDlg::~CMainFramDlg()
{
}

void CMainFramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_ctrlTab);
	DDX_Text(pDX, IDC_EDIT1, m_strLoginInfo);
}


BEGIN_MESSAGE_MAP(CMainFramDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMainFramDlg::OnTcnSelchangeTab1)
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMainFramDlg 消息处理程序

BOOL CMainFramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO:  在此添加额外的初始化
	ModifyStyleEx(0, WS_EX_APPWINDOW);//窗口显示到任务栏

	CRect tabRect;   // 标签控件客户区的位置和大小   
	m_ctrlTab.InsertItem(0, _T("签到窗口"));   // 插入第一个标签  
	m_ctrlTab.InsertItem(1, _T("签到记录"));   // 插入第一个标签  
	m_ctrlTab.InsertItem(2, _T("收件箱"));  // 插入第二个标签   
	m_ctrlTab.InsertItem(3, _T("发件箱"));
	m_ctrlTab.InsertItem(4, _T("个人课表"));
	m_ctrlTab.InsertItem(5, _T("个人中心"));
	m_ctrlTab.InsertItem(6, _T("通讯录"));

	//如此说来，这些字对话框的父窗口是tab 控件，而不是mainfram 窗口！！！？？？

	m_signDlg.Create(IDD_DIALOG_SIGN, &m_ctrlTab);
    m_recordDlg.Create(IDD_DIALOG_RECORD, &m_ctrlTab);    // 创建第一个标签页   
	m_receiveDlg.Create(IDD_DIALOG_RECEIVEBOX, &m_ctrlTab); // 创建第二个标签页 
	m_sendDlg.Create(IDD_DIALOG_SENDBOX, &m_ctrlTab);
	m_courseDlg.Create(IDD_DIALOG_COURSE, &m_ctrlTab);
	m_userDlg.Create(IDD_DIALOG_USERCENTRE, &m_ctrlTab);
	m_adminDlg.Create(IDD_DIALOG_ADMIN, &m_ctrlTab);
	
	
	

	m_ctrlTab.GetClientRect(&tabRect);    // 获取标签控件客户区Rect   
	// 调整tabRect，使其覆盖范围适合放置标签页   
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	// 根据调整好的tabRect放置子对话框，并设置为显示 
	m_signDlg.SetWindowPos(NULL,
		tabRect.left, tabRect.top, tabRect.Width(),
		tabRect.Height(), SWP_SHOWWINDOW);
	m_recordDlg.SetWindowPos(NULL,
		tabRect.left, tabRect.top, tabRect.Width(),
		tabRect.Height(), SWP_HIDEWINDOW);
	// 根据调整好的tabRect放置子对话框，并设置为隐藏   
	m_receiveDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
		tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_sendDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
		tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_courseDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
		tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_userDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
		tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	m_adminDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
		tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);

	m_nowIndex = 0;
	ShowWelcome();//显示欢迎信息
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CMainFramDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
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
	switch (m_nowIndex)//关闭上一标签对话框
	{
	case 0:
		m_signDlg.SetWindowPos(NULL, tabRect.left,
			tabRect.top, tabRect.Width(),
			tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 1:
		m_recordDlg.SetWindowPos(NULL, tabRect.left,
			tabRect.top, tabRect.Width(),
			tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 2:
		m_receiveDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 3:
		m_sendDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 4:
		m_courseDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 5:
		m_userDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 6:
		m_adminDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	default:
		break;
	}

	m_nowIndex = m_ctrlTab.GetCurSel();

	switch (m_nowIndex)//打开当前选择标签
	{
		// 如果标签控件当前选择标签为对话框，隐藏对话框   
	case 0:
		m_signDlg.SetWindowPos(NULL, tabRect.left,
			tabRect.top, tabRect.Width(),
			tabRect.Height(), SWP_SHOWWINDOW);
		break;
	case 1:
		m_recordDlg.SetWindowPos(NULL, tabRect.left,
			tabRect.top, tabRect.Width(),
			tabRect.Height(), SWP_SHOWWINDOW);
		break;
	case 2:
		m_receiveDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	case 3:
		m_sendDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	case 4:
		m_courseDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	case 5:
		m_userDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	case 6:
		m_adminDlg.SetWindowPos(NULL, tabRect.left, tabRect.top,
			tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	default:
		break;
	}
}

void CMainFramDlg::ShowWelcome()
{
	CString str, week, ti; //获取系统时间
	CTime tm;
	tm = CTime::GetCurrentTime();
	switch (tm.GetDayOfWeek())
	{
	case 1:week = "星期日"; break;
	case 2:week = "星期一"; break;
	case 3:week = "星期二"; break;
	case 4:week = "星期三"; break;
	case 5:week = "星期四"; break;
	case 6:week = "星期五"; break;
	default:week = "星期六"; break;
	}
	ti = tm.Format("现在是%Y年%m月%d日");
	CString welcome;
	int hour = tm.GetHour();
	if (hour < 12)welcome = "早上好呀~~~";
	else if (hour>=14 && hour < 18)welcome = "下午好呀~~~";
	else if(hour>=12&&hour<14)welcome = "中午好呀~~~";
	else welcome = "晚上好呀~~~";

	srand((unsigned)time(NULL));
	int i=rand() % 10;
	if (i % 2 == 0)welcome = "欢迎您";

	str.Format("%s,%s ! %s  第%d周%s", 
		welcome, theApp.m_strUserName, ti,theApp.m_nowWeek,week);
	m_strLoginInfo = str;
}


void CMainFramDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CTime tm;
	tm = CTime::GetCurrentTime();
	bool sys = false;
	//此处代码没有考虑夏季时和冬季时的区别
	if ((tm.GetHour() == 11 || tm.GetHour() == 17) && tm.GetMinute() > 50)
		sys = true;
	if (tm.GetHour() == 12 || tm.GetHour() == 18)
		sys = true;
	if (tm.GetHour() == 13 || tm.GetHour() >19)
		sys = true;
	if (sys)
	{
		try
		{
			//Connect to the database
			CString strSQL;

			CSignSet ss(&theApp.m_DB);
			strSQL.Format("select * from start_work where is_lock=0");
			if (!ss.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			{
				MessageBox("打开数据库失败!", "数据库错误", MB_OK);
				return;
			}
			if (!ss.IsEOF())//找到上班签到信息，
			{
				Cperson rs(&theApp.m_DB);
				strSQL.Format("select * from person where pname='%s'",ss.m_signer);
				if (!rs.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
				{
					MessageBox("打开数据库失败!", "数据库错误", MB_OK);
					return;
				}
				CString sex;
				if (!rs.IsEOF())
				{
					if (rs.m_sex)sex = "他";
					else sex = "她";
				}
				CString str;
				str.Format("%s 还没有签下班，记得提醒%s哟~~~", ss.m_signer, sex);
				MessageBox(str, "数据库错误", MB_OK);
			}
			ss.Close();
			UpdateData(FALSE);
		}
		catch (CDBException ex)
		{
			AfxMessageBox(ex.m_strError);
			AfxMessageBox(ex.m_strStateNativeOrigin);
		}
		catch (CMemoryException mEx)
		{
			mEx.ReportError();
			AfxMessageBox("memory exception! ");
		}
		catch (CException *cEx){
			TCHAR szError[100];
			cEx->GetErrorMessage(szError, 100);
			AfxMessageBox(szError);

		}
	}
	
	CDialogEx::OnClose();
}



// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMainFramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}