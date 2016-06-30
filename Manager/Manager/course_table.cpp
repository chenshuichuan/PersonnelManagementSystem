// course_table.h : CCourseSet ���ʵ��



// CCourseSet ʵ��

// ���������� 2016��2��2��, 23:31

#include "stdafx.h"
#include "course_table.h"
IMPLEMENT_DYNAMIC(CCourseSet, CRecordset)

CCourseSet::CCourseSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_course_id = 0;
	m_pname = L"";
	m_extra_infor = L"";
	m_is_lock = FALSE;
	m_week_number = 0;
	m_Monday12 = FALSE;
	m_Monday34 = FALSE;
	m_Monday56 = FALSE;
	m_Monday78 = FALSE;
	m_Tuesday12 = FALSE;
	m_Tuesday34 = FALSE;
	m_Tuesday56 = FALSE;
	m_Tuesday78 = FALSE;
	m_Wednesday12 = FALSE;
	m_Wednesday34 = FALSE;
	m_Wednesday56 = FALSE;
	m_Wednesday78 = FALSE;
	m_Thursday12 = FALSE;
	m_Thursday34 = FALSE;
	m_Thursday56 = FALSE;
	m_Thursday78 = FALSE;
	m_Friday12 = FALSE;
	m_Friday34 = FALSE;
	m_Friday56 = FALSE;
	m_Friday78 = FALSE;
	m_Saturday12 = FALSE;
	m_Saturday34 = FALSE;
	m_Saturday56 = FALSE;
	m_Saturday78 = FALSE;
	m_Sunday12 = FALSE;
	m_Sunday34 = FALSE;
	m_Sunday56 = FALSE;
	m_Sunday78 = FALSE;
	m_nFields = 33;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CCourseSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=MS Access Database");
	//return _T("DSN=personManager;DBQ=C:\\Users\\yuan\\Desktop\\\x4eba\x4e8b\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf\\datadb.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=zhaosheng123;UID=admin;");
}

CString CCourseSet::GetDefaultSQL()
{
	return _T("[course_table]");
}

void CCourseSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[course_id]"), m_course_id);
	RFX_Text(pFX, _T("[pname]"), m_pname);
	RFX_Text(pFX, _T("[extra_infor]"), m_extra_infor);
	RFX_Bool(pFX, _T("[is_lock]"), m_is_lock);
	RFX_Long(pFX, _T("[week_number]"), m_week_number);
	RFX_Bool(pFX, _T("[Monday12]"), m_Monday12);
	RFX_Bool(pFX, _T("[Monday34]"), m_Monday34);
	RFX_Bool(pFX, _T("[Monday56]"), m_Monday56);
	RFX_Bool(pFX, _T("[Monday78]"), m_Monday78);
	RFX_Bool(pFX, _T("[Tuesday12]"), m_Tuesday12);
	RFX_Bool(pFX, _T("[Tuesday34]"), m_Tuesday34);
	RFX_Bool(pFX, _T("[Tuesday56]"), m_Tuesday56);
	RFX_Bool(pFX, _T("[Tuesday78]"), m_Tuesday78);
	RFX_Bool(pFX, _T("[Wednesday12]"), m_Wednesday12);
	RFX_Bool(pFX, _T("[Wednesday34]"), m_Wednesday34);
	RFX_Bool(pFX, _T("[Wednesday56]"), m_Wednesday56);
	RFX_Bool(pFX, _T("[Wednesday78]"), m_Wednesday78);
	RFX_Bool(pFX, _T("[Thursday12]"), m_Thursday12);
	RFX_Bool(pFX, _T("[Thursday34]"), m_Thursday34);
	RFX_Bool(pFX, _T("[Thursday56]"), m_Thursday56);
	RFX_Bool(pFX, _T("[Thursday78]"), m_Thursday78);
	RFX_Bool(pFX, _T("[Friday12]"), m_Friday12);
	RFX_Bool(pFX, _T("[Friday34]"), m_Friday34);
	RFX_Bool(pFX, _T("[Friday56]"), m_Friday56);
	RFX_Bool(pFX, _T("[Friday78]"), m_Friday78);
	RFX_Bool(pFX, _T("[Saturday12]"), m_Saturday12);
	RFX_Bool(pFX, _T("[Saturday34]"), m_Saturday34);
	RFX_Bool(pFX, _T("[Saturday56]"), m_Saturday56);
	RFX_Bool(pFX, _T("[Saturday78]"), m_Saturday78);
	RFX_Bool(pFX, _T("[Sunday12]"), m_Sunday12);
	RFX_Bool(pFX, _T("[Sunday34]"), m_Sunday34);
	RFX_Bool(pFX, _T("[Sunday56]"), m_Sunday56);
	RFX_Bool(pFX, _T("[Sunday78]"), m_Sunday78);

}
/////////////////////////////////////////////////////////////////////////////
// CCourseSet ���

#ifdef _DEBUG
void CCourseSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCourseSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


