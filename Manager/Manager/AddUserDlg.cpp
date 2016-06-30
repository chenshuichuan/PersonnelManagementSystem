// AddUserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "AddUserDlg.h"
#include "afxdialogex.h"


// CAddUserDlg �Ի���

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


// CAddUserDlg ��Ϣ�������

//�Ա�
void CAddUserDlg::OnCbnSelchangeCombo4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iPos = m_ctrlSex.GetCurSel();//��ǰѡ�е��С�
	m_ctrlSex.SetCurSel(iPos);//���õ�n������Ϊ��ʾ�����ݡ�
	m_ctrlSex.GetLBText(iPos, m_strSex);
}

//����
void CAddUserDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iPos = m_ctrlDepart.GetCurSel();//��ǰѡ�е��С�
	m_ctrlDepart.SetCurSel(iPos);//���õ�n������Ϊ��ʾ�����ݡ�
	m_ctrlDepart.GetLBText(iPos, m_strDepart);
}

//ְλ
void CAddUserDlg::OnCbnSelchangeCombo2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iPos = m_ctrlPost.GetCurSel();//��ǰѡ�е��С�
	m_ctrlPost.SetCurSel(iPos);//���õ�n������Ϊ��ʾ�����ݡ�
	m_ctrlPost.GetLBText(iPos, m_strPost);
}

//Ȩ��
void CAddUserDlg::OnCbnSelchangeCombo3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iPos = m_ctrlPrivilige.GetCurSel();//��ǰѡ�е��С�
	m_ctrlPrivilige.SetCurSel(iPos);//���õ�n������Ϊ��ʾ�����ݡ�
	m_ctrlPrivilige.GetLBText(iPos, m_strPrivilige);
}


void CAddUserDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
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
		MessageBox("��������Ϊ�գ�����������!", "�������", MB_OK);
		return;
	}
	if (m_strSex.GetLength() == 0)
	{
		MessageBox("�Ա���Ϊ�գ�����������!", "�������", MB_OK);
		return;
	}
	if (m_strPost.GetLength() == 0)
	{
		MessageBox("ְλ����Ϊ�գ�����������!", "�������", MB_OK);
		return;
	}
	if (m_strPasswd.GetLength() < 6)
	{
		MessageBox("���벻������6���ַ�������������!", "�������", MB_OK);
		return;
	}
	if (m_strPrivilige.GetLength() == 0)
	{
		MessageBox("Ȩ�޲���Ϊ�գ�����������!", "�������", MB_OK);
		return;
	}
	CDialogEx::OnOK();
}


BOOL CAddUserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ctrlPost.AddString("��ʦ");
	m_ctrlPost.AddString("��ϯ");
	m_ctrlPost.AddString("����");
	m_ctrlPost.AddString("������");
	m_ctrlPost.AddString("����");

	m_ctrlDepart.AddString("����");
	m_ctrlDepart.AddString("ѧ����");
	m_ctrlDepart.AddString("������");
	m_ctrlDepart.AddString("��֯��");
	m_ctrlDepart.AddString("����");
	m_ctrlDepart.AddString("������");
	
	m_ctrlSex.AddString("��");
	m_ctrlSex.AddString("Ů");
	
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
		m_strPost = "����";
		m_strDepart = "������";
		m_strSex = "Ů";
		m_strPrivilige = "0";
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
