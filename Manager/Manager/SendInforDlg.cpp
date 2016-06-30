// SendInforDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "SendInforDlg.h"
#include "afxdialogex.h"
#include"person.h"

// CSendInforDlg �Ի���

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


// CSendInforDlg ��Ϣ�������


void CSendInforDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iPos = m_ctrlLevel.GetCurSel();//��ǰѡ�е��С�
	m_ctrlLevel.SetCurSel(iPos);//���õ�n������Ϊ��ʾ�����ݡ�
	m_ctrlLevel.GetLBText(iPos, m_strLevel);

	if (m_strLevel == "ȫ��")
	{
		m_strDepart = "";
		m_strPerson = "";
		m_ctrlDepart.EnableWindow(FALSE);
		m_ctrlPerson.EnableWindow(FALSE);
	}
	else if (m_strLevel == "����")
	{
		m_ctrlDepart.EnableWindow(TRUE);
		m_strPerson = "";
		m_ctrlPerson.EnableWindow(FALSE);
	}
	else if (m_strLevel == "����")
	{
		m_strDepart = "";
		m_ctrlDepart.EnableWindow(FALSE);
		m_ctrlPerson.EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}


void CSendInforDlg::OnCbnSelchangeCombo2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iPos = m_ctrlDepart.GetCurSel();//��ǰѡ�е��С�
	m_ctrlDepart.SetCurSel(iPos);//���õ�n������Ϊ��ʾ�����ݡ�
	m_ctrlDepart.GetLBText(iPos, m_strDepart);
}


void CSendInforDlg::OnCbnSelchangeCombo3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iPos = m_ctrlPerson.GetCurSel();//��ǰѡ�е��С�
	m_ctrlPerson.SetCurSel(iPos);//���õ�n������Ϊ��ʾ�����ݡ�
	m_ctrlPerson.GetLBText(iPos, m_strPerson);
}


void CSendInforDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	UpdateData(TRUE);
	CString str;
	if (m_strLevel == "ȫ��")
	{
		str = "ȫ����Ա������Ϣ";
	}
	else if (m_strLevel == "����")
	{
		if (m_strDepart.GetLength()==0)
		{
			MessageBoxA("Ҫ�����ŷ�����Ϣ��ѡ���ţ�", "��ѡ����",
				MB_ICONINFORMATION | MB_OK);
			return;
		}
		str = m_strDepart+"����Ա������Ϣ";
	}
	else if (m_strLevel == "����")
	{
		if (m_strPerson.GetLength() == 0)
		{
			MessageBoxA("Ҫ�����˷�����Ϣ��ѡ����ˣ�", "��ѡ�����",
				MB_ICONINFORMATION | MB_OK);
			return;
		}
		str = m_strPerson + "������Ϣ";
	}
	else
	{
		MessageBoxA("��ѡ����Ϣ����", "��ѡ��",
			MB_ICONINFORMATION | MB_OK);
		return;
	}
	if (m_strInfor.GetLength() == 0)
	{
		MessageBoxA("����д��Ϣ���ݣ�", "����д����",
			MB_ICONINFORMATION | MB_OK);
		return;
	}
	if(MessageBoxA("�㽫Ҫ��"+str+"\n�����ȷ������ť���޷����أ�", "��ȷ��",
		MB_ICONQUESTION | MB_YESNO)==IDNO)return;
	CDialogEx::OnOK();
}


BOOL CSendInforDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_ctrlLevel.AddString("ȫ��");
	m_ctrlLevel.AddString("����");
	m_ctrlLevel.AddString("����");

	m_ctrlDepart.AddString("ѧ����");
	m_ctrlDepart.AddString("������");
	m_ctrlDepart.AddString("��֯��");
	m_ctrlDepart.AddString("����");
	m_ctrlDepart.AddString("������");

	
	try
	{
		//Connect to the database
		Cperson recordset(&theApp.m_DB);
		CString strSQL;
		strSQL = "select * from person";
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
