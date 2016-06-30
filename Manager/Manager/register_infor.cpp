// register_infor.h : CRegisterSet ���ʵ��



// CRegisterSet ʵ��

// ���������� 2016��1��29��, 23:27

#include "stdafx.h"
#include "register_infor.h"
IMPLEMENT_DYNAMIC(CRegisterSet, CRecordset)

CRegisterSet::CRegisterSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_sign_id = 0;
	m_start_time;
	m_end_time;
	m_working_hours = 0;
	m_week_number = 0;
	m_signer = L"";
	m_extra_infor = L"";
	m_nFields = 7;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CRegisterSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=MS Access Database");
	//return _T("DSN=personManager;DBQ=C:\\Users\\yuan\\Desktop\\\x4eba\x4e8b\x4fe1\x606f\x7ba1\x7406\x7cfb\x7edf\\datadb.mdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;PWD=zhaosheng123;UID=admin;");
}

CString CRegisterSet::GetDefaultSQL()
{
	return _T("[register_infor]");
}

void CRegisterSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[sign_id]"), m_sign_id);
	RFX_Date(pFX, _T("[start_time]"), m_start_time);
	RFX_Date(pFX, _T("[end_time]"), m_end_time);
	RFX_Double(pFX, _T("[working_hours]"), m_working_hours);
	RFX_Long(pFX, _T("[week_number]"), m_week_number);
	RFX_Text(pFX, _T("[signer]"), m_signer);
	RFX_Text(pFX, _T("[extra_infor]"), m_extra_infor);

}
/////////////////////////////////////////////////////////////////////////////
// CRegisterSet ���

#ifdef _DEBUG
void CRegisterSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRegisterSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


