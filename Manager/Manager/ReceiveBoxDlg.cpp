// ReceiveBoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "ReceiveBoxDlg.h"
#include "afxdialogex.h"
#include"receive_infor.h"
#include"ReadInforDlg.h"

// CReceiveBoxDlg 对话框

IMPLEMENT_DYNAMIC(CReceiveBoxDlg, CDialogEx)

CReceiveBoxDlg::CReceiveBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReceiveBoxDlg::IDD, pParent)
{

}

CReceiveBoxDlg::~CReceiveBoxDlg()
{

	// 如果非模态对话框已经创建则删除它   
	if (NULL != m_dlg)
	{
		// 删除非模态对话框对象   
		delete m_dlg;
	}
}

void CReceiveBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CReceiveBoxDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTR_READ, &CReceiveBoxDlg::OnBnClickedBtrRead)
	ON_BN_CLICKED(IDC_BTR_DELETE, &CReceiveBoxDlg::OnBnClickedBtrDelete)
	ON_BN_CLICKED(IDC_BTR_REFRASH, &CReceiveBoxDlg::OnBnClickedBtrRefrash)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CReceiveBoxDlg::OnNMRClickList1)
END_MESSAGE_MAP()


// CReceiveBoxDlg 消息处理程序


void CReceiveBoxDlg::OnBnClickedBtrRead()
{
	// TODO:  在此添加控件通知处理程序代码
	RMRead();
}


void CReceiveBoxDlg::OnBnClickedBtrDelete()
{
	// TODO:  在此添加控件通知处理程序代码
	RMDelete();
}


void CReceiveBoxDlg::OnBnClickedBtrRefrash()
{
	// TODO:  在此添加控件通知处理程序代码
	InitDialogCtrl();
}


BOOL CReceiveBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//为列表视图控件添加全行选中和栅格风格
	//LVS_EX_FULLROWSELECT 全行选择
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |
		LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT;
	m_ctrlList.SetExtendedStyle(dwExStyle);

	//初始化联系人列表控件
	m_ctrlList.InsertColumn(0, (LPCTSTR)"信息ID", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(1, (LPCTSTR) "发件人", LVCFMT_LEFT, 80);
	m_ctrlList.InsertColumn(2, (LPCTSTR)"发送时间", LVCFMT_LEFT, 120);
	m_ctrlList.InsertColumn(3, (LPCTSTR)"内容", LVCFMT_LEFT, 200);
	m_ctrlList.InsertColumn(4, (LPCTSTR) "信息级别", LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(5, (LPCTSTR) "未读", LVCFMT_CENTER, 50);
	
	// TODO:  在此添加额外的初始化
	InitDialogCtrl();

	if (m_haveNoRead > 0)
	{
		// 如果指针变量m_pTipDlg的值为NULL，则对话框还未创建，需要动态创建  
		if (NULL == m_dlg)
		{
			// 创建非模态对话框实例  
			m_dlg = new CRemindReceiveDlg();
			m_dlg->Create(IDD_DIALOG_REMIND, this);

		}
		// 显示非模态对话框  
		m_dlg->m_intNumberOfMessage = m_haveNoRead;
		m_dlg->UpdateData(FALSE);
		m_dlg->ShowWindow(SW_SHOW);

	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


//初始化控件数据
void CReceiveBoxDlg::InitDialogCtrl()
{
	while (m_ctrlList.GetItemCount()>0)
	{
		m_ctrlList.DeleteItem(0);
	}
	try
	{
		//Connect to the database
		//将receive_infor 表的数据显示
		CReceiveSet rs(&theApp.m_DB);
		CString strSQL;
		strSQL.Format("select * from receive_infor where receiver='%s'",
			theApp.m_strUserName);
		if (!rs.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		m_haveNoRead = 0;
		while (!rs.IsEOF())
		{
			AddInforToListBox(rs.m_message_id, rs.m_sender, rs.m_send_date,
					rs.m_message_infor, rs.m_message_level, rs.m_is_read);
			if (!rs.m_is_read) ++m_haveNoRead;
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
void CReceiveBoxDlg::AddInforToListBox(long id, CString sender,
	CTime start,CString infor,CString level, BOOL isRead )
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
	if (isRead)temp = "";
	else temp = "是";
	m_ctrlList.SetItemText(nIndex, 5, temp);// 
}


void CReceiveBoxDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
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
// 右键菜单的查看功能
void CReceiveBoxDlg::RMRead()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("请选择要查看的信息！", "请确定",
			MB_ICONQUESTION | MB_OK);
		return;
	}

	CReadInforDlg dlg;
	dlg.m_strSenderOrRecever = "发件人：";
	dlg.m_strName = m_ctrlList.GetItemText(iItem, 1);
	dlg.m_strInforId = m_ctrlList.GetItemText(iItem, 0);
	dlg.m_strTime = m_ctrlList.GetItemText(iItem, 2);
	dlg.m_strLevel = m_ctrlList.GetItemText(iItem, 4);
	dlg.m_strInfor = m_ctrlList.GetItemText(iItem, 3);
	if (dlg.DoModal() == IDOK)
	{
	}
	if (m_ctrlList.GetItemText(iItem, 5) == "是")
	{
		try
		{
			//将该信息设置为已读
			CString strSQL;
			CReceiveSet ss(&theApp.m_DB);
			strSQL.Format("select * from receive_infor where message_id=%s",
				m_ctrlList.GetItemText(iItem, 0));
			if (!ss.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			{
				MessageBox("打开数据库失败!", "数据库错误", MB_OK);
				return;
			}
			if (!ss.IsEOF())
			{
				CString update;
				update.Format("update receive_infor set is_read =%d where message_id =%d",
					1, ss.m_message_id);
				theApp.m_DB.ExecuteSQL(update);
			}
			else MessageBox("数据库查找数据出错!", "数据库错误", MB_OK);
			ss.Close();
			InitDialogCtrl();
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
//右键菜单的删除功能
void CReceiveBoxDlg::RMDelete()
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
		str.Format("您将要删除:\"ID:%d,发件人:%s\n发送时间：%s\n内容:%s\n级别:%s\"，\n点击\"确定\"按钮,该信息将被删除？",
			id, m_ctrlList.GetItemText(iItem, 1), 
			m_ctrlList.GetItemText(iItem, 2),
			m_ctrlList.GetItemText(iItem, 3),
			m_ctrlList.GetItemText(iItem, 4));
			if (MessageBoxA(str, "请确定",
				MB_ICONQUESTION | MB_YESNO) == IDNO) return;
			//在start_work 表删除上班记录
			CString drop;
			drop.Format("delete from receive_infor where message_id = %d", id);
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