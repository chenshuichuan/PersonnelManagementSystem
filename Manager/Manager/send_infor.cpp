// send_infor.h : CSendSet ���ʵ��



// CSendSet ʵ��

// ���������� 2016��2��1��, 9:53

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
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[message_id]"), m_message_id);
	RFX_Text(pFX, _T("[message_infor]"), m_message_infor);
	RFX_Text(pFX, _T("[sender]"), m_sender);
	RFX_Date(pFX, _T("[send_date]"), m_send_date);
	RFX_Text(pFX, _T("[message_level]"), m_message_level);
	RFX_Text(pFX, _T("[receiver]"), m_receiver);

}
/////////////////////////////////////////////////////////////////////////////
// CSendSet ���

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


