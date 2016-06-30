// SendBoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "SendBoxDlg.h"
#include "afxdialogex.h"
#include"send_infor.h"
#include"ReadInforDlg.h"
#include"SendInforDlg.h"
#include"person.h"

// CSendBoxDlg 对话框

IMPLEMENT_DYNAMIC(CSendBoxDlg, CDialogEx)

CSendBoxDlg::CSendBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSendBoxDlg::IDD, pParent)
{

}

CSendBoxDlg::~CSendBoxDlg()
{
}

void CSendBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CSendBoxDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTS_READ, &CSendBoxDlg::OnBnClickedBtsRead)
	ON_BN_CLICKED(IDC_BTS_DELETE, &CSendBoxDlg::OnBnClickedBtsDelete)
	ON_BN_CLICKED(IDC_BTS_SENG, &CSendBoxDlg::OnBnClickedBtsSeng)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CSendBoxDlg::OnNMRClickList1)
END_MESSAGE_MAP()


// CSendBoxDlg 消息处理程序


BOOL CSendBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//为列表视图控件添加全行选中和栅格风格
	//LVS_EX_FULLROWSELECT 全行选择
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |
		LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT;
	m_ctrlList.SetExtendedStyle(dwExStyle);
	//初始化联系人列表控件
	m_ctrlList.InsertColumn(0, (LPCTSTR)"信息ID", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(1, (LPCTSTR) "收件人", LVCFMT_LEFT, 80);
	m_ctrlList.InsertColumn(2, (LPCTSTR)"发送时间", LVCFMT_LEFT, 120);
	m_ctrlList.InsertColumn(3, (LPCTSTR)"内容", LVCFMT_LEFT, 200);
	m_ctrlList.InsertColumn(4, (LPCTSTR) "信息级别", LVCFMT_CENTER, 80);
	//m_ctrlList.InsertColumn(5, (LPCTSTR) "未读", LVCFMT_CENTER, 50);

	// TODO:  在此添加额外的初始化
	InitDialogCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//初始化控件数据
void CSendBoxDlg::InitDialogCtrl()
{
	while (m_ctrlList.GetItemCount()>0)
	{
		m_ctrlList.DeleteItem(0);
	}
	try
	{
		//Connect to the database
		//将receive_infor 表的数据显示
		CSendSet rs(&theApp.m_DB);
		CString strSQL;
		strSQL.Format("select * from send_infor where sender='%s'",
			theApp.m_strUserName);
		if (!rs.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		while (!rs.IsEOF())
		{
			AddInforToListBox(rs.m_message_id, rs.m_receiver, rs.m_send_date,
				rs.m_message_infor, rs.m_message_level);
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
void CSendBoxDlg::AddInforToListBox(long id, CString sender,
	CTime start, CString infor, CString level)
{
	int nIndex = m_ctrlList.GetItemCount();
	LV_ITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nIndex;
	lvItem.iSubItem = 0;
	CString temp;
	temp.Format("%d", (int)id);
	lvItem.pszText = (char*)(LPCTSTR)temp;
	//在nIndex 一行插入 数据
	m_ctrlList.InsertItem(&lvItem);// ID
	m_ctrlList.SetItemText(nIndex, 1, sender);// 
	temp = start.Format("%Y-%m-%d %X");
	m_ctrlList.SetItemText(nIndex, 2, temp);// 
	m_ctrlList.SetItemText(nIndex, 3, infor);// 
	m_ctrlList.SetItemText(nIndex, 4, level);
	
}


void CSendBoxDlg::OnBnClickedBtsRead()
{
	// TODO:  在此添加控件通知处理程序代码
	RMRead();
}


void CSendBoxDlg::OnBnClickedBtsDelete()
{
	// TODO:  在此添加控件通知处理程序代码
	RMDelete();
}


void CSendBoxDlg::OnBnClickedBtsSeng()
{
	// TODO:  在此添加控件通知处理程序代码
	CSendInforDlg dlg;
	dlg.m_strSender = theApp.m_strUserName;
	CTime tm;
	tm = CTime::GetCurrentTime();
	dlg.m_strSendTime = tm.Format("%Y-%m-%d %X");

	if (dlg.DoModal() == IDOK)
	{
		CString str,receiver;
		if (dlg.m_strLevel == "全体")
		{
			str.Format("select * from person");
			receiver = "全体人员";
		}
		else if (dlg.m_strLevel == "部门")
		{
			str.Format("select * from person where department='%s'", dlg.m_strDepart);
			receiver = dlg.m_strDepart;
		}
		else if (dlg.m_strLevel == "个人")
		{
			str.Format("select * from person where pname='%s'", dlg.m_strPerson);
			receiver = dlg.m_strPerson;
		}
		
		try
		{
			CTime tm;
			tm = CTime::GetCurrentTime();
			Cperson ss(&theApp.m_DB);
			
			if (!ss.Open(AFX_DB_USE_DEFAULT_TYPE, str))
			{
				MessageBox("打开数据库失败!", "数据库错误", MB_OK);
				return;
			}
			if (!ss.IsEOF())//找到信息
			{
				CRecordset rs;
				rs.m_pDatabase = &theApp.m_DB;
				CString sql = "Select max(message_id) from send_infor";
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

				//在send_infor 表插入数据
				//
				CString insert;
				insert.Format("insert into send_infor(message_id,message_infor,sender"
					",send_date,message_level,receiver)"
					" values(%d,'%s','%s','%s','%s','%s')", id + 1,
					dlg.m_strInfor, theApp.m_strUserName,
					dlg.m_strSendTime, dlg.m_strLevel, receiver);
				theApp.m_DB.ExecuteSQL(insert);
				

				//在receive_infor上添加记录
				sql = "Select max(message_id) from receive_infor";
				//获取 最大ID值
				rs.Open(CRecordset::dynaset, sql);
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

				while (!ss.IsEOF())//找到信息
				{
					if (ss.m_pname == theApp.m_strUserName)
					{
						ss.MoveNext();
						continue;//不用给自己发
					}
					insert.Format("insert into receive_infor(message_id,message_infor,sender"
						",send_date,message_level,receiver,is_read)"
						" values(%d,'%s','%s','%s','%s','%s',%d)", ++id,
						dlg.m_strInfor, theApp.m_strUserName,
						dlg.m_strSendTime, dlg.m_strLevel, ss.m_pname,0);
					theApp.m_DB.ExecuteSQL(insert);
					ss.MoveNext();
				}
				MessageBoxA("信息发送成功！", "成功发送",
					MB_ICONINFORMATION | MB_OK);
				InitDialogCtrl();//刷新列表
			}
			else MessageBox("数据库未找到收件人，请检查数据库！", "警告", MB_OK);
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
}


void CSendBoxDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	CMenu menuTray;
	CPoint point;
	int id;
	GetCursorPos(&point);
	//如果点击弹出菜单的时候,菜单失去焦点让菜单自动关闭
	SetForegroundWindow();

	menuTray.LoadMenu(IDR_MENU2);
	id = menuTray.GetSubMenu(0)->TrackPopupMenu(TPM_RETURNCMD |
		TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	switch (id)
	{
	case ID_READ: RMRead(); break;
	case ID_DELETE: RMDelete(); break;
	default:
		break;
	}
}
//右键菜单的查看功能
void CSendBoxDlg::RMRead()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("请选择要查看的信息！", "请确定",
			MB_ICONQUESTION | MB_OK);
		return;
	}
	
	CReadInforDlg dlg;
	dlg.m_strSenderOrRecever = "收件人：";
	dlg.m_strName = m_ctrlList.GetItemText(iItem, 1);
	dlg.m_strInforId =m_ctrlList.GetItemText(iItem, 0);
	dlg.m_strTime = m_ctrlList.GetItemText(iItem, 2);
	dlg.m_strLevel = m_ctrlList.GetItemText(iItem, 4);
	dlg.m_strInfor = m_ctrlList.GetItemText(iItem, 3);
	if (dlg.DoModal() == IDOK)
	{
	}

	
}
//右键菜单的删除功能
void CSendBoxDlg::RMDelete()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("请选择要删除的信息！", "请确定",
			MB_ICONQUESTION | MB_OK);
		return;
	}
	int  id = atoi(m_ctrlList.GetItemText(iItem, 0));
	try{
		CString str;
		str.Format("您将要删除:\"ID:%d,收件人:%s\n发送时间：%s\n内容:%s\n级别:%s\"，\n点击\"确定\"按钮,该信息将被删除？",
			id, m_ctrlList.GetItemText(iItem, 1),
			m_ctrlList.GetItemText(iItem, 2),
			m_ctrlList.GetItemText(iItem, 3),
			m_ctrlList.GetItemText(iItem, 4));
		if (MessageBoxA(str, "请确定",
			MB_ICONQUESTION | MB_YESNO) == IDNO) return;
		//在start_work 表删除上班记录
		CString drop;
		drop.Format("delete from send_infor where message_id = %d", id);
		theApp.m_DB.ExecuteSQL(drop);
		InitDialogCtrl();
		MessageBoxA("删除信息成功！", "成功删除",
			MB_ICONINFORMATION | MB_OK);
	}
	catch (CDBException ex){
		AfxMessageBox(ex.m_strError);
		AfxMessageBox(ex.m_strStateNativeOrigin);
	}
}
