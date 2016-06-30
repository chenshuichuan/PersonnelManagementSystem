// receive_infor.h : CReceiveSet ���ʵ��



// CReceiveSet ʵ��

// ���������� 2016��2��1��, 9:50

#include "stdafx.h"
#include "receive_infor.h"
IMPLEMENT_DYNAMIC(CReceiveSet, CRecordset)

CReceiveSet::CReceiveSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_message_id = 0;
	m_message_infor = L"";
	m_sender = L"";
	m_send_date;
	m_receiver = L"";
	m_message_level = L"";
	m_is_read = FALSE;
	m_nFields = 7;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CReceiveSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=MS Access Database");
	//return _T("DSN=personManager;DBQ=datadb.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=zhaosheng123;UID=admin;");
}

CString CReceiveSet::GetDefaultSQL()
{
	return _T("[receive_infor]");
}

void CReceiveSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[message_id]"), m_message_id);
	RFX_Text(pFX, _T("[message_infor]"), m_message_infor);
	RFX_Text(pFX, _T("[sender]"), m_sender);
	RFX_Date(pFX, _T("[send_date]"), m_send_date);
	RFX_Text(pFX, _T("[receiver]"), m_receiver);
	RFX_Text(pFX, _T("[message_level]"), m_message_level);
	RFX_Bool(pFX, _T("[is_read]"), m_is_read);

}
/////////////////////////////////////////////////////////////////////////////
// CReceiveSet ���

#ifdef _DEBUG
void CReceiveSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CReceiveSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


