// send_infor.h : CSendSet 类的实现



// CSendSet 实现

// 代码生成在 2016年2月1日, 9:53

#include "stdafx.h"
#include "send_infor.h"
IMPLEMENT_DYNAMIC(CSendSet, CRecordset)

CSendSet::CSendSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_message_id = 0;
	m_message_infor = L"";
	m_sender = L"";
	m_send_date;
	m_message_level = L"";
	m_receiver = L"";
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CSendSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=MS Access Database");
	//return _T("DSN=personManager;DBQ=C:\\Users\\yuan\\Desktop\\\x4eba\x4e8b\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf\\datadb.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=zhaosheng123;UID=admin;");
}

CString CSendSet::GetDefaultSQL()
{
	return _T("[send_infor]");
}

void CSendSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[message_id]"), m_message_id);
	RFX_Text(pFX, _T("[message_infor]"), m_message_infor);
	RFX_Text(pFX, _T("[sender]"), m_sender);
	RFX_Date(pFX, _T("[send_date]"), m_send_date);
	RFX_Text(pFX, _T("[message_level]"), m_message_level);
	RFX_Text(pFX, _T("[receiver]"), m_receiver);

}
/////////////////////////////////////////////////////////////////////////////
// CSendSet 诊断

#ifdef _DEBUG
void CSendSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSendSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


