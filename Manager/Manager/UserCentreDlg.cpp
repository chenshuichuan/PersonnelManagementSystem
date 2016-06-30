// UserCentreDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "UserCentreDlg.h"
#include "afxdialogex.h"
#include"ChangePasswdDlg.h"

// CUserCentreDlg �Ի���

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


// CUserCentreDlg ��Ϣ�������


BOOL CUserCentreDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_strName=theApp.m_strUserName;
	m_strId = theApp.m_id;
	if (theApp.m_sex)m_strSex="��";
	else m_strSex = "Ů";
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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CUserCentreDlg::OnBnClickedBtuModify()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BTU_SAVE)->EnableWindow(TRUE);
	m_ctrlAcademy.SetReadOnly(FALSE);
	m_ctrlMajor.SetReadOnly(FALSE);
	m_ctrlPhone.SetReadOnly(FALSE);
	m_ctrlExtra.SetReadOnly(FALSE);
}


void CUserCentreDlg::OnBnClickedBtuSave()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	MessageBox("���¸�����Ϣʧ�ܣ������ԣ�", "����ʧ��", MB_OK);
}


void CUserCentreDlg::OnBnClickedBtuPasswd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CChangePasswdDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		try{
			CString update;
			update.Format("update  person set passwd='%s' where pname='%s'"
				, dlg.m_strNew1, m_strName);
			theApp.m_DB.ExecuteSQL(update);
			theApp.m_strPasswd = dlg.m_strNew1;
			MessageBox("��������ɹ���", "�ɹ�", MB_OK);
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
		MessageBox("��������ʧ�ܣ������Ի���ϵ����Ա��", "����ʧ��", MB_OK);
	}
}
