// receive_infor.h : CReceiveSet 的声明

#pragma once

// 代码生成在 2016年2月1日, 9:50

class CReceiveSet : public CRecordset
{
public:
	CReceiveSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CReceiveSet)

// 字段/参数数据

// 以下字符串类型(如果存在)反映数据库字段(ANSI 数据类型的 CStringA 和 Unicode
// 数据类型的 CStringW)的实际数据类型。
//  这是为防止 ODBC 驱动程序执行可能
// 不必要的转换。如果希望，可以将这些成员更改为
// CString 类型，ODBC 驱动程序将执行所有必要的转换。
// (注意: 必须使用 3.5 版或更高版本的 ODBC 驱动程序
// 以同时支持 Unicode 和这些转换)。

	long	m_message_id;	//信息编号
	CString	m_message_infor;	//信息内容
	CString	m_sender;	//发送者
	CTime	m_send_date;	//发送日期
	CString	m_receiver;	//接收者 有个人姓名 部门名称 所有人
	CString	m_message_level;	//个人 部门 所有人
	BOOL	m_is_read;	//是否已读

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


