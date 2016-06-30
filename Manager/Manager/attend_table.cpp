// attend_table.h : CAttend_tableSet ���ʵ��



// CAttend_tableSet ʵ��

// ���������� 2016��2��17��, 17:38

#include "stdafx.h"
#include "attend_table.h"
IMPLEMENT_DYNAMIC(CAttend_tableSet, CRecordset)

CAttend_tableSet::CAttend_tableSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_week_number = 0;
	m_extra_infor = L"";
	m_Monday12 = L"";
	m_Monday34 = L"";
	m_Monday56 = L"";
	m_Monday78 = L"";
	m_Tuesday12 = L"";
	m_Tuesday34 = L"";
	m_Tuesday56 = L"";
	m_Tuesday78 = L"";
	m_Wednesday12 = L"";
	m_Wednesday34 = L"";
	m_Wednesday56 = L"";
	m_Wednesday78 = L"";
	m_Thursday12 = L"";
	m_Thursday34 = L"";
	m_Thursday56 = L"";
	m_Thursday78 = L"";
	m_Friday12 = L"";
	m_Friday34 = L"";
	m_Friday56 = L"";
	m_Friday78 = L"";
	m_Saturday12 = L"";
	m_Saturday34 = L"";
	m_Saturday56 = L"";
	m_Saturday78 = L"";
	m_Sunday12 = L"";
	m_Sunday34 = L"";
	m_Sunday56 = L"";
	m_Sunday78 = L"";
	m_nFields = 30;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CAttend_tableSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=MS Access Database");
	//return _T("DSN=personManager;DBQ=C:\\Users\\yuan\\Desktop\\\x4eba\x4e8b\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf\\datadb.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=zhaosheng123;UID=admin;");
}

CString CAttend_tableSet::GetDefaultSQL()
{
	return _T("[attend_table]");
}

void CAttend_tableSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[week_number]"), m_week_number);
	RFX_Text(pFX, _T("[extra_infor]"), m_extra_infor);
	RFX_Text(pFX, _T("[Monday12]"), m_Monday12);
	RFX_Text(pFX, _T("[Monday34]"), m_Monday34);
	RFX_Text(pFX, _T("[Monday56]"), m_Monday56);
	RFX_Text(pFX, _T("[Monday78]"), m_Monday78);
	RFX_Text(pFX, _T("[Tuesday12]"), m_Tuesday12);
	RFX_Text(pFX, _T("[Tuesday34]"), m_Tuesday34);
	RFX_Text(pFX, _T("[Tuesday56]"), m_Tuesday56);
	RFX_Text(pFX, _T("[Tuesday78]"), m_Tuesday78);
	RFX_Text(pFX, _T("[Wednesday12]"), m_Wednesday12);
	RFX_Text(pFX, _T("[Wednesday34]"), m_Wednesday34);
	RFX_Text(pFX, _T("[Wednesday56]"), m_Wednesday56);
	RFX_Text(pFX, _T("[Wednesday78]"), m_Wednesday78);
	RFX_Text(pFX, _T("[Thursday12]"), m_Thursday12);
	RFX_Text(pFX, _T("[Thursday34]"), m_Thursday34);
	RFX_Text(pFX, _T("[Thursday56]"), m_Thursday56);
	RFX_Text(pFX, _T("[Thursday78]"), m_Thursday78);
	RFX_Text(pFX, _T("[Friday12]"), m_Friday12);
	RFX_Text(pFX, _T("[Friday34]"), m_Friday34);
	RFX_Text(pFX, _T("[Friday56]"), m_Friday56);
	RFX_Text(pFX, _T("[Friday78]"), m_Friday78);
	RFX_Text(pFX, _T("[Saturday12]"), m_Saturday12);
	RFX_Text(pFX, _T("[Saturday34]"), m_Saturday34);
	RFX_Text(pFX, _T("[Saturday56]"), m_Saturday56);
	RFX_Text(pFX, _T("[Saturday78]"), m_Saturday78);
	RFX_Text(pFX, _T("[Sunday12]"), m_Sunday12);
	RFX_Text(pFX, _T("[Sunday34]"), m_Sunday34);
	RFX_Text(pFX, _T("[Sunday56]"), m_Sunday56);
	RFX_Text(pFX, _T("[Sunday78]"), m_Sunday78);

}
/////////////////////////////////////////////////////////////////////////////
// CAttend_tableSet ���

#ifdef _DEBUG
void CAttend_tableSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAttend_tableSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


