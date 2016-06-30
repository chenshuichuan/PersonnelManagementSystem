// course_table.h : CCourseSet 的声明

#pragma once

// 代码生成在 2016年2月2日, 23:31

class CCourseSet : public CRecordset
{
public:
	CCourseSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCourseSet)

// 字段/参数数据

// 以下字符串类型(如果存在)反映数据库字段(ANSI 数据类型的 CStringA 和 Unicode
// 数据类型的 CStringW)的实际数据类型。
//  这是为防止 ODBC 驱动程序执行可能
// 不必要的转换。如果希望，可以将这些成员更改为
// CString 类型，ODBC 驱动程序将执行所有必要的转换。
// (注意: 必须使用 3.5 版或更高版本的 ODBC 驱动程序
// 以同时支持 Unicode 和这些转换)。

	long	m_course_id;	//周课表编号
	CString	m_pname;	//该表是属于谁的
	CString	m_extra_infor;	//这周课程特别之处的备注信息
	BOOL	m_is_lock;	//课表已经被锁定，则不可以修改
	long	m_week_number;	//该周课程信息属于的周数
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


