// person.h : Cperson 的声明

#pragma once

// 代码生成在 2016年1月29日, 13:17

/*Cperson 人员类对应数据库的person 表*/
class Cperson : public CRecordset
{
public:
	Cperson(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Cperson)

// 字段/参数数据

// 以下字符串类型(如果存在)反映数据库字段(ANSI 数据类型的 CStringA 和 Unicode
// 数据类型的 CStringW)的实际数据类型。
//  这是为防止 ODBC 驱动程序执行可能
// 不必要的转换。如果希望，可以将这些成员更改为
// CString 类型，ODBC 驱动程序将执行所有必要的转换。
// (注意: 必须使用 3.5 版或更高版本的 ODBC 驱动程序
// 以同时支持 Unicode 和这些转换)。

	CString	m_pname;//用户名
	CString	m_id;//学号
	BOOL	m_sex;//性别
	CString	m_academy;//学院
	CString	m_major;//专业
	CString	m_telephone;//手机
	CTime	m_join_date;//入职时间
	CString	m_post;//职称
	CString	m_introduction;//简介
	CString	m_department;//部门
	CString	m_passwd;//密码
	long m_privilege;//权限
// 重写
	// 向导生成的虚函数重写
	public:
	virtual CString GetDefaultConnect();	// 默认连接字符串

	virtual CString GetDefaultSQL(); 	// 记录集的默认 SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX 支持

// 实现
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


