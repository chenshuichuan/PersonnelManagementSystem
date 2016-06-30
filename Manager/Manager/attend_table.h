// attend_table.h : CAttend_tableSet 的声明

#pragma once

// 代码生成在 2016年2月17日, 17:38

class CAttend_tableSet : public CRecordset
{
public:
	CAttend_tableSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAttend_tableSet)

// 字段/参数数据

// 以下字符串类型(如果存在)反映数据库字段(ANSI 数据类型的 CStringA 和 Unicode
// 数据类型的 CStringW)的实际数据类型。
//  这是为防止 ODBC 驱动程序执行可能
// 不必要的转换。如果希望，可以将这些成员更改为
// CString 类型，ODBC 驱动程序将执行所有必要的转换。
// (注意: 必须使用 3.5 版或更高版本的 ODBC 驱动程序
// 以同时支持 Unicode 和这些转换)。

	long	m_week_number;	//值班表周数
	CString	m_extra_infor;	//值班备注可以填写调班，换班缺到情况
	CString	m_Monday12;
	CString	m_Monday34;
	CString	m_Monday56;
	CString	m_Monday78;
	CString	m_Tuesday12;
	CString	m_Tuesday34;
	CString	m_Tuesday56;
	CString	m_Tuesday78;
	CString	m_Wednesday12;
	CString	m_Wednesday34;
	CString	m_Wednesday56;
	CString	m_Wednesday78;
	CString	m_Thursday12;
	CString	m_Thursday34;
	CString	m_Thursday56;
	CString	m_Thursday78;
	CString	m_Friday12;
	CString	m_Friday34;
	CString	m_Friday56;
	CString	m_Friday78;
	CString	m_Saturday12;
	CString	m_Saturday34;
	CString	m_Saturday56;
	CString	m_Saturday78;
	CString	m_Sunday12;
	CString	m_Sunday34;
	CString	m_Sunday56;
	CString	m_Sunday78;

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


