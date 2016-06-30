// SignDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "SignDlg.h"
#include "afxdialogex.h"
#include"start_work.h"
#include"register_infor.h"
#include"EditSignDlg.h"

// CSignDlg 对话框

IMPLEMENT_DYNAMIC(CSignDlg, CDialogEx)

CSignDlg::CSignDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSignDlg::IDD, pParent)
{

}

CSignDlg::~CSignDlg()
{
}

void CSignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CSignDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSignDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSignDlg::OnBnClickedButton2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CSignDlg::OnNMRClickList1)
END_MESSAGE_MAP()


// CSignDlg 消息处理程序

//上班签到按钮
void CSignDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码

	try
	{
		//Connect to the database
		CString strSQL;
		CTime tm;
		tm = CTime::GetCurrentTime();
		CSignSet ss(&theApp.m_DB);
		strSQL.Format("select * from start_work where signer='%s' AND is_lock=0",theApp.m_strUserName);
		if (!ss.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			//if (!recordset.Open(CRecordset::dynaset,strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		if (!ss.IsEOF())
		{
			//可以在这里加上是否今日的记录 检查

			MessageBox("你还有上班签到记录没有签下班，请先签下班！\n如果无法解决，请找管理员！", "警告", MB_OK);
		}
		else//产生上班签到信息
		{
			CRecordset rs;
			rs.m_pDatabase = &theApp.m_DB;
			CString sql = "Select max(start_id) from start_work";
			//获取 最大ID值
			rs.Open(CRecordset::dynaset, sql);
			int id=0;
			if (!rs.IsEOF())
			{
				CDBVariant var;
				//获ID字段
				rs.GetFieldValue((short)0, var, SQL_C_SLONG);
				if (var.m_dwType != DBVT_NULL)
				{
					id = var.m_iVal;
				}
				var.Clear();
			}
			if (id < 1)id = 1;
			rs.Close();

			CString ti,insert;
			ti = tm.Format("%Y-%m-%d %X");
			insert.Format("insert into start_work(start_id,signer,start_time)"
				" values(%d,'%s','%s')",id+1,theApp.m_strUserName,ti);
			theApp.m_DB.ExecuteSQL(insert);
			SignSucceed(true);
		}
		ss.Close();
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

//下班签到按钮
void CSignDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	try
	{
		//Connect to the database
		CString strSQL;
		CTime tm;
		tm = CTime::GetCurrentTime();
		CSignSet ss(&theApp.m_DB);
		strSQL.Format("select * from start_work where signer='%s' AND is_lock=0", theApp.m_strUserName);
		if (!ss.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			//if (!recordset.Open(CRecordset::dynaset,strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		if (!ss.IsEOF())//找到上班签到信息，产生当次值班签到记录
		{
			CRecordset rs;
			rs.m_pDatabase = &theApp.m_DB;
			CString sql = "Select max(sign_id) from register_infor";
			//获取 最大ID值
			rs.Open(CRecordset::dynaset, sql);
			int id = 0;
			if (!rs.IsEOF())
			{
				CDBVariant var;
				//获ID字段
				rs.GetFieldValue((short)0, var, SQL_C_SLONG);
				if (var.m_dwType != DBVT_NULL)
				{
					id = var.m_iVal;
				}
				var.Clear();
			}
			if (id < 1)id = 1;
			rs.Close();

			//在register_infor 表插入数据
			CString startTime,ti, insert;
			if (tm.GetDay() != ss.m_start_time.GetDay())
			{
				MessageBox("找到的数据错误！请找管理员处理！", "无法签到", MB_OK);
				ss.Close();
				return;
			}
			double hours = tm.GetHour() - ss.m_start_time.GetHour();
			if (tm.GetMinute() < ss.m_start_time.GetMinute())
			{
				hours -= ( (double)(ss.m_start_time.GetMinute() - tm.GetMinute()) ) / (double)60;
			}
			else hours += ((double)(tm.GetMinute() - ss.m_start_time.GetMinute())) /(double) 60;
			startTime = ss.m_start_time.Format("%Y-%m-%d %X");
			ti = tm.Format("%Y-%m-%d %X");

			insert.Format("insert into register_infor(sign_id,signer,start_time"
				",end_time,working_hours,week_number)"
				" values(%d,'%s','%s','%s',%4.2f,%d)", id + 1,
				theApp.m_strUserName, startTime,ti, hours,theApp.m_nowWeek);
			theApp.m_DB.ExecuteSQL(insert);

			//在start_work 表删除上班记录
			CString drop;
			drop.Format("delete from start_work where start_id = %d", ss.m_start_id);
			theApp.m_DB.ExecuteSQL(drop);

			SignSucceed(true);//输出成功信息
		}
		else MessageBox("你还没有上班签到，请先上班签到！", "警告", MB_OK);
		ss.Close();
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


BOOL CSignDlg::OnInitDialog()
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
	m_ctrlList.InsertColumn(4, (LPCTSTR) "工时", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(5, (LPCTSTR) "信息锁定", LVCFMT_CENTER, 80);
	m_ctrlList.InsertColumn(6, (LPCTSTR)"备注信息", LVCFMT_LEFT, 200);
	
	// TODO:  在此添加额外的初始化
	InitDialogCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//初始化控件数据
void CSignDlg::InitDialogCtrl()
{
	while (m_ctrlList.GetItemCount()>0)
	{
		m_ctrlList.DeleteItem(0);
	}
	try
	{
		//Connect to the database
		//将register_infor 表的今天的数据显示
		CRegisterSet rs(&theApp.m_DB);
		CString strSQL;
		CTime tm;
		tm = CTime::GetCurrentTime();
		strSQL = "select * from register_infor";
		if (!rs.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			//if (!recordset.Open(CRecordset::dynaset,strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}

		while (!rs.IsEOF())
		{
			if (rs.m_start_time.GetMonth()==tm.GetMonth()&&
				rs.m_start_time.GetDay()==tm.GetDay())//将今天签到的信息显示
				AddInforToListBox(rs.m_sign_id,rs.m_signer,rs.m_start_time,
				rs.m_end_time,rs.m_working_hours,FALSE,rs.m_extra_infor);
			rs.MoveNext();
		}

		rs.Close();

		//将start_work 表的数据全部显示
		CSignSet ss(&theApp.m_DB);
		strSQL = "select * from start_work";
		if (!ss.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			//if (!recordset.Open(CRecordset::dynaset,strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		while (!ss.IsEOF())
		{
			AddInforToListBox(ss.m_start_id, ss.m_signer, ss.m_start_time,
				ss.m_start_time, -1,ss.m_is_lock, " ");
			ss.MoveNext();
		}
		ss.Close();
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
void CSignDlg::AddInforToListBox(long id, CString signer,
	CTime start, CTime end, double hours, BOOL lock, CString extra)
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
	if ((int)hours == -1 && !lock)
	{
		temp = "仍在努力工作中~~~";
		hours = 0;
	}
	else if ((int)hours == -1 && lock)
	{
		temp = "";
		hours = 0;
	}
	m_ctrlList.SetItemText(nIndex, 3, temp);//下班

	temp.Format("%4.2f", hours);
	m_ctrlList.SetItemText(nIndex, 4, temp);
	if (lock)temp = "是";
	else temp = " ";
	m_ctrlList.SetItemText(nIndex, 5, temp);//锁定标记
	m_ctrlList.SetItemText(nIndex, 6, extra);//发件日期
}

//sys=true显示上班签到成功的信息，false 显示下班签到成功的信息
void CSignDlg::SignSucceed(bool sys)
{
	CString str, ti; //获取系统时间
	CString welcome;
	CTime tm;
	tm = CTime::GetCurrentTime();
	ti.Format("%d：%d分签到成功~~~",tm.GetHour(),tm.GetMinute());

	if (sys)//上班签到
	{
		if ((tm.GetHour() == 7 || tm.GetHour() == 13) && tm.GetMinute() < 56)
			welcome = "\n今天提前到班哟，继续努力~~~";
		if ((tm.GetHour() == 8 || tm.GetHour() == 14) && tm.GetMinute()>5)
			welcome = "\n今天迟到了哟，下次来早一点呀~~~";
	}
	else//下班签到
	{
		welcome = "\n工作辛苦啦，拜拜~~~";
	}
	srand((unsigned)time(NULL));
	int i = rand() % 10;
	if (i % 2 == 0)welcome = "";
	InitDialogCtrl();//刷新控件列表的数据

	MessageBox(ti+welcome, "签到成功", MB_OK);
}

//右键菜单的解锁锁定功能
//lock 等于true 说明下面要锁定，否则为解锁
void CSignDlg::LockAddUnLock(bool lock)
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("请选择要操作的信息！", "请确定",
			MB_ICONQUESTION | MB_OK);
		return;
	}
	CString signer = m_ctrlList.GetItemText(iItem, 1);
	int  id = atoi(m_ctrlList.GetItemText(iItem, 0));

	try{
		CSignSet rs(&theApp.m_DB);
		CString sql;
		sql.Format("Select * from start_work where signer = '%s' AND start_id =%d", signer, id);
		rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
		if (!rs.IsEOF())
		{
			if (rs.m_is_lock == TRUE&&lock==false)//
			{
				if (MessageBoxA("点击\"确定\"按钮,该信息将解锁？", "请确定",
					MB_ICONQUESTION | MB_YESNO) == IDNO)return;

				CString update;
				update.Format("update start_work set is_lock =%d "
					"where start_id =%d",
					0,id);
				theApp.m_DB.ExecuteSQL(update);
				m_ctrlList.SetItemText(iItem, 5, "");
				MessageBoxA("成功解锁该签到信息！", "解锁成功",
					MB_ICONINFORMATION | MB_OK);
			}
			else if (rs.m_is_lock == FALSE&&lock == true)
			{
				if (MessageBoxA("点击\"确定\"按钮,该信息将锁定？", "请确定",
					MB_ICONQUESTION | MB_YESNO) == IDNO)return;

				CString update;
				update.Format("update start_work set is_lock =%d "
					"where start_id =%d",
					1, id);
				theApp.m_DB.ExecuteSQL(update);
				m_ctrlList.SetItemText(iItem, 5, "是");
				MessageBoxA("成功锁定该签到信息！", "锁定成功",
					MB_ICONINFORMATION | MB_OK);
			}
			UpdateData(FALSE);
			rs.Close();
			return;
		}
		//程序走到这里说明在上班签到表里 没有找到要修改的信息
		MessageBoxA("未找到选择的信息,只能修改未签下班的信息！", "请确定",
			MB_ICONQUESTION | MB_OK);
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
void CSignDlg::RMEdit()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("请选择要修改的信息！", "请确定",
			MB_ICONQUESTION | MB_OK);
		return;
	}
	CString signer=m_ctrlList.GetItemText(iItem, 1);
	int  id = atoi(m_ctrlList.GetItemText(iItem, 0));
	
	try{
		CSignSet rs(&theApp.m_DB);
		CString sql;
		sql.Format("Select * from start_work where signer = '%s' AND start_id =%d",signer,id);
		rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
		if (!rs.IsEOF())
		{
			CTime tm;
			tm = CTime::GetCurrentTime();
			CEditSignDlg dlg;
			CString str;
			str.Format("%d年%d月", rs.m_start_time.GetYear(), rs.m_start_time.GetMonth());
			dlg.m_strSigner =  rs.m_signer;
			dlg.m_strYearMonth = str;
			dlg.m_strStartYM = str;
			dlg.m_intEndDay = rs.m_start_time.GetDay();
			dlg.m_intStartDay = rs.m_start_time.GetDay();
			dlg.m_intStartHour = rs.m_start_time.GetHour();
		    dlg.m_intStartMin = rs.m_start_time.GetMinute();

			rs.Close();
			if (dlg.DoModal() == IDOK)
			{
				int startDay, startMin, startHour, endDay, endHour, endMin;
				startDay=dlg.m_intStartDay;
				startHour=dlg.m_intStartHour;
				startMin=dlg.m_intStartMin;
				endDay=dlg.m_intEndDay;
				endHour=dlg.m_intEndHour;
				endMin=dlg.m_intEndMin;
				
				//构造开始时间
				CTime st(rs.m_start_time.GetYear(), rs.m_start_time.GetMonth()
					, startDay, startHour,startMin,0);
				//构造结束时间 endDay==0时构造时间将崩溃
				CTime et(rs.m_start_time.GetYear(), rs.m_start_time.GetMonth()
					, endDay, endHour, endMin, 0);
				CRecordset crs;
				crs.m_pDatabase = &theApp.m_DB;
				CString sql1 = "Select max(sign_id) from register_infor";
				//获取 最大ID值
				crs.Open(CRecordset::dynaset, sql1);
				int idl = 0;
				if (!crs.IsEOF())
				{
					CDBVariant var;
					//获ID字段
					crs.GetFieldValue((short)0, var, SQL_C_SLONG);
					if (var.m_dwType != DBVT_NULL)
					{
						idl = var.m_iVal;
					}
					var.Clear();
				}
				if (idl < 1)idl = 10;
				crs.Close();

				//在register_infor 表插入数据
				CString startTime, ti, insert;
				double hours = et.GetHour() - st.GetHour();
				if (et.GetMinute() < st.GetMinute())
				{
					hours -= ((double)(st.GetMinute() - et.GetMinute())) / (double)60;
				}
				else hours += ((double)(et.GetMinute() - st.GetMinute())) / (double)60;
				startTime = st.Format("%Y - %m - %d %X");
				ti = et.Format("%Y-%m-%d %X");

				insert.Format("insert into register_infor(sign_id,signer,start_time"
					",end_time,working_hours,week_number)"
					" values(%d,'%s','%s','%s',%4.2f,%d)", idl + 1,
					signer, startTime, ti, hours, theApp.m_nowWeek);
				theApp.m_DB.ExecuteSQL(insert);

				//在start_work 表删除上班记录
				CString drop;
				drop.Format("delete from start_work where start_id = %d", id);
				theApp.m_DB.ExecuteSQL(drop);
				MessageBoxA("成功修改该签到信息！", "修改成功",
					MB_ICONINFORMATION | MB_OK);
				InitDialogCtrl();//刷新控件数据
			}
			return;//正常是在这里结束程序的
		}

		//程序走到这里说明在上班签到表里 没有找到要修改的信息
		MessageBoxA("未找到选择的信息,只能修改未签下班的信息！", "请确定",
				MB_ICONQUESTION | MB_OK);
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
//右键菜单的删除功能
void CSignDlg::RMDelete()
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
		CSignSet rs(&theApp.m_DB);
		CString sql;
		sql.Format("Select * from start_work where signer = '%s' AND start_id =%d", signer, id);
		rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
		if (!rs.IsEOF())
		{
			CString str,strLock;
			if (rs.m_is_lock)strLock = "锁定";
			else strLock = "未锁定";
			str.Format("您将要删除:\"%d,%s,%s,%s\"，\n点击\"确定\"按钮,该信息将被删除？",
				id,signer,rs.m_start_time.Format("%Y-%m-%d %X"),strLock);
			if (MessageBoxA(str, "请确定",
				MB_ICONQUESTION | MB_YESNO) == IDNO) return;
			//在start_work 表删除上班记录
			CString drop;
			drop.Format("delete from start_work where start_id = %d", id);
			theApp.m_DB.ExecuteSQL(drop);
			InitDialogCtrl();
			MessageBoxA("删除信息成功！", "成功删除",
				MB_ICONINFORMATION | MB_OK);		
		}
		//程序走到这里说明在上班签到表里 没有找到要修改的信息
		else MessageBoxA("未找到选择的信息,当前窗口只能删除未签下班的信息！", "请确定",
			MB_ICONQUESTION | MB_OK);
		rs.Close();
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
void CSignDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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

		menuTray.LoadMenu(IDR_MENU4);
		id = menuTray.GetSubMenu(0)->TrackPopupMenu(TPM_RETURNCMD |
			TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		switch (id)
		{
		case ID_SIGN_UNLOCK: LockAddUnLock(false); break;
		case ID_SIGN_LOCK: LockAddUnLock(true); break;
		case ID_SIGN_EDIT: RMEdit(); break;
		case ID_SIGN_DELETE: RMDelete(); break;

		default:
			break;
		}
	}
	
}
