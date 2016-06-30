
// Manager.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include<string>
using namespace std;

// CManagerApp: 
// 有关此类的实现，请参阅 Manager.cpp
//

class CManagerApp : public CWinApp
{
public:
	CManagerApp();

	/*以下为在用户登录后保存用户信息，方便用户进入系统后直接使用*/
	// 用户输入的密码
	CString m_strPasswd;
	// 用户名
	CString m_strUserName;
	//学号
	CString m_id;
	//学院
	CString m_academy;
	//专业
	CString m_major;
	//性别
	BOOL m_sex;
	//手机
	CString m_phone;
	//入职时间
	CTime m_joinTime;
	//部门
	CString m_department;
	//职称
	CString m_post;
	//简介
	CString m_introduction;
	//权限
	long m_privilege;

	int m_nowWeek;//当前周数

public:
	CDatabase   m_DB;//全局数据库
	//打开数据库
	void OpenDB();
	//加载系统配置信息
	void LoadConfigInfor();
	//保存当前系统的配置信息
	void SaveConfigInfor();
	string CStringToString(const CString &cstr);
	CString StringToCString(const string &str);

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CManagerApp theApp;