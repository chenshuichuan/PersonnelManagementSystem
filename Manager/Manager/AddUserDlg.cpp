// AddUserDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "AddUserDlg.h"
#include "afxdialogex.h"


// CAddUserDlg 对话框

IMPLEMENT_DYNAMIC(CAddUserDlg, CDialogEx)

CAddUserDlg::CAddUserDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddUserDlg::IDD, pParent)
	, m_strName(_T(""))
	, m_strID(_T(""))
	, m_strSex(_T(""))
	, m_strJoinDate(_T(""))
	, m_strPost(_T(""))
	, m_strDepart(_T(""))
	, m_strAcademy(_T(""))
	, m_strMajor(_T(""))
	, m_strPhone(_T(""))
	, m_strPasswd(_T(""))
	, m_strPrivilige(_T(""))
	, m_strIntroduction(_T(""))
{

}

CAddUserDlg::~CAddUserDlg()
{
}

void CAddUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ctrlName);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_strID);
	DDX_Control(pDX, IDC_COMBO4, m_ctrlSex);
	DDX_CBString(pDX, IDC_COMBO4, m_strSex);
	//  DDX_Control(pDX, IDC_EDIT4, m_strJoinDate);
	DDX_Text(pDX, IDC_EDIT4, m_strJoinDate);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlDepart);
	DDX_Control(pDX, IDC_COMBO2, m_ctrlPost);
	DDX_CBString(pDX, IDC_COMBO2, m_strPost);
	DDX_CBString(pDX, IDC_COMBO1, m_strDepart);
	DDX_Text(pDX, IDC_EDIT8, m_strAcademy);
	DDX_Text(pDX, IDC_EDIT9, m_strMajor);
	DDX_Text(pDX, IDC_EDIT10, m_strPhone);
	DDX_Text(pDX, IDC_EDIT6, m_strPasswd);
	DDX_Control(pDX, IDC_COMBO3, m_ctrlPrivilige);
	DDX_CBString(pDX, IDC_COMBO3, m_strPrivilige);
	DDX_Text(pDX, IDC_EDIT7, m_strIntroduction);
}


BEGIN_MESSAGE_MAP(CAddUserDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CAddUserDlg::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddUserDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CAddUserDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CAddUserDlg::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// CAddUserDlg 消息处理程序

//性别
void CAddUserDlg::OnCbnSelchangeCombo4()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlSex.GetCurSel();//当前选中的行。
	m_ctrlSex.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlSex.GetLBText(iPos, m_strSex);
}

//部门
void CAddUserDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlDepart.GetCurSel();//当前选中的行。
	m_ctrlDepart.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlDepart.GetLBText(iPos, m_strDepart);
}

//职位
void CAddUserDlg::OnCbnSelchangeCombo2()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlPost.GetCurSel();//当前选中的行。
	m_ctrlPost.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlPost.GetLBText(iPos, m_strPost);
}

//权限
void CAddUserDlg::OnCbnSelchangeCombo3()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlPrivilige.GetCurSel();//当前选中的行。
	m_ctrlPrivilige.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlPrivilige.GetLBText(iPos, m_strPrivilige);
}


void CAddUserDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	/*m_strName;
	m_strID;
	m_strSex;
	m_strJoinDate;
	m_strPost;
	m_strDepart;
	m_strAcademy;
	m_strMajor;
	m_strPhone;
	m_strPasswd;
	m_strPrivilige;
	m_strIntroduction;*/
	UpdateData(TRUE);
	if (m_strName.GetLength() == 0)
	{
		MessageBox("姓名不能为空，请重新输入!", "输入错误", MB_OK);
		return;
	}
	if (m_strSex.GetLength() == 0)
	{
		MessageBox("性别不能为空，请重新输入!", "输入错误", MB_OK);
		return;
	}
	if (m_strPost.GetLength() == 0)
	{
		MessageBox("职位不能为空，请重新输入!", "输入错误", MB_OK);
		return;
	}
	if (m_strPasswd.GetLength() < 6)
	{
		MessageBox("密码不能少于6个字符，请重新输入!", "输入错误", MB_OK);
		return;
	}
	if (m_strPrivilige.GetLength() == 0)
	{
		MessageBox("权限不能为空，请重新输入!", "输入错误", MB_OK);
		return;
	}
	CDialogEx::OnOK();
}


BOOL CAddUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ctrlPost.AddString("老师");
	m_ctrlPost.AddString("主席");
	m_ctrlPost.AddString("部长");
	m_ctrlPost.AddString("副部长");
	m_ctrlPost.AddString("助理");

	m_ctrlDepart.AddString("其他");
	m_ctrlDepart.AddString("学籍部");
	m_ctrlDepart.AddString("招生部");
	m_ctrlDepart.AddString("组织部");
	m_ctrlDepart.AddString("财务部");
	m_ctrlDepart.AddString("技术部");
	
	m_ctrlSex.AddString("男");
	m_ctrlSex.AddString("女");
	
	m_ctrlPrivilige.AddString("0");
	m_ctrlPrivilige.AddString("1");
	m_ctrlPrivilige.AddString("2");
	m_ctrlPrivilige.AddString("3");
	
	if (is_edit)m_ctrlName.SetReadOnly(TRUE);
	else
	{
		CTime tm;
		tm = CTime::GetCurrentTime();
		m_strJoinDate = tm.Format("%Y-%m-%d");

		m_strPasswd = "666666";
		m_strPost = "助理";
		m_strDepart = "技术部";
		m_strSex = "女";
		m_strPrivilige = "0";
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
