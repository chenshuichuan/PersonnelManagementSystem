// SendInforDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "SendInforDlg.h"
#include "afxdialogex.h"
#include"person.h"

// CSendInforDlg 对话框

IMPLEMENT_DYNAMIC(CSendInforDlg, CDialogEx)

CSendInforDlg::CSendInforDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSendInforDlg::IDD, pParent)
	, m_strSender(_T(""))
	, m_strSendTime(_T(""))
	, m_strLevel(_T(""))
	, m_strDepart(_T(""))
	, m_strPerson(_T(""))
	, m_strInfor(_T(""))
{

}

CSendInforDlg::~CSendInforDlg()
{
}

void CSendInforDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strSender);
	DDX_Text(pDX, IDC_EDIT2, m_strSendTime);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlLevel);
	DDX_CBString(pDX, IDC_COMBO1, m_strLevel);
	DDX_Control(pDX, IDC_COMBO2, m_ctrlDepart);
	DDX_CBString(pDX, IDC_COMBO2, m_strDepart);
	DDX_Control(pDX, IDC_COMBO3, m_ctrlPerson);
	DDX_CBString(pDX, IDC_COMBO3, m_strPerson);
	DDX_Text(pDX, IDC_EDIT3, m_strInfor);
}


BEGIN_MESSAGE_MAP(CSendInforDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSendInforDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CSendInforDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CSendInforDlg::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// CSendInforDlg 消息处理程序


void CSendInforDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlLevel.GetCurSel();//当前选中的行。
	m_ctrlLevel.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlLevel.GetLBText(iPos, m_strLevel);

	if (m_strLevel == "全体")
	{
		m_strDepart = "";
		m_strPerson = "";
		m_ctrlDepart.EnableWindow(FALSE);
		m_ctrlPerson.EnableWindow(FALSE);
	}
	else if (m_strLevel == "部门")
	{
		m_ctrlDepart.EnableWindow(TRUE);
		m_strPerson = "";
		m_ctrlPerson.EnableWindow(FALSE);
	}
	else if (m_strLevel == "个人")
	{
		m_strDepart = "";
		m_ctrlDepart.EnableWindow(FALSE);
		m_ctrlPerson.EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}


void CSendInforDlg::OnCbnSelchangeCombo2()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlDepart.GetCurSel();//当前选中的行。
	m_ctrlDepart.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlDepart.GetLBText(iPos, m_strDepart);
}


void CSendInforDlg::OnCbnSelchangeCombo3()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlPerson.GetCurSel();//当前选中的行。
	m_ctrlPerson.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlPerson.GetLBText(iPos, m_strPerson);
}


void CSendInforDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	UpdateData(TRUE);
	CString str;
	if (m_strLevel == "全体")
	{
		str = "全体人员发送消息";
	}
	else if (m_strLevel == "部门")
	{
		if (m_strDepart.GetLength()==0)
		{
			MessageBoxA("要给部门发送消息请选择部门！", "请选择部门",
				MB_ICONINFORMATION | MB_OK);
			return;
		}
		str = m_strDepart+"的人员发送消息";
	}
	else if (m_strLevel == "个人")
	{
		if (m_strPerson.GetLength() == 0)
		{
			MessageBoxA("要给个人发送消息请选择个人！", "请选择个人",
				MB_ICONINFORMATION | MB_OK);
			return;
		}
		str = m_strPerson + "发送消息";
	}
	else
	{
		MessageBoxA("请选择消息级别！", "请选择",
			MB_ICONINFORMATION | MB_OK);
		return;
	}
	if (m_strInfor.GetLength() == 0)
	{
		MessageBoxA("请填写消息内容！", "请填写内容",
			MB_ICONINFORMATION | MB_OK);
		return;
	}
	if(MessageBoxA("你将要给"+str+"\n点击‘确定’按钮后将无法撤回！", "请确定",
		MB_ICONQUESTION | MB_YESNO)==IDNO)return;
	CDialogEx::OnOK();
}


BOOL CSendInforDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_ctrlLevel.AddString("全体");
	m_ctrlLevel.AddString("部门");
	m_ctrlLevel.AddString("个人");

	m_ctrlDepart.AddString("学籍部");
	m_ctrlDepart.AddString("招生部");
	m_ctrlDepart.AddString("组织部");
	m_ctrlDepart.AddString("财务部");
	m_ctrlDepart.AddString("技术部");

	
	try
	{
		//Connect to the database
		Cperson recordset(&theApp.m_DB);
		CString strSQL;
		strSQL = "select * from person";
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return 1;
		}

		while (!recordset.IsEOF())
		{
			if (recordset.m_pname!=theApp.m_strUserName)
				m_ctrlPerson.AddString(recordset.m_pname);
			recordset.MoveNext();
		}
		recordset.Close();

		m_ctrlDepart.EnableWindow(FALSE);
		m_ctrlPerson.EnableWindow(FALSE);

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
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
