// AdminDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "AdminDlg.h"
#include "afxdialogex.h"
#include"person.h"
#include"DeletePersonDlg.h"
#include"AddUserDlg.h"
#include"excel9.h"

// CAdminDlg 对话框

IMPLEMENT_DYNAMIC(CAdminDlg, CDialogEx)

CAdminDlg::CAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdminDlg::IDD, pParent)
{

}

CAdminDlg::~CAdminDlg()
{
}

void CAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CAdminDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTA_EXPORT, &CAdminDlg::OnBnClickedBtaExport)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CAdminDlg::OnNMRClickList1)
END_MESSAGE_MAP()


// CAdminDlg 消息处理程序


void CAdminDlg::OnBnClickedBtaExport()
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
	range = sheet.GetRange(COleVariant(_T("C1")), COleVariant(_T("C1")));
	//设置单元格类容为Hello Excel
	range.SetValue(COleVariant("通讯录"));
	//选择整列，并设置宽度为自适应
	//cols =range.GetColumns();
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("A2")), COleVariant(_T("A2")));
	range.SetValue(COleVariant(_T("姓名")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("B2")), COleVariant(_T("B2")));
	range.SetValue(COleVariant(_T("电话")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("C2")), COleVariant(_T("C2")));
	range.SetValue(COleVariant(_T("性别")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("D2")), COleVariant(_T("D2")));
	range.SetValue(COleVariant(_T("学院")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("E2")), COleVariant(_T("E2")));
	range.SetValue(COleVariant(_T("专业")));

	range = sheet.GetRange(COleVariant(_T("F2")), COleVariant(_T("F2")));
	range.SetValue(COleVariant(_T("年级")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("G2")), COleVariant(_T("G2")));
	range.SetValue(COleVariant(_T("部门")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("H2")), COleVariant(_T("H2")));
	range.SetValue(COleVariant(_T("备注")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("I2")), COleVariant(_T("I2")));
	range.SetValue(COleVariant(_T("简介")));
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
		range.SetValue(COleVariant(m_ctrlList.GetItemText(i, 1)));
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

		index.Format("H%d", i + 3);
		range = sheet.GetRange(COleVariant(index), COleVariant(index));
		range.SetValue(COleVariant(m_ctrlList.GetItemText(i, 7)));
		cols = range.GetEntireColumn();
		cols.AutoFit();

		index.Format("I%d", i + 3);
		range = sheet.GetRange(COleVariant(index), COleVariant(index));
		range.SetValue(COleVariant(m_ctrlList.GetItemText(i, 8)));
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



//初始化控件数据
void CAdminDlg::InitDialogCtrl()
{
	while (m_ctrlList.GetItemCount()>0)
	{
		m_ctrlList.DeleteItem(0);
	}
	try
	{
		//Connect to the database
		Cperson rs(&theApp.m_DB);
		CString strSQL;
		strSQL.Format("select * from person");
		if (!rs.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			//if (!recordset.Open(CRecordset::dynaset,strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		while (!rs.IsEOF())
		{
			AddInforToListBox(rs.m_pname,rs.m_telephone,rs.m_sex,rs.m_academy
				,rs.m_major, rs.m_id, rs.m_department,rs.m_post, rs.m_introduction);
			rs.MoveNext();
		}
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
void CAdminDlg::AddInforToListBox(CString name,
	CString telephone, BOOL sex, CString academy,CString major,CString grade,
	CString depart,CString extra,CString introduction)
{
	CString temp;
	int nIndex = m_ctrlList.GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nIndex;
	lvItem.iSubItem = 0;
	lvItem.pszText = (char*)(LPCTSTR)name;
	//在nIndex 一行插入联系人信息数据
	m_ctrlList.InsertItem(&lvItem);// ID
	m_ctrlList.SetItemText(nIndex, 1, telephone);
	if(sex)temp ="男";
	else temp = "女";
	m_ctrlList.SetItemText(nIndex, 2, temp);
	m_ctrlList.SetItemText(nIndex, 3, academy);
	m_ctrlList.SetItemText(nIndex, 4, major);
	m_ctrlList.SetItemText(nIndex, 5, grade);
	m_ctrlList.SetItemText(nIndex, 6, depart);
	m_ctrlList.SetItemText(nIndex, 7, extra);
	m_ctrlList.SetItemText(nIndex, 8, introduction);

}

//右键菜单的添加功能
void CAdminDlg::RMAdd()
{
	CAddUserDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		try{
			int sex = 0;
			if (dlg.m_strSex == "男")sex = 1;
			else sex = 0;

			CString insert;
			insert.Format("insert into person(pname,id,sex,academy,major,"
				"telephone,join_date,post,introduction,department,passwd,privilege) "
				"values('%s','%s',%d,'%s','%s','%s','%s','%s','%s','%s','%s',%s)",
				dlg.m_strName,dlg.m_strID,sex,dlg.m_strAcademy,
				dlg.m_strMajor,dlg.m_strPhone,dlg.m_strJoinDate,dlg.m_strPost,
				dlg.m_strIntroduction,dlg.m_strDepart,dlg.m_strPasswd,dlg.m_strPrivilige);
			theApp.m_DB.ExecuteSQL(insert);

			InitDialogCtrl();//更新数据列表
			MessageBoxA("成功添加人员信息,下次启动系统即可使用该账号登录！", "添加成功",
				MB_ICONEXCLAMATION | MB_OK);
			return;
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
		MessageBox("添加信息失败！可能填写的数据格式出错，请重新填写！", "添加失败", MB_OK);
	}

}
//右键菜单的编辑功能
void CAdminDlg::RMEdit()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("请选择要修改的信息！", "请确定",
			MB_ICONQUESTION | MB_OK);
		return;
	}
	CString name = m_ctrlList.GetItemText(iItem, 0);

	try{
		Cperson rs(&theApp.m_DB);
		CString sql;
		sql.Format("Select * from person where pname = '%s'", name);
		rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
		if (!rs.IsEOF())
		{
			CAddUserDlg dlg;
			dlg.is_edit = 1;

			dlg.m_strName = rs.m_pname;
			dlg.m_strAcademy = rs.m_academy;
			dlg.m_strDepart = rs.m_department;
			dlg.m_strID = rs.m_id;
			dlg.m_strIntroduction = rs.m_introduction;
			dlg.m_strJoinDate = rs.m_join_date.Format("%Y-%m-%d");
			dlg.m_strMajor = rs.m_major;
			dlg.m_strPasswd = rs.m_passwd;
			dlg.m_strPhone = rs.m_telephone;
			dlg.m_strPost = rs.m_post;
			dlg.m_strPrivilige.Format("%d",rs.m_privilege);
			if (rs.m_sex == 1)
				dlg.m_strSex = "男";
			else dlg.m_strSex = "女";

			if (dlg.DoModal() == IDOK)
			{
				int sex = 0;
				if (dlg.m_strSex == "男")sex = 1;
				else sex = 0;

				CString update;
				update.Format("update  person set id='%s',sex=%d,academy='%s',major='%s',"
					"telephone='%s',join_date='%s',post='%s',introduction='%s',"
					"department='%s',passwd='%s',privilege=%s where pname='%s'"
					,
					dlg.m_strID, sex, dlg.m_strAcademy,
					dlg.m_strMajor, dlg.m_strPhone, dlg.m_strJoinDate, dlg.m_strPost,
					dlg.m_strIntroduction, dlg.m_strDepart, dlg.m_strPasswd,
					dlg.m_strPrivilige, dlg.m_strName);
				theApp.m_DB.ExecuteSQL(update);

				InitDialogCtrl();//更新数据列表
				MessageBoxA("成功更新人员信息！", "更新成功",
					MB_ICONEXCLAMATION | MB_OK);			
			}
			rs.Close();
			return;
		}
		else MessageBox("查找数据出错，请检查数据库！", "编辑失败", MB_OK);
		rs.Close();
		return;
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
	MessageBox("更新信息失败！可能填写的数据格式出错，请重新填写！", "更新失败", MB_OK);
}
//右键菜单的删除功能
void CAdminDlg::RMDelete()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("请选择要删除的信息！", "请确定",
			MB_ICONQUESTION | MB_OK);
		return;
	}
	CString strName = m_ctrlList.GetItemText(iItem, 0);
	if (strName == theApp.m_strUserName)
	{
		if(MessageBoxA("您将要删除自己的账户信息，删除后下次将无法登陆！", "请确定",
			MB_ICONQUESTION | MB_YESNO)==IDNO)return;
	}
	CDeletePersonDlg dlg;
	dlg.m_strName = strName;

	if (dlg.DoModal() == IDOK)
	{
		try{

			//在person 表删除记录
			CString drop;
			drop.Format("delete from person where pname = '%s'", strName);
			theApp.m_DB.ExecuteSQL(drop);
			if (dlg.m_intTwo)
			{
				//course_table 表
				drop.Format("delete from course_table where pname = '%s'", strName);
				theApp.m_DB.ExecuteSQL(drop);
				//receive_infor 表
				drop.Format("delete from receive_infor where receiver = '%s'", strName);
				theApp.m_DB.ExecuteSQL(drop);
				//send_infor 表
				drop.Format("delete from send_infor where sender = '%s'", strName);
				theApp.m_DB.ExecuteSQL(drop);
				//start_work 表
				drop.Format("delete from start_work where signer = '%s'", strName);
				theApp.m_DB.ExecuteSQL(drop);

				//register_infor 表
				drop.Format("delete from register_infor where signer = '%s'", strName);
				theApp.m_DB.ExecuteSQL(drop);
			}
			InitDialogCtrl();//更新数据列表
			MessageBoxA("删除信息成功！", "成功删除",
				MB_ICONWARNING | MB_OK);
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
	
}

void CAdminDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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

		menuTray.LoadMenu(IDR_MENU3);
		id = menuTray.GetSubMenu(0)->TrackPopupMenu(TPM_RETURNCMD |
			TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
		switch (id)
		{
		case ID_AADD_PERSON:RMAdd(); break;
		case ID_AEDIT_PERSON: RMEdit(); break;
		case ID_ADELETE_PERSON: RMDelete(); break;
		default:
			break;
		}
	}
}

BOOL CAdminDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	m_ctrlList.InsertColumn(0, (LPCTSTR)"姓名", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(1, (LPCTSTR) "电话", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(2, (LPCTSTR)"性别", LVCFMT_LEFT, 40);
	m_ctrlList.InsertColumn(3, (LPCTSTR)"学院", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(4, (LPCTSTR) "专业", LVCFMT_CENTER, 100);
	m_ctrlList.InsertColumn(5, (LPCTSTR) "年级", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(6, (LPCTSTR)"部门", LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(7, (LPCTSTR)"备注", LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(8, (LPCTSTR)"简介", LVCFMT_LEFT, 100);



	InitDialogCtrl();
	// TODO:  在此添加额外的初始化
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
