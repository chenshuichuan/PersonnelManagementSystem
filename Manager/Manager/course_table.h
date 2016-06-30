// course_table.h : CCourseSet ������

#pragma once

// ���������� 2016��2��2��, 23:31

class CCourseSet : public CRecordset
{
public:
	CCourseSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCourseSet)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	long	m_course_id;	//�ܿα���
	CString	m_pname;	//�ñ�������˭��
	CString	m_extra_infor;	//���ܿγ��ر�֮���ı�ע��Ϣ
	BOOL	m_is_lock;	//�α��Ѿ����������򲻿����޸�
	long	m_week_number;	//���ܿγ���Ϣ���ڵ�����
	BOOL	m_Monday12;
	BOOL	m_Monday34;
	BOOL	m_Monday56;
	BOOL	m_Monday78;
	BOOL	m_Tuesday12;
	BOOL	m_Tuesday34;
	BOOL	m_Tuesday56;
	BOOL	m_Tuesday78;
	BOOL	m_Wednesday12;
	BOOL	m_Wednesday34;
	BOOL	m_Wednesday56;
	BOOL	m_Wednesday78;
	BOOL	m_Thursday12;
	BOOL	m_Thursday34;
	BOOL	m_Thursday56;
	BOOL	m_Thursday78;
	BOOL	m_Friday12;
	BOOL	m_Friday34;
	BOOL	m_Friday56;
	BOOL	m_Friday78;
	BOOL	m_Saturday12;
	BOOL	m_Saturday34;
	BOOL	m_Saturday56;
	BOOL	m_Saturday78;
	BOOL	m_Sunday12;
	BOOL	m_Sunday34;
	BOOL	m_Sunday56;
	BOOL	m_Sunday78;

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


