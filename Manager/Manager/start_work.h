// start_work.h : CSignSet ������

#pragma once

// ���������� 2016��1��29��, 23:19
//CSignSet �࣬��Ӧ���ݿ��start_work ���ݱ�
class CSignSet : public CRecordset
{
public:
	CSignSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSignSet)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	long	m_start_id;
	CString	m_signer;    //ǩ����
	CTime	m_start_time;
	BOOL	m_is_lock;	//��Ϣ�Ƿ��Ѿ�������("��"�����ܱ��޸�)

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


