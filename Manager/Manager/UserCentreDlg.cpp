// UserCentreDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "UserCentreDlg.h"
#include "afxdialogex.h"
#include"ChangePasswdDlg.h"

// CUserCentreDlg 对话框

IMPLEMENT_DYNAMIC(CUserCentreDlg, CDialogEx)

CUserCentreDlg::CUserCentreDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserCentreDlg::IDD, pParent)
	, m_strName(_T(""))
	, m_strId(_T(""))
	, m_strSex(_T(""))
	, m_strJoinDate(_T(""))
	, m_strDepart(_T(""))
	, m_strAcademy(_T(""))
	, m_strMajor(_T(""))
	, m_strPhone(_T(""))
	, m_strExtra(_T(""))
{

}

CUserCentreDlg::~CUserCentreDlg()
{
}

void CUserCentreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_strId);
	DDX_Text(pDX, IDC_EDIT3, m_strSex);
	DDX_Text(pDX, IDC_EDIT4, m_strJoinDate);
	DDX_Text(pDX, IDC_EDIT5, m_strDepart);
	DDX_Text(pDX, IDC_EDIT8, m_strAcademy);
	DDX_Text(pDX, IDC_EDIT9, m_strMajor);
	DDX_Text(pDX, IDC_EDIT10, m_strPhone);
	DDX_Text(pDX, IDC_EDIT7, m_strExtra);
	DDX_Control(pDX, IDC_EDIT8, m_ctrlAcademy);
	DDX_Control(pDX, IDC_EDIT9, m_ctrlMajor);
	DDX_Control(pDX, IDC_EDIT10, m_ctrlPhone);
	DDX_Control(pDX, IDC_EDIT7, m_ctrlExtra);
}


BEGIN_MESSAGE_MAP(CUserCentreDlg, CDialogEx)

	ON_BN_CLICKED(IDC_BTU_MODIFY, &CUserCentreDlg::OnBnClickedBtuModify)
	ON_BN_CLICKED(IDC_BTU_SAVE, &CUserCentreDlg::OnBnClickedBtuSave)
	ON_BN_CLICKED(IDC_BTU_PASSWD, &CUserCentreDlg::OnBnClickedBtuPasswd)
END_MESSAGE_MAP()


// CUserCentreDlg 消息处理程序


BOOL CUserCentreDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_strName=theApp.m_strUserName;
	m_strId = theApp.m_id;
	if (theApp.m_sex)m_strSex="男";
	else m_strSex = "女";
	m_strJoinDate=theApp.m_joinTime.Format("%Y-%m-%d");
	m_strDepart=theApp.m_department;
	m_strAcademy=theApp.m_academy;
	m_strMajor=theApp.m_major;
	m_strPhone=theApp.m_phone;
	m_strExtra=theApp.m_introduction;

	
	m_ctrlAcademy.SetReadOnly(TRUE);
	m_ctrlMajor.SetReadOnly(TRUE);
	m_ctrlPhone.SetReadOnly(TRUE);
	m_ctrlExtra.SetReadOnly(TRUE);

	GetDlgItem(IDC_BTU_SAVE)->EnableWindow(FALSE);
	UpdateData(FALSE);
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CUserCentreDlg::OnBnClickedBtuModify()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItem(IDC_BTU_SAVE)->EnableWindow(TRUE);
	m_ctrlAcademy.SetReadOnly(FALSE);
	m_ctrlMajor.SetReadOnly(FALSE);
	m_ctrlPhone.SetReadOnly(FALSE);
	m_ctrlExtra.SetReadOnly(FALSE);
}


void CUserCentreDlg::OnBnClickedBtuSave()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	try{
		CString update;
		update.Format("update  person set academy='%s',major='%s',"
			"telephone='%s',introduction='%s' where pname='%s'"
			, m_strAcademy, m_strMajor, m_strPhone, m_strExtra, m_strName);
		theApp.m_DB.ExecuteSQL(update);

		m_ctrlAcademy.SetReadOnly(TRUE);
		m_ctrlMajor.SetReadOnly(TRUE);
		m_ctrlPhone.SetReadOnly(TRUE);
		m_ctrlExtra.SetReadOnly(TRUE);
		GetDlgItem(IDC_BTU_SAVE)->EnableWindow(FALSE);
		UpdateData(FALSE);
		return;
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
	MessageBox("更新个人信息失败！请重试！", "更新失败", MB_OK);
}


void CUserCentreDlg::OnBnClickedBtuPasswd()
{
	// TODO:  在此添加控件通知处理程序代码
	CChangePasswdDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		try{
			CString update;
			update.Format("update  person set passwd='%s' where pname='%s'"
				, dlg.m_strNew1, m_strName);
			theApp.m_DB.ExecuteSQL(update);
			theApp.m_strPasswd = dlg.m_strNew1;
			MessageBox("更新密码成功！", "成功", MB_OK);
			return;
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
		MessageBox("更新密码失败！请重试或联系管理员！", "更新失败", MB_OK);
	}
}
