// person.h : Cperson 类的实现



// Cperson 实现

// 代码生成在 2016年1月29日, 13:17

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
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
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
// Cperson 诊断

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


