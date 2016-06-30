
// Manager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include<string>
using namespace std;

// CManagerApp: 
// �йش����ʵ�֣������ Manager.cpp
//

class CManagerApp : public CWinApp
{
public:
	CManagerApp();

	/*����Ϊ���û���¼�󱣴��û���Ϣ�������û�����ϵͳ��ֱ��ʹ��*/
	// �û����������
	CString m_strPasswd;
	// �û���
	CString m_strUserName;
	//ѧ��
	CString m_id;
	//ѧԺ
	CString m_academy;
	//רҵ
	CString m_major;
	//�Ա�
	BOOL m_sex;
	//�ֻ�
	CString m_phone;
	//��ְʱ��
	CTime m_joinTime;
	//����
	CString m_department;
	//ְ��
	CString m_post;
	//���
	CString m_introduction;
	//Ȩ��
	long m_privilege;

	int m_nowWeek;//��ǰ����

public:
	CDatabase   m_DB;//ȫ�����ݿ�
	//�����ݿ�
	void OpenDB();
	//����ϵͳ������Ϣ
	void LoadConfigInfor();
	//���浱ǰϵͳ��������Ϣ
	void SaveConfigInfor();
	string CStringToString(const CString &cstr);
	CString StringToCString(const string &str);

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CManagerApp theApp;