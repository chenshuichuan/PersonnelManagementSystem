// receive_infor.h : CReceiveSet ������

#pragma once

// ���������� 2016��2��1��, 9:50

class CReceiveSet : public CRecordset
{
public:
	CReceiveSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CReceiveSet)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	long	m_message_id;	//��Ϣ���
	CString	m_message_infor;	//��Ϣ����
	CString	m_sender;	//������
	CTime	m_send_date;	//��������
	CString	m_receiver;	//������ �и������� �������� ������
	CString	m_message_level;	//���� ���� ������
	BOOL	m_is_read;	//�Ƿ��Ѷ�

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


