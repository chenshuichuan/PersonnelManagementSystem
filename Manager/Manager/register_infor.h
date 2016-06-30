// register_infor.h : CRegisterSet ������

#pragma once

// ���������� 2016��1��29��, 23:27

class CRegisterSet : public CRecordset
{
public:
	CRegisterSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRegisterSet)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	long	m_sign_id;	//ǩ����Ϣid
	CTime	m_start_time;
	CTime	m_end_time;
	double	m_working_hours;	//��ʱ�ļ���Ϊ�°�ʱ���ȥ�ϰ�ʱ�䣬����1λС��
	long	m_week_number;
	CString	m_signer;
	CString	m_extra_infor;

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


