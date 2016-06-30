// person.h : Cperson ���ʵ��



// Cperson ʵ��

// ���������� 2016��1��29��, 13:17

#include "stdafx.h"
#include "person.h"
IMPLEMENT_DYNAMIC(Cperson, CRecordset)

Cperson::Cperson(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_pname = L"";
	m_id = L"";
	m_sex = FALSE;
	m_academy = L"";
	m_major = L"";
	m_telephone = L"";
	m_join_date;
	m_post = L"";
	m_introduction = L"";
	m_department = L"";
	m_passwd = L"";
	m_privilege = 0;
	m_nFields = 12;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString Cperson::GetDefaultConnect()
{
	return _T("ODBC;DSN=MS Access Database");
	//return _T("DSN=personManager;DBQ=datadb.mdb;PWD=zhaosheng123;UID=admin;");
}

CString Cperson::GetDefaultSQL()
{
	return _T("[person]");
}

void Cperson::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[pname]"), m_pname);
	RFX_Text(pFX, _T("[id]"), m_id);
	RFX_Bool(pFX, _T("[sex]"), m_sex);
	RFX_Text(pFX, _T("[academy]"), m_academy);
	RFX_Text(pFX, _T("[major]"), m_major);
	RFX_Text(pFX, _T("[telephone]"), m_telephone);
	RFX_Date(pFX, _T("[join_date]"), m_join_date);
	RFX_Text(pFX, _T("[post]"), m_post);
	RFX_Text(pFX, _T("[introduction]"), m_introduction);
	RFX_Text(pFX, _T("[department]"), m_department);
	RFX_Text(pFX, _T("[passwd]"), m_passwd);
	RFX_Long(pFX, _T("[privilege]"), m_privilege);
}
/////////////////////////////////////////////////////////////////////////////
// Cperson ���

#ifdef _DEBUG
void Cperson::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cperson::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


