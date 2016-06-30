// RecordDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "RecordDlg.h"
#include "afxdialogex.h"
#include"register_infor.h"
#include"person.h"
#include"EditRecordDlg.h"
#include"excel9.h"

// CRecordDlg 对话框

IMPLEMENT_DYNAMIC(CRecordDlg, CDialogEx)

CRecordDlg::CRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRecordDlg::IDD, pParent)
	, m_boolName(FALSE)
	, m_boolMonth(FALSE)
	, m_boolWeek(FALSE)
	, m_boolDay(FALSE)
	, m_strMonth(_T(""))
	, m_strWeek(_T(""))
	, m_ctimeDay(0)
	, m_strSQL(_T(""))
	, m_intTotalTime(0)
	, m_strName(_T(""))
	, m_strTotalHours(_T(""))
{

}

CRecordDlg::~CRecordDlg()
{
}

void CRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
	DDX_Check(pDX, IDC_CHECK1, m_boolName);
	DDX_Check(pDX, IDC_CHECK2, m_boolMonth);
	DDX_Check(pDX, IDC_CHECK3, m_boolWeek);
	DDX_Check(pDX, IDC_CHECK4, m_boolDay);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlName);
	DDX_Control(pDX, IDC_COMBO2, m_ctrlMonth);
	DDX_CBString(pDX, IDC_COMBO2, m_strMonth);
	DDX_Control(pDX, IDC_COMBO3, m_ctrlWeek);
	DDX_CBString(pDX, IDC_COMBO3, m_strWeek);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_ctimeDay);
	DDX_Text(pDX, IDC_EDIT2, m_strSQL);
	DDX_Text(pDX, IDC_EDIT3, m_intTotalTime);
	//  DDX_Text(pDX, IDC_EDIT4, m_intTotalHours);
	DDX_CBString(pDX, IDC_COMBO1, m_strName);
	DDX_Text(pDX, IDC_EDIT4, m_strTotalHours);
	DDX_Control(pDX, IDC_CHECK2, m_ctrlCheckMonth);
	DDX_Control(pDX, IDC_CHECK3, m_ctrlCheckWeek);
	DDX_Control(pDX, IDC_CHECK4, m_ctrlCheckDay);
}


BEGIN_MESSAGE_MAP(CRecordDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTRECORD_FIND, &CRecordDlg::OnBnClickedBtrecordFind)
	ON_BN_CLICKED(IDC_BTRECORD_EXPORT, &CRecordDlg::OnBnClickedBtrecordExport)
	ON_BN_CLICKED(IDC_BTRECORD_REFRASH, &CRecordDlg::OnBnClickedBtrecordRefrash)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CRecordDlg::OnNMRClickList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CRecordDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CRecordDlg::OnCbnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CRecordDlg::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_CHECK2, &CRecordDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CRecordDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CRecordDlg::OnBnClickedCheck4)
END_MESSAGE_MAP()


// CRecordDlg 消息处理程序


BOOL CRecordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//为列表视图控件添加全行选中和栅格风格
	//LVS_EX_FULLROWSELECT 全行选择
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |
		LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT;
	m_ctrlList.SetExtendedStyle(dwExStyle);
	//获取列表控件矩形
	CRect rect;
	m_ctrlList.GetClientRect(&rect);
	int wide = rect.Width();//取得列表控件宽度
	//初始化联系人列表控件
	m_ctrlList.InsertColumn(0, (LPCTSTR)"信息ID", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(1, (LPCTSTR) "签到", LVCFMT_LEFT, 80);
	m_ctrlList.InsertColumn(2, (LPCTSTR)"上班签到时间", LVCFMT_LEFT, 120);
	m_ctrlList.InsertColumn(3, (LPCTSTR)"下班签到时间", LVCFMT_LEFT, 120);
	m_ctrlList.InsertColumn(4, (LPCTSTR) "工时(/h)", LVCFMT_CENTER, 80);
	m_ctrlList.InsertColumn(5, (LPCTSTR) "周数", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(6, (LPCTSTR)"备注信息", LVCFMT_LEFT, 200);

	

	InitFindCtrl();
	// TODO:  在此添加额外的初始化
	CString strSQL;
	strSQL.Format("select * from register_infor where signer='%s'",theApp.m_strUserName);
	InitDialogCtrl(strSQL);


	//删除数据的权限
	if (!theApp.m_privilege)
	{
		GetDlgItem(IDC_BTRECORD_REFRASH)->EnableWindow(FALSE);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CRecordDlg::InitFindCtrl()
{
	//对话框的查找条件
	m_boolName = 1;//选中
	m_boolMonth = 0;
	m_boolWeek = 0;
	m_boolDay = 0;
	m_month = 0;
	m_week = 0;
	for (int i = 1; i < 13;i++)
	{
		CString str;
		str.Format("%d月", i);
		m_ctrlMonth.AddString(str);
	}
	for (int i = 0; i < 23; i++)
	{
		CString str;
		str.Format("第%d周", i);
		m_ctrlWeek.AddString(str);
	}
	m_ctimeDay = CTime::GetCurrentTime();
	m_strSQL.Format("select * from register_infor where signer='%s'",
		theApp.m_strUserName);
	m_ctrlName.AddString("全体");
	try
	{
		//Connect to the database
		Cperson recordset(&theApp.m_DB);
		CString strSQL;

		strSQL = "select * from person";
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			//if (!recordset.Open(CRecordset::dynaset,strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}

		while (!recordset.IsEOF())
		{
			m_ctrlName.AddString(recordset.m_pname);
			recordset.MoveNext();
		}
		recordset.Close();
		m_strName = theApp.m_strUserName;

		UpdateData(FALSE);
		
	}
	catch (CDBException ex)
	{
		AfxMessageBox(ex.m_strError);
		AfxMessageBox(ex.m_strStateNativeOrigin);
	}
	catch (CMemoryException mEx)
	{
		mEx.ReportError();
		AfxMessageBox("memory exception! ");
	}
	catch (CException *cEx){
		TCHAR szError[100];
		cEx->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);

	}


}
//初始化控件数据
void CRecordDlg::InitDialogCtrl(CString strSQL)
{
	while (m_ctrlList.GetItemCount()>0)
	{
		m_ctrlList.DeleteItem(0);
	}
	try
	{
		//Connect to the database
		CRegisterSet rs(&theApp.m_DB);
		CTime tm;
		tm = CTime::GetCurrentTime();
		
		if (!rs.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			//if (!recordset.Open(CRecordset::dynaset,strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		int times = 0;
		double totalHour = 0;
		while (!rs.IsEOF())
		{
			AddInforToListBox(rs.m_sign_id, rs.m_signer, rs.m_start_time,
				rs.m_end_time, rs.m_working_hours, rs.m_week_number, rs.m_extra_infor);
			times++;
			totalHour += rs.m_working_hours;
			rs.MoveNext();
		}
		m_intTotalTime = times;
		m_strTotalHours.Format("%4.2f h", totalHour);
		rs.Close();
		UpdateData(FALSE);
	}
	catch (CDBException ex)
	{
		AfxMessageBox(ex.m_strError);
		AfxMessageBox(ex.m_strStateNativeOrigin);
	}
	catch (CMemoryException mEx)
	{
		mEx.ReportError();
		AfxMessageBox("memory exception! ");
	}
	catch (CException *cEx){
		TCHAR szError[100];
		cEx->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);

	}

}
//将数据添加到list中
void CRecordDlg::AddInforToListBox(long id, CString signer,
	CTime start, CTime end, double hours,long week, CString extra)
{
	int nIndex = m_ctrlList.GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nIndex;
	lvItem.iSubItem = 0;
	CString temp;
	temp.Format("%d", (int)id);
	lvItem.pszText = (char*)(LPCTSTR)temp;
	//在nIndex 一行插入联系人信息数据
	m_ctrlList.InsertItem(&lvItem);// ID
	m_ctrlList.SetItemText(nIndex, 1, signer);//签到者
	temp = start.Format("%Y-%m-%d %X");
	m_ctrlList.SetItemText(nIndex, 2, temp);//上班签到时间
	temp = end.Format("%Y-%m-%d %X");
	m_ctrlList.SetItemText(nIndex, 3, temp);//下班
	temp.Format("%4.2f", hours);
	m_ctrlList.SetItemText(nIndex, 4, temp);
	temp.Format("%d", week);
	m_ctrlList.SetItemText(nIndex, 5, temp);//周数

	m_ctrlList.SetItemText(nIndex, 6, extra);//备注信息
}

void CRecordDlg::GetStrSql()
{
	CString sql, str;
	if (m_strName == "全体")
		sql.Format("select * from register_infor");
	else
		sql.Format("select * from register_infor where signer='%s'",
		m_strName);
	m_strSQL = sql;
	if (m_ctrlCheckMonth.GetCheck())
	{
		if (m_strName == "全体")
			m_strSQL.Format(sql + " where month=%d", m_month);
		else
			m_strSQL.Format(sql + " AND month=%d", m_month);
	}
	else if (m_ctrlCheckWeek.GetCheck())
	{

		if (m_strName == "全体")
			m_strSQL.Format(sql + " where Week=%s", m_strWeek);
		else
			m_strSQL.Format(sql + " AND Week=%s", m_strWeek);
	}
	else if (m_ctrlCheckDay.GetCheck())
	{
		if (m_strName == "全体")
			m_strSQL.Format(sql + " where Day=%s", m_ctimeDay.Format("%x") );
		else
			m_strSQL.Format(sql + " AND Day=%s", m_ctimeDay.Format("%x"));
	}
}
void CRecordDlg::OnBnClickedBtrecordFind()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString sql;
	if (m_strName == "全体")
		sql.Format("select * from register_infor");
	else
		sql.Format("select * from register_infor where signer='%s'", 
		m_strName);
	while (m_ctrlList.GetItemCount()>0)
	{
		m_ctrlList.DeleteItem(0);
	}
	try
	{
		//Connect to the database
		CRegisterSet rs(&theApp.m_DB);
		CTime tm;
		tm = CTime::GetCurrentTime();

		if (!rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		int times = 0;
		double totalHour = 0;
		while (!rs.IsEOF())
		{
			bool sys = false;
			if (m_ctrlCheckMonth.GetCheck())
			{
				if (rs.m_start_time.GetMonth() == m_month)
				{
					sys = true;
				}
			}
			else if (m_ctrlCheckWeek.GetCheck())
			{

				if (rs.m_week_number == m_week)
				{
					sys = true;
				}
			}
			else if (m_ctrlCheckDay.GetCheck())
			{
				if (rs.m_start_time.GetMonth() == m_ctimeDay.GetMonth()
					&&rs.m_start_time.GetDay()==m_ctimeDay.GetDay())
				{
					sys = true;
				}
			}
			else sys = true;
			if (sys)//当前记录需要显示
			{
				AddInforToListBox(rs.m_sign_id, rs.m_signer, rs.m_start_time,
					rs.m_end_time, rs.m_working_hours, rs.m_week_number, rs.m_extra_infor);
				times++;
				totalHour += rs.m_working_hours;
			}
			rs.MoveNext();
		}
		m_intTotalTime = times;
		m_strTotalHours.Format("%4.2f h", totalHour);
		GetStrSql();
		rs.Close();
		UpdateData(FALSE);
	}
	catch (CDBException ex)
	{
		AfxMessageBox(ex.m_strError);
		AfxMessageBox(ex.m_strStateNativeOrigin);
	}
	catch (CMemoryException mEx)
	{
		mEx.ReportError();
		AfxMessageBox("memory exception! ");
	}
	catch (CException *cEx){
		TCHAR szError[100];
		cEx->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);

	}

}


void CRecordDlg::OnBnClickedBtrecordExport()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_ctrlList.GetItemCount() == 0)
	{
		MessageBoxA("当前列表上没有数据可以导出,请查找数据！", "导出错误", MB_ICONERROR | MB_OK);
		return;
	}

	_Application app;
	_Workbook book;
	Workbooks books;
	_Worksheet sheet;
	Worksheets sheets;
	Range range;
	Range cols;
	//Font font;
	COleVariant covOptional((long)
		DISP_E_PARAMNOTFOUND, VT_ERROR);
	if (!app.CreateDispatch(_T("Excel.Application")))
	{
		MessageBoxA("程序无法创建Excel应用,请自行安装Excel驱动程序！", "导出错误",
			MB_ICONERROR | MB_OK);
		return;
	}
	books = app.GetWorkbooks();
	book = books.Add(covOptional);
	sheets = book.GetWorksheets();
	sheet = sheets.GetItem(COleVariant((short)1));

	//获得坐标为（A，1）和（A，1）的两个单元格
	range = sheet.GetRange(COleVariant(_T("A1")), COleVariant(_T("A1")));
	//设置单元格类容为Hello Excel
	range.SetValue(COleVariant(m_strSQL));
	//选择整列，并设置宽度为自适应
	//cols =range.GetColumns();
	//cols = range.GetEntireColumn();
	//cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("A2")), COleVariant(_T("A2")));
	range.SetValue(COleVariant(_T("信息ID")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("B2")), COleVariant(_T("B2")));
	range.SetValue(COleVariant(_T("签到人")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("C2")), COleVariant(_T("C2")));
	range.SetValue(COleVariant(_T("上班签到时间")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("D2")), COleVariant(_T("D2")));
	range.SetValue(COleVariant(_T("下班签到时间")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("E2")), COleVariant(_T("E2")));
	range.SetValue(COleVariant(_T("工时")));

	range = sheet.GetRange(COleVariant(_T("F2")), COleVariant(_T("F2")));
	range.SetValue(COleVariant(_T("周数")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("G2")), COleVariant(_T("G2")));
	range.SetValue(COleVariant(_T("备注")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	
	int i = 0, size = m_ctrlList.GetItemCount();
	while (i < size)
	{
		//取得id
		//获得坐标为（A，i+3）和（A，i+3）的两个单元格
		CString index;
		index.Format("A%d", i + 3);
		range = sheet.GetRange(COleVariant(index), COleVariant(index));
		//设置单元格类容为
		range.SetValue(COleVariant(m_ctrlList.GetItemText(i, 0)));
		//选择整列，并设置宽度为自适应
		cols = range.GetEntireColumn();
		cols.AutoFit();

		index.Format("B%d", i + 3);
		range = sheet.GetRange(COleVariant(index), COleVariant(index));
		range.SetValue(COleVariant(m_ctrlList.GetItemText(i, 1) ));
		cols = range.GetEntireColumn();
		cols.AutoFit();
		index.Format("C%d", i + 3);
		range = sheet.GetRange(COleVariant(index), COleVariant(index));
		range.SetValue(COleVariant(m_ctrlList.GetItemText(i, 2)));
		cols = range.GetEntireColumn();
		cols.AutoFit();

		index.Format("D%d", i + 3);
		range = sheet.GetRange(COleVariant(index), COleVariant(index));
		range.SetValue(COleVariant(m_ctrlList.GetItemText(i, 3)));
		cols = range.GetEntireColumn();
		cols.AutoFit();

		index.Format("E%d", i + 3);
		range = sheet.GetRange(COleVariant(index), COleVariant(index));
		range.SetValue(COleVariant(m_ctrlList.GetItemText(i, 4)));
		cols = range.GetEntireColumn();
		cols.AutoFit();

		index.Format("F%d", i + 3);
		range = sheet.GetRange(COleVariant(index), COleVariant(index));
		range.SetValue(COleVariant(m_ctrlList.GetItemText(i, 5)));
		cols = range.GetEntireColumn();
		cols.AutoFit();

		index.Format("G%d", i + 3);
		range = sheet.GetRange(COleVariant(index), COleVariant(index));
		range.SetValue(COleVariant(m_ctrlList.GetItemText(i, 6)));
		cols = range.GetEntireColumn();
		cols.AutoFit();

		i++;
	}
	//显示Excel表
	app.SetVisible(TRUE);
	app.SetUserControl(TRUE);
	//book.Save();
	//app.Quit();
	//释放对象 
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	CString str;
	str.Format("成功导出 %d 条数据记录！", size);
	MessageBoxA(str, "导出成功",
		MB_ICONEXCLAMATION | MB_OK);
}


void CRecordDlg::OnBnClickedBtrecordRefrash()
{
	// TODO:  在此添加控件通知处理程序代码
	int i = 0, size = m_ctrlList.GetItemCount();
	if (size == 0)
	{
		MessageBoxA("当前列表没有数据！", "删除错误", MB_ICONQUESTION | MB_OK);
		return;
	}
	CString str;
	str.Format("您将要删除 %d 条数据记录，按\"确定\"按钮将执行操作!", size);
	if (MessageBoxA(str, "请确定",
		MB_ICONQUESTION | MB_YESNO) == IDNO) return;

	try{
		//打开数据库的连接，并捕获异常
		i = 0;
		while (i < size)
		{
			//取得id
			int id = atoi(m_ctrlList.GetItemText(i, 0));
			CRegisterSet rs(&theApp.m_DB);
			CString drop;
			drop.Format("delete from register_infor where sign_id = %d", id);
			theApp.m_DB.ExecuteSQL(drop);
			i++;
		}
		OnBnClickedBtrecordFind();
		if (m_ctrlList.GetItemCount() == 0)
		{
			MessageBoxA("成功删除列表数据！", "删除成功", 
				MB_ICONQUESTION | MB_OK);
		}
		else MessageBoxA("部分数据发生错误，请检查数据库！", "出错",
			MB_ICONERROR | MB_OK);
	}
	catch (CDBException ex)
	{
		AfxMessageBox(ex.m_strError);
		AfxMessageBox(ex.m_strStateNativeOrigin);
	}
	catch (CMemoryException mEx)
	{
		mEx.ReportError();
		AfxMessageBox("memory exception! ");
	}
	catch (CException *cEx){
		TCHAR szError[100];
		cEx->GetErrorMessage(szError, 100);
		AfxMessageBox(szError);
	}
}


//右键菜单的编辑功能
void CRecordDlg::RMEdit()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("请选择要修改的信息！", "请确定",
			MB_ICONQUESTION | MB_OK);
		return;
	}
	CString signer = m_ctrlList.GetItemText(iItem, 1);
	int  id = atoi(m_ctrlList.GetItemText(iItem, 0));

	try{
		CRegisterSet rs(&theApp.m_DB);
		CString sql;
		sql.Format("Select * from register_infor where signer = '%s' AND sign_id =%d", signer, id);
		rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
		if (!rs.IsEOF())
		{
			CEditRecordDlg dlg;
			CString str;
			str.Format("%d年%d月", rs.m_start_time.GetYear(), rs.m_start_time.GetMonth());
			dlg.m_strName = rs.m_signer;
			dlg.m_strYearMonth = str;	
			dlg.m_intStartDay = rs.m_start_time.GetDay();
			dlg.m_intStartHour = rs.m_start_time.GetHour();
			dlg.m_intStartMin = rs.m_start_time.GetMinute();

			str.Format("%d年%d月", rs.m_end_time.GetYear(), rs.m_end_time.GetMonth());
			dlg.m_strEndYM = str;
			dlg.m_intEndDay = rs.m_end_time.GetDay();
			dlg.m_intEndHour = rs.m_end_time.GetHour();
			dlg.m_intEndMin = rs.m_end_time.GetMinute();
			dlg.m_intWeek = rs.m_week_number;
			str.Format("%4.2fh", rs.m_working_hours);
			dlg.m_strWorkHour = str;
			dlg.m_strExtraInfor = rs.m_extra_infor;

			if (dlg.DoModal() == IDOK)
			{
				
				CString update, st,et;
				double hours = dlg.m_intEndHour - dlg.m_intStartHour;
				if (dlg.m_intEndMin < dlg.m_intStartMin)
				{
					hours -= dlg.m_intStartMin - dlg.m_intEndMin;
				}
				else hours += ((double)(dlg.m_intEndMin - dlg.m_intStartMin))/(double)60 ;

				st.Format("%d-%d-%d %d:%d:00", rs.m_start_time.GetYear(), rs.m_start_time.GetMonth()
					,dlg.m_intStartDay,dlg.m_intStartHour,dlg.m_intStartMin);
				et.Format("%d-%d-%d %d:%d:00", rs.m_start_time.GetYear(), rs.m_start_time.GetMonth()
					, dlg.m_intEndDay, dlg.m_intEndHour, dlg.m_intEndMin);
				update.Format("update register_infor set start_time ='%s',end_time='%s',"
					"working_hours=%4.2f,week_number=%d,extra_infor='%s' where sign_id =%d",
					st, et,hours,dlg.m_intWeek,dlg.m_strExtraInfor, id);
				theApp.m_DB.ExecuteSQL(update);
				
				OnBnClickedBtrecordFind();//更新数据列表
				MessageBoxA("成功修改信息！", "修改成功",
					MB_ICONEXCLAMATION | MB_OK);
			}
			rs.Close();
			return;//正常是在这里结束程序的
		}
		rs.Close();
		//程序走到这里说明在上班签到表里 没有找到要修改的信息
		MessageBoxA("未找到选择的信息！请联系管理员！", "数据错误",
			MB_ICONERROR | MB_OK);
	}
	catch (CDBException ex){
		AfxMessageBox(ex.m_strError);
		AfxMessageBox(ex.m_strStateNativeOrigin);
	}
}
//右键菜单的删除功能
void CRecordDlg::RMDelete()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("请选择要删除的信息！", "请确定",
			MB_ICONQUESTION | MB_OK);
		return;
	}
	CString signer = m_ctrlList.GetItemText(iItem, 1);
	int  id = atoi(m_ctrlList.GetItemText(iItem, 0));
	try{
		CRegisterSet rs(&theApp.m_DB);
		CString sql;
		sql.Format("Select * from register_infor where signer = '%s' AND sign_id =%d", signer, id);
		rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
		if (!rs.IsEOF())
		{
			CString str, strLock;
			
			str.Format("您将要删除:\"%d,%s\n%s,%s\n %4.2fh,第%d周\"，\n点击\"确定\"按钮,该信息将被删除？",
				id, signer, rs.m_start_time.Format("%Y-%m-%d %X"),
				rs.m_end_time.Format("%Y-%m-%d %X"),
				rs.m_working_hours,rs.m_week_number);
			if (MessageBoxA(str, "请确定",
				MB_ICONQUESTION | MB_YESNO) == IDNO) return;
			//在register_infor 表删除记录
			CString drop;
			drop.Format("delete from register_infor where sign_id = %d", id);
			theApp.m_DB.ExecuteSQL(drop);
			OnBnClickedBtrecordFind();//更新数据列表
			MessageBoxA("删除信息成功！", "成功删除",
				MB_ICONWARNING | MB_OK);

		}
		//程序走到这里说明在上班签到表里 没有找到要修改的信息
		else MessageBoxA("未找到选择的信息,请检查数据库！", "数据错误",
			MB_ICONERROR | MB_OK);
		rs.Close();
	}
	catch (CDBException ex){
		AfxMessageBox(ex.m_strError);
		AfxMessageBox(ex.m_strStateNativeOrigin);
	}
}
void CRecordDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	if (theApp.m_privilege)//修妖权限支持
	{
		CMenu menuTray;
		CPoint point;
		int id;
		GetCursorPos(&point);
		//如果点击弹出菜单的时候,菜单失去焦点让菜单自动关闭
		SetForegroundWindow();

		menuTray.LoadMenu(IDR_MENU1);
		id = menuTray.GetSubMenu(0)->TrackPopupMenu(TPM_RETURNCMD |
			TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		switch (id)
		{
		case ID_RM_EDIT: RMEdit(); break;
		case ID_RM_DELETE: RMDelete(); break;
		default:
			break;
		}
	}

}

void CRecordDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlName.GetCurSel();//当前选中的行。
	m_ctrlName.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlName.GetLBText(iPos, m_strName);
}


void CRecordDlg::OnCbnSelchangeCombo2()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlMonth.GetCurSel();//当前选中的行。
	m_ctrlMonth.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlMonth.GetLBText(iPos, m_strMonth);
	m_month = iPos + 1;//box从0开始，月份从1 开始
}


void CRecordDlg::OnCbnSelchangeCombo3()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlWeek.GetCurSel();//当前选中的行。
	m_ctrlWeek.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlWeek.GetLBText(iPos, m_strWeek);
	m_week = iPos;//box从0开始，周数也是从0开始
}


void CRecordDlg::OnBnClickedCheck2()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	/*void SetCheck(int nCheck);
       设置按钮的选择状态。参数nCheck为0表示未选中状态，
	   1表示选中状态，2表示不确定状态（仅用于复选框）。
       int GetCheck( ) const;*/
	if (m_ctrlCheckMonth.GetCheck())//禁用周和日期 选项框
	{
		m_ctrlCheckWeek.EnableWindow(FALSE);
		m_ctrlWeek.EnableWindow(FALSE);
		m_ctrlCheckDay.EnableWindow(FALSE);
		
	}
	else
	{
		m_ctrlCheckWeek.EnableWindow(TRUE);
		m_ctrlWeek.EnableWindow(TRUE);
		m_ctrlCheckDay.EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}


void CRecordDlg::OnBnClickedCheck3()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_ctrlCheckWeek.GetCheck())//禁用月和日期 选项框
	{
		m_ctrlCheckMonth.EnableWindow(FALSE);
		m_ctrlMonth.EnableWindow(FALSE);
		m_ctrlCheckDay.EnableWindow(FALSE);

	}
	else
	{
		m_ctrlCheckMonth.EnableWindow(TRUE);
		m_ctrlMonth.EnableWindow(TRUE);
		m_ctrlCheckDay.EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}


void CRecordDlg::OnBnClickedCheck4()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_ctrlCheckDay.GetCheck())//禁用月和日期 选项框
	{
		m_ctrlCheckWeek.EnableWindow(FALSE);
		m_ctrlWeek.EnableWindow(FALSE);
		m_ctrlCheckMonth.EnableWindow(FALSE);
		m_ctrlMonth.EnableWindow(FALSE);
	}
	else
	{
		m_ctrlCheckWeek.EnableWindow(TRUE);
		m_ctrlWeek.EnableWindow(TRUE);
		m_ctrlCheckMonth.EnableWindow(TRUE);
		m_ctrlMonth.EnableWindow(TRUE);
	}
	UpdateData(FALSE);
}
