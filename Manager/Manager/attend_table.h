// attend_table.h : CAttend_tableSet ������

#pragma once

// ���������� 2016��2��17��, 17:38

class CAttend_tableSet : public CRecordset
{
public:
	CAttend_tableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAttend_tableSet)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	long	m_week_number;	//ֵ�������
	CString	m_extra_infor;	//ֵ�౸ע������д���࣬����ȱ�����
	CString	m_Monday12;
	CString	m_Monday34;
	CString	m_Monday56;
	CString	m_Monday78;
	CString	m_Tuesday12;
	CString	m_Tuesday34;
	CString	m_Tuesday56;
	CString	m_Tuesday78;
	CString	m_Wednesday12;
	CString	m_Wednesday34;
	CString	m_Wednesday56;
	CString	m_Wednesday78;
	CString	m_Thursday12;
	CString	m_Thursday34;
	CString	m_Thursday56;
	CString	m_Thursday78;
	CString	m_Friday12;
	CString	m_Friday34;
	CString	m_Friday56;
	CString	m_Friday78;
	CString	m_Saturday12;
	CString	m_Saturday34;
	CString	m_Saturday56;
	CString	m_Saturday78;
	CString	m_Sunday12;
	CString	m_Sunday34;
	CString	m_Sunday56;
	CString	m_Sunday78;

// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


