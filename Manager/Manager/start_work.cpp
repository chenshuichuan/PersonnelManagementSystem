// start_work.h : CSignSet ���ʵ��



// CSignSet ʵ��

// ���������� 2016��1��29��, 23:19

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
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[start_id]"), m_start_id);
	RFX_Text(pFX, _T("[signer]"), m_signer);
	RFX_Date(pFX, _T("[start_time]"), m_start_time);
	RFX_Bool(pFX, _T("[is_lock]"), m_is_lock);

}
/////////////////////////////////////////////////////////////////////////////
// CSignSet ���

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


