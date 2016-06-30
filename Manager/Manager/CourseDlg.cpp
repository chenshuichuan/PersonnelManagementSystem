// CourseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "CourseDlg.h"
#include "afxdialogex.h"
#include"person.h"
#include"course_table.h"
#include"WorkSheetDlg.h"
// CCourseDlg 对话框

IMPLEMENT_DYNAMIC(CCourseDlg, CDialogEx)

CCourseDlg::CCourseDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CCourseDlg::IDD, pParent)
, m_strPerson(_T(""))
, m_strWeek(_T(""))
, m_intWeek(0)
, m_Monday12(FALSE)
, m_Monday34(FALSE)
, m_Monday56(FALSE)
, m_Monday78(FALSE)
, m_Tuesday12(FALSE)
, m_Tuesday34(FALSE)
, m_Tuesday56(FALSE)
, m_Tuesday78(FALSE)
, m_Wednesday12(FALSE)
, m_Wednesday34(FALSE)
, m_Wednesday56(FALSE)
, m_Wednesday78(FALSE)
, m_Thursday12(FALSE)
, m_Thursday34(FALSE)
, m_Thursday56(FALSE)
, m_Thursday78(FALSE)
, m_Friday12(FALSE)
, m_Friday34(FALSE)
, m_Friday56(FALSE)
, m_Friday78(FALSE)
, m_Saturday12(FALSE)
, m_Saturday34(FALSE)
, m_Saturday56(FALSE)
, m_Saturday78(FALSE)
, m_Sunday12(FALSE)
, m_Sunday34(FALSE)
, m_Sunday56(FALSE)
, m_Sunday78(FALSE)
, m_strState(_T(""))
, m_strExtra(_T(""))
{

}

CCourseDlg::~CCourseDlg()
{
}

void CCourseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_ctrlPerson);
	DDX_CBString(pDX, IDC_COMBO2, m_strPerson);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlWeek);
	DDX_CBString(pDX, IDC_COMBO1, m_strWeek);
	DDX_Check(pDX, IDC_CHECK1, m_Monday12);
	DDX_Check(pDX, IDC_CHECK8, m_Monday34);
	DDX_Check(pDX, IDC_CHECK15, m_Monday56);
	DDX_Check(pDX, IDC_CHECK22, m_Monday78);
	DDX_Check(pDX, IDC_CHECK2, m_Tuesday12);
	DDX_Check(pDX, IDC_CHECK9, m_Tuesday34);
	DDX_Check(pDX, IDC_CHECK16, m_Tuesday56);
	DDX_Check(pDX, IDC_CHECK23, m_Tuesday78);
	DDX_Check(pDX, IDC_CHECK3, m_Wednesday12);
	DDX_Check(pDX, IDC_CHECK10, m_Wednesday34);
	DDX_Check(pDX, IDC_CHECK17, m_Wednesday56);
	DDX_Check(pDX, IDC_CHECK24, m_Wednesday78);
	DDX_Check(pDX, IDC_CHECK4, m_Thursday12);
	DDX_Check(pDX, IDC_CHECK11, m_Thursday34);
	DDX_Check(pDX, IDC_CHECK18, m_Thursday56);
	DDX_Check(pDX, IDC_CHECK25, m_Thursday78);
	DDX_Check(pDX, IDC_CHECK5, m_Friday12);
	DDX_Check(pDX, IDC_CHECK12, m_Friday34);
	DDX_Check(pDX, IDC_CHECK19, m_Friday56);
	DDX_Check(pDX, IDC_CHECK26, m_Friday78);
	DDX_Check(pDX, IDC_CHECK6, m_Saturday12);
	DDX_Check(pDX, IDC_CHECK13, m_Saturday34);
	DDX_Check(pDX, IDC_CHECK20, m_Saturday56);
	DDX_Check(pDX, IDC_CHECK27, m_Saturday78);
	DDX_Check(pDX, IDC_CHECK7, m_Sunday12);
	DDX_Check(pDX, IDC_CHECK14, m_Sunday34);
	DDX_Check(pDX, IDC_CHECK21, m_Sunday56);
	DDX_Check(pDX, IDC_CHECK28, m_Sunday78);
	DDX_Text(pDX, IDC_EDIT1, m_strState);
	DDX_Control(pDX, IDC_EDIT2, m_ctrlExtra);
	DDX_Text(pDX, IDC_EDIT2, m_strExtra);
}


BEGIN_MESSAGE_MAP(CCourseDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CCourseDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCourseDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BTC_SAVE, &CCourseDlg::OnBnClickedBtcSave)
	ON_BN_CLICKED(IDC_BTC_EXPORT, &CCourseDlg::OnBnClickedBtcExport)
END_MESSAGE_MAP()


// CCourseDlg 消息处理程序


void CCourseDlg::OnCbnSelchangeCombo2()//person
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlPerson.GetCurSel();//当前选中的行。
	m_ctrlPerson.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlPerson.GetLBText(iPos, m_strPerson);
	ShowCourse();
	UpdateData(FALSE);
}

void CCourseDlg::ShowCourse()//根据当前状态显示空余时间表
{
	UpdateData(TRUE);
	try
	{
		//Connect to the database
		CCourseSet recordset(&theApp.m_DB);
		CString strSQL;

		strSQL.Format("select * from course_table where pname='%s' AND week_number=%d"
			,m_strPerson,m_intWeek);
		m_strState.Format("%s的第%d周空余时间表", m_strPerson, m_intWeek);
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBoxA("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		if(!recordset.IsEOF())
		{
			m_Monday12=recordset.m_Monday12;
			m_Monday34 = recordset.m_Monday34;
			m_Monday56 = recordset.m_Monday56;
			m_Monday78 = recordset.m_Monday78;
			m_Tuesday12 = recordset.m_Tuesday12;
			m_Tuesday34 = recordset.m_Tuesday34;
			m_Tuesday56 = recordset.m_Tuesday56;
			m_Tuesday78 = recordset.m_Tuesday78;
			m_Wednesday12 = recordset.m_Wednesday12;
			m_Wednesday34 = recordset.m_Wednesday34;
			m_Wednesday56 = recordset.m_Wednesday56;
			m_Wednesday78 = recordset.m_Wednesday78;
			m_Thursday12 = recordset.m_Thursday12;
			m_Thursday34 = recordset.m_Thursday34;
			m_Thursday56 = recordset.m_Thursday56;
			m_Thursday78 = recordset.m_Thursday78;
			m_Friday12 = recordset.m_Friday12;
			m_Friday34 = recordset.m_Friday34;
			m_Friday56 = recordset.m_Friday56;
			m_Friday78 = recordset.m_Friday78;
			m_Saturday12 = recordset.m_Saturday12;
			m_Saturday34 = recordset.m_Saturday34;
			m_Saturday56 = recordset.m_Saturday56;
			m_Saturday78 = recordset.m_Saturday78;
			m_Sunday12 = recordset.m_Sunday12;
			m_Sunday34 = recordset.m_Sunday34;
			m_Sunday56 = recordset.m_Sunday56;
			m_Sunday78 = recordset.m_Sunday78;

			m_strExtra = recordset.m_extra_infor;

			if (recordset.m_is_lock)
			{
				m_strState += ",已经锁定";
				GetDlgItem(IDC_BTC_SAVE)->EnableWindow(FALSE);
				m_ctrlExtra.SetReadOnly(1);
			}
			else
			{
				m_strState += ",未锁定";
				//仅可以添加或修改自己的未来周数课程空余时间
				if (recordset.m_pname == theApp.m_strUserName
					&& recordset.m_week_number>theApp.m_nowWeek)
				{
					m_ctrlExtra.SetReadOnly(0);
					GetDlgItem(IDC_BTC_SAVE)->EnableWindow(TRUE);
				}
				else
				{
					m_ctrlExtra.SetReadOnly(1);
					GetDlgItem(IDC_BTC_SAVE)->EnableWindow(FALSE);
				}
			}
		}
		else
		{
			m_Monday12 =0;
			m_Monday34 = 0;
			m_Monday56 = 0;
			m_Monday78 = 0;
			m_Tuesday12 =0;
			m_Tuesday34 = 0;
			m_Tuesday56 = 0;
			m_Tuesday78 = 0;
			m_Wednesday12 =0;
			m_Wednesday34 = 0;
			m_Wednesday56 = 0;
			m_Wednesday78 = 0;
			m_Thursday12 = 0;
			m_Thursday34 = 0;
			m_Thursday56 = 0;
			m_Thursday78 = 0;
			m_Friday12 = 0;
			m_Friday34 =0;
			m_Friday56 = 0;
			m_Friday78 = 0;
			m_Saturday12 = 0;
			m_Saturday34 =0;
			m_Saturday56 = 0;
			m_Saturday78 = 0;
			m_Sunday12 = 0;
			m_Sunday34 =0;
			m_Sunday56 = 0;
			m_Sunday78 = 0;

			m_strExtra ="";
			m_strState += ",未设置";
			//仅可以添加或修改自己的课程空余时间
			if (m_strPerson == theApp.m_strUserName
				&&m_intWeek>theApp.m_nowWeek)
			{
				m_ctrlExtra.SetReadOnly(0);
				GetDlgItem(IDC_BTC_SAVE)->EnableWindow(TRUE);
			}
				
			else
			{
				m_ctrlExtra.SetReadOnly(1);
				GetDlgItem(IDC_BTC_SAVE)->EnableWindow(FALSE);
			}
		}
		recordset.Close();
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
	UpdateData(FALSE);
}

void CCourseDlg::OnCbnSelchangeCombo1()//week
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlWeek.GetCurSel();//当前选中的行。
	m_ctrlWeek.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlWeek.GetLBText(iPos, m_strWeek);
	m_intWeek = iPos;//box从0开始，周数也是从0开始
	ShowCourse();
	UpdateData(FALSE);
}


void CCourseDlg::OnBnClickedBtcSave()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	try
	{
		//Connect to the database
		CCourseSet recordset(&theApp.m_DB);
		CString strSQL;

		strSQL.Format("select * from course_table where pname='%s' AND week_number=%d"
			, m_strPerson, m_intWeek);
		
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBoxA("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		if (!recordset.IsEOF())//存在且未锁定，则更新
		{
			CString update;
			update.Format("update course_table set "
				"Monday12=%d,Monday34=%d,Monday56=%d,Monday78=%d,"
				"Tuesday12=%d,Tuesday34=%d,Tuesday56=%d,Tuesday78=%d,"
				"Wednesday12=%d,Wednesday34=%d,Wednesday56=%d,Wednesday78=%d,"
				"Thursday12=%d,Thursday34=%d,Thursday56=%d,Thursday78=%d,"
				"Friday12=%d,Friday34=%d,Friday56=%d,Friday78=%d,"
				"Saturday12=%d,Saturday34=%d,Saturday56=%d,Saturday78=%d,"
				"Sunday12=%d,Sunday34=%d,Sunday56=%d,Sunday78=%d,"
				"extra_infor='%s' where pname='%s' AND week_number=%d"
				, m_Monday12,m_Monday34,m_Monday56,m_Monday78,
				m_Tuesday12,m_Tuesday34,m_Tuesday56,m_Tuesday78,
				m_Wednesday12,m_Wednesday34,m_Wednesday56,m_Wednesday78,
				m_Thursday12,m_Thursday34,m_Thursday56,m_Thursday78,
				m_Friday12,m_Friday34,m_Friday56,m_Friday78,
				m_Saturday12,m_Saturday34,m_Saturday56,m_Saturday78,
				m_Sunday12,m_Sunday34,m_Sunday56,m_Sunday78, 
				m_strExtra, m_strPerson, m_intWeek);

			theApp.m_DB.ExecuteSQL(update);
			CString str;
			str.Format("成功更新第%d周的时间空余表！", m_intWeek);
			MessageBoxA(str, "更新成功", MB_OK);

		}
		else//不存在则添加
		{
			CString insert;
			insert.Format("insert into course_table("
				"Monday12,Monday34,Monday56,Monday78,"
				"Tuesday12,Tuesday34,Tuesday56,Tuesday78,"
				"Wednesday12,Wednesday34,Wednesday56,Wednesday78,"
				"Thursday12,Thursday34,Thursday56,Thursday78,"
				"Friday12,Friday34,Friday56,Friday78,"
				"Saturday12,Saturday34,Saturday56,Saturday78,"
				"Sunday12,Sunday34,Sunday56,Sunday78,"
				"extra_infor,pname,week_number) values("
				"%d,%d,%d,%d,"
				"%d,%d,%d,%d,"
				"%d,%d,%d,%d,"
				"%d,%d,%d,%d,"
				"%d,%d,%d,%d,"
				"%d,%d,%d,%d,"
				"%d,%d,%d,%d,"
				"'%s','%s',%d)"
				, m_Monday12, m_Monday34, m_Monday56, m_Monday78,
				m_Tuesday12, m_Tuesday34, m_Tuesday56, m_Tuesday78,
				m_Wednesday12, m_Wednesday34, m_Wednesday56, m_Wednesday78,
				m_Thursday12, m_Thursday34, m_Thursday56, m_Thursday78,
				m_Friday12, m_Friday34, m_Friday56, m_Friday78,
				m_Saturday12, m_Saturday34, m_Saturday56, m_Saturday78,
				m_Sunday12, m_Sunday34, m_Sunday56, m_Sunday78,
				m_strExtra, m_strPerson, m_intWeek);

			theApp.m_DB.ExecuteSQL(insert);
			CString str;
			str.Format("成功添加第%d周的时间空余表！", m_intWeek);
			MessageBoxA(str, "添加成功", MB_OK);
		}
		m_strState.Format("%s的第%d周空余时间表,未锁定", m_strPerson, m_intWeek);
		recordset.Close();

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
	UpdateData(FALSE);

}


BOOL CCourseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (int i = 0; i < 24; i++)
	{
		CString str;
		str.Format("第%d周", i);
		m_ctrlWeek.AddString(str);
	}
	m_intWeek = theApp.m_nowWeek;
	m_strWeek.Format("第%d周", m_intWeek);
	m_strPerson = theApp.m_strUserName;
	UpdateData(FALSE);

	m_ctrlExtra.SetReadOnly(1);
	ShowCourse();

	try
	{
		//Connect to the database
		Cperson recordset(&theApp.m_DB);
		CString strSQL;

		strSQL = "select * from person";
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return 0;
		}

		while (!recordset.IsEOF())
		{
			//if (recordset.m_post != "老师"&&recordset.m_post != "主席")
				m_ctrlPerson.AddString(recordset.m_pname);
			recordset.MoveNext();
		}
		recordset.Close();
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
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

/*
long	m_course_id;	//周课表编号
CString	m_pname;	//该表是属于谁的
CString	m_extra_infor;	//这周课程特别之处的备注信息
BOOL	m_is_lock;	//课表已经被锁定，则不可以修改
long	m_week_number;	//该周课程信息属于的周数
BOOL	m_Monday12;
BOOL	m_Monday34;
BOOL	m_Monday56;
BOOL	m_Monday78;
BOOL	m_Tuesday12;
BOOL	m_Tuesday34;
BOOL	m_Tuesday56;
BOOL	m_Tuesday78;
BOOL	m_Wednesday12;
BOOL	m_Wednesday34;
BOOL	m_Wednesday56;
BOOL	m_Wednesday78;
BOOL	m_Thursday12;
BOOL	m_Thursday34;
BOOL	m_Thursday56;
BOOL	m_Thursday78;
BOOL	m_Friday12;
BOOL	m_Friday34;
BOOL	m_Friday56;
BOOL	m_Friday78;
BOOL	m_Saturday12;
BOOL	m_Saturday34;
BOOL	m_Saturday56;
BOOL	m_Saturday78;
BOOL	m_Sunday12;
BOOL	m_Sunday34;
BOOL	m_Sunday56;
BOOL	m_Sunday78;
*/

void CCourseDlg::OnBnClickedBtcExport()
{
	// TODO:  在此添加控件通知处理程序代码
	CWorkSheetDlg dlg;
	dlg.DoModal();


}
