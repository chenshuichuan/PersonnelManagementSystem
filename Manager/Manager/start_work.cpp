// start_work.h : CSignSet 类的实现



// CSignSet 实现

// 代码生成在 2016年1月29日, 23:19

#include "stdafx.h"
#include "start_work.h"
IMPLEMENT_DYNAMIC(CSignSet, CRecordset)

CSignSet::CSignSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_start_id = 0;
	m_signer = L"";
	m_start_time;
	m_is_lock = FALSE;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CSignSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=MS Access Database");
	//return _T("DSN=personManager;DBQ=C:\\Users\\yuan\\Desktop\\\x4eba\x4e8b\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf\\datadb.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=zhaosheng123;UID=admin;");
}

CString CSignSet::GetDefaultSQL()
{
	return _T("[start_work]");
}

void CSignSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[start_id]"), m_start_id);
	RFX_Text(pFX, _T("[signer]"), m_signer);
	RFX_Date(pFX, _T("[start_time]"), m_start_time);
	RFX_Bool(pFX, _T("[is_lock]"), m_is_lock);

}
/////////////////////////////////////////////////////////////////////////////
// CSignSet 诊断

#ifdef _DEBUG
void CSignSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSignSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


