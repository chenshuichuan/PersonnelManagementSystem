// AtWorkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "AtWorkDlg.h"
#include "afxdialogex.h"
//#include"course_table.h"
#include"attend_table.h"
// CAtWorkDlg 对话框

IMPLEMENT_DYNAMIC(CAtWorkDlg, CDialogEx)

CAtWorkDlg::CAtWorkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAtWorkDlg::IDD, pParent)
	, m_strWeek(_T(""))
	, m_strExtra(_T(""))
	, m_Monday12(_T(""))
	, m_Monday34(_T(""))
	, m_Monday56(_T(""))
	, m_Monday78(_T(""))
	, m_Tuesday12(_T(""))
	, m_Tuesday34(_T(""))
	, m_Tuesday56(_T(""))
	, m_Tuesday78(_T(""))
	, m_Wednesday12(_T(""))
	, m_Wednesday34(_T(""))
	, m_Wednesday56(_T(""))
	, m_Wednesday78(_T(""))
	, m_Thursday12(_T(""))
	, m_Thursday34(_T(""))
	, m_Thursday56(_T(""))
	, m_Thursday78(_T(""))
	, m_Friday12(_T(""))
	, m_Friday34(_T(""))
	, m_Friday56(_T(""))
	, m_Friday78(_T(""))
	, m_Saturday12(_T(""))
	, m_Saturday34(_T(""))
	, m_Saturday56(_T(""))
	, m_Saturday78(_T(""))
	, m_Sunday12(_T(""))
	, m_Sunday34(_T(""))
	, m_Sunday56(_T(""))
	, m_Sunday78(_T(""))
{

}

CAtWorkDlg::~CAtWorkDlg()
{
}

void CAtWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlWeek);
	DDX_CBString(pDX, IDC_COMBO1, m_strWeek);
	DDX_Text(pDX, IDC_EDIT1, m_strExtra);

	DDX_Text(pDX, IDC_EDIT_A112, m_Monday12);
	DDX_Text(pDX, IDC_EDIT_A134, m_Monday34);
	DDX_Text(pDX, IDC_EDIT_A156, m_Monday56);
	DDX_Text(pDX, IDC_EDIT_A178, m_Monday78);
	DDX_Text(pDX, IDC_EDIT_A212, m_Tuesday12);
	DDX_Text(pDX, IDC_EDIT_A234, m_Tuesday34);
	DDX_Text(pDX, IDC_EDIT_A256, m_Tuesday56);
	DDX_Text(pDX, IDC_EDIT_A278, m_Tuesday78);
	DDX_Text(pDX, IDC_EDIT_A312, m_Wednesday12);
	DDX_Text(pDX, IDC_EDIT_A334, m_Wednesday34);
	DDX_Text(pDX, IDC_EDIT_A356, m_Wednesday56);
	DDX_Text(pDX, IDC_EDIT_A378, m_Wednesday78);
	DDX_Text(pDX, IDC_EDIT_A412, m_Thursday12);
	//  DDX_Text(pDX, IDC_EDIT_434, m_Thursday56);
	DDX_Text(pDX, IDC_EDIT_A434, m_Thursday34);
	DDX_Text(pDX, IDC_EDIT_A456, m_Thursday56);
	DDX_Text(pDX, IDC_EDIT_A478, m_Thursday78);
	//  DDX_Control(pDX, IDC_EDIT_512, m_Sunday12);
	DDX_Text(pDX, IDC_EDIT_A512, m_Friday12);
	DDX_Text(pDX, IDC_EDIT_A534, m_Friday34);
	DDX_Text(pDX, IDC_EDIT_A556, m_Friday56);
	DDX_Text(pDX, IDC_EDIT_A578, m_Friday78);
	DDX_Text(pDX, IDC_EDIT_A612, m_Saturday12);
	DDX_Text(pDX, IDC_EDIT_A634, m_Saturday34);
	DDX_Text(pDX, IDC_EDIT_A656, m_Saturday56);
	DDX_Text(pDX, IDC_EDIT_A678, m_Saturday78);
	DDX_Text(pDX, IDC_EDIT_A712, m_Sunday12);
	DDX_Text(pDX, IDC_EDIT_A734, m_Sunday34);
	DDX_Text(pDX, IDC_EDIT_A756, m_Sunday56);
	DDX_Text(pDX, IDC_EDIT_A778, m_Sunday78);
}


BEGIN_MESSAGE_MAP(CAtWorkDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAtWorkDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CAtWorkDlg 消息处理程序


BOOL CAtWorkDlg::OnInitDialog()
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
	ShowSheet();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CAtWorkDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlWeek.GetCurSel();//当前选中的行。
	m_ctrlWeek.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlWeek.GetLBText(iPos, m_strWeek);
	m_intWeek = iPos;//box从0开始，周数也是从0开始
	ShowSheet();
	UpdateData(FALSE);
}
void CAtWorkDlg::ShowSheet()//显示空余时间表
{
	m_Monday12 = "";
	m_Monday34 = "";
	m_Monday56 = "";
	m_Monday78 = "";
	m_Tuesday12 = "";
	m_Tuesday34 = "";
	m_Tuesday56 = "";
	m_Tuesday78 = "";
	m_Wednesday12 = "";
	m_Wednesday34 = "";
	m_Wednesday56 = "";
	m_Wednesday78 = "";
	m_Thursday12 = "";
	m_Thursday34 = "";
	m_Thursday56 = "";
	m_Thursday78 = "";
	m_Friday12 = "";
	m_Friday34 = "";
	m_Friday56 = "";
	m_Friday78 = "";
	m_Saturday12 = "";
	m_Saturday34 = "";
	m_Saturday56 = "";
	m_Saturday78 = "";
	m_Sunday12 = "";
	m_Sunday34 = "";
	m_Sunday56 = "";
	m_Sunday78 = "";

	m_strExtra = "";

	try
	{
		//Connect to the database
		CAttend_tableSet recordset(&theApp.m_DB);
		CString strSQL;

		strSQL.Format("select * from attend_table where week_number=%d", m_intWeek);
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		if (!recordset.IsEOF())
		{
			//如果该时间有空，则加入到空余时间表
			m_Monday12 = recordset.m_Monday12;
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
			recordset.MoveNext();
		}
		else
		{
			m_strExtra.Format("第%d周的值班表未设置！",m_intWeek);
		}
		recordset.Close();

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
	UpdateData(FALSE);
}

