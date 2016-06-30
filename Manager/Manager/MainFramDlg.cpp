// MainFramDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "MainFramDlg.h"
#include "afxdialogex.h"
#include"start_work.h"
#include"person.h"
#include"ManagerDlg.h"
// CMainFramDlg �Ի���

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


// CMainFramDlg ��Ϣ�������

BOOL CMainFramDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ModifyStyleEx(0, WS_EX_APPWINDOW);//������ʾ��������

	CRect tabRect;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С   
	m_ctrlTab.InsertItem(0, _T("ǩ������"));   // �����һ����ǩ  
	m_ctrlTab.InsertItem(1, _T("ǩ����¼"));   // �����һ����ǩ  
	m_ctrlTab.InsertItem(2, _T("�ռ���"));  // ����ڶ�����ǩ   
	m_ctrlTab.InsertItem(3, _T("������"));
	m_ctrlTab.InsertItem(4, _T("���˿α�"));
	m_ctrlTab.InsertItem(5, _T("��������"));
	m_ctrlTab.InsertItem(6, _T("ͨѶ¼"));

	//���˵������Щ�ֶԻ���ĸ�������tab �ؼ���������mainfram ���ڣ�����������

	m_signDlg.Create(IDD_DIALOG_SIGN, &m_ctrlTab);
    m_recordDlg.Create(IDD_DIALOG_RECORD, &m_ctrlTab);    // ������һ����ǩҳ   
	m_receiveDlg.Create(IDD_DIALOG_RECEIVEBOX, &m_ctrlTab); // �����ڶ�����ǩҳ 
	m_sendDlg.Create(IDD_DIALOG_SENDBOX, &m_ctrlTab);
	m_courseDlg.Create(IDD_DIALOG_COURSE, &m_ctrlTab);
	m_userDlg.Create(IDD_DIALOG_USERCENTRE, &m_ctrlTab);
	m_adminDlg.Create(IDD_DIALOG_ADMIN, &m_ctrlTab);
	
	
	

	m_ctrlTab.GetClientRect(&tabRect);    // ��ȡ��ǩ�ؼ��ͻ���Rect   
	// ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ   
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	// ���ݵ����õ�tabRect�����ӶԻ��򣬲�����Ϊ��ʾ 
	m_signDlg.SetWindowPos(NULL,
		tabRect.left, tabRect.top, tabRect.Width(),
		tabRect.Height(), SWP_SHOWWINDOW);
	m_recordDlg.SetWindowPos(NULL,
		tabRect.left, tabRect.top, tabRect.Width(),
		tabRect.Height(), SWP_HIDEWINDOW);
	// ���ݵ����õ�tabRect�����ӶԻ��򣬲�����Ϊ����   
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
	ShowWelcome();//��ʾ��ӭ��Ϣ
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CMainFramDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
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
	switch (m_nowIndex)//�ر���һ��ǩ�Ի���
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

	switch (m_nowIndex)//�򿪵�ǰѡ���ǩ
	{
		// �����ǩ�ؼ���ǰѡ���ǩΪ�Ի������ضԻ���   
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
	CString str, week, ti; //��ȡϵͳʱ��
	CTime tm;
	tm = CTime::GetCurrentTime();
	switch (tm.GetDayOfWeek())
	{
	case 1:week = "������"; break;
	case 2:week = "����һ"; break;
	case 3:week = "���ڶ�"; break;
	case 4:week = "������"; break;
	case 5:week = "������"; break;
	case 6:week = "������"; break;
	default:week = "������"; break;
	}
	ti = tm.Format("������%Y��%m��%d��");
	CString welcome;
	int hour = tm.GetHour();
	if (hour < 12)welcome = "���Ϻ�ѽ~~~";
	else if (hour>=14 && hour < 18)welcome = "�����ѽ~~~";
	else if(hour>=12&&hour<14)welcome = "�����ѽ~~~";
	else welcome = "���Ϻ�ѽ~~~";

	srand((unsigned)time(NULL));
	int i=rand() % 10;
	if (i % 2 == 0)welcome = "��ӭ��";

	str.Format("%s,%s ! %s  ��%d��%s", 
		welcome, theApp.m_strUserName, ti,theApp.m_nowWeek,week);
	m_strLoginInfo = str;
}


void CMainFramDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTime tm;
	tm = CTime::GetCurrentTime();
	bool sys = false;
	//�˴�����û�п����ļ�ʱ�Ͷ���ʱ������
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
				MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
				return;
			}
			if (!ss.IsEOF())//�ҵ��ϰ�ǩ����Ϣ��
			{
				Cperson rs(&theApp.m_DB);
				strSQL.Format("select * from person where pname='%s'",ss.m_signer);
				if (!rs.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
				{
					MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
					return;
				}
				CString sex;
				if (!rs.IsEOF())
				{
					if (rs.m_sex)sex = "��";
					else sex = "��";
				}
				CString str;
				str.Format("%s ��û��ǩ�°࣬�ǵ�����%sӴ~~~", ss.m_signer, sex);
				MessageBox(str, "���ݿ����", MB_OK);
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



// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMainFramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}