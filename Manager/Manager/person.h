// person.h : Cperson ������

#pragma once

// ���������� 2016��1��29��, 13:17

/*Cperson ��Ա���Ӧ���ݿ��person ��*/
class Cperson : public CRecordset
{
public:
	Cperson(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Cperson)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	CString	m_pname;//�û���
	CString	m_id;//ѧ��
	BOOL	m_sex;//�Ա�
	CString	m_academy;//ѧԺ
	CString	m_major;//רҵ
	CString	m_telephone;//�ֻ�
	CTime	m_join_date;//��ְʱ��
	CString	m_post;//ְ��
	CString	m_introduction;//���
	CString	m_department;//����
	CString	m_passwd;//����
	long m_privilege;//Ȩ��
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


