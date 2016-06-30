// send_infor.h : CSendSet ������

#pragma once

// ���������� 2016��2��1��, 9:53

class CSendSet : public CRecordset
{
public:
	CSendSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSendSet)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	long	m_message_id;
	CString	m_message_infor;
	CString	m_sender;
	CTime	m_send_date;
	CString	m_message_level;	//ֻ�С����ˡ��������š�����ȫ�塱����������
	CString	m_receiver;	//����Ǹ�����Ϣ���ֵΪ��������������Ϊ�������ƻ�ȫ��

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


