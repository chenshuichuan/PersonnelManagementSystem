// ReceiveBoxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "ReceiveBoxDlg.h"
#include "afxdialogex.h"
#include"receive_infor.h"
#include"ReadInforDlg.h"

// CReceiveBoxDlg �Ի���

IMPLEMENT_DYNAMIC(CReceiveBoxDlg, CDialogEx)

CReceiveBoxDlg::CReceiveBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReceiveBoxDlg::IDD, pParent)
{

}

CReceiveBoxDlg::~CReceiveBoxDlg()
{

	// �����ģ̬�Ի����Ѿ�������ɾ����   
	if (NULL != m_dlg)
	{
		// ɾ����ģ̬�Ի������   
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


// CReceiveBoxDlg ��Ϣ�������


void CReceiveBoxDlg::OnBnClickedBtrRead()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RMRead();
}


void CReceiveBoxDlg::OnBnClickedBtrDelete()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RMDelete();
}


void CReceiveBoxDlg::OnBnClickedBtrRefrash()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	InitDialogCtrl();
}


BOOL CReceiveBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����
	//LVS_EX_FULLROWSELECT ȫ��ѡ��
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |
		LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT;
	m_ctrlList.SetExtendedStyle(dwExStyle);

	//��ʼ����ϵ���б�ؼ�
	m_ctrlList.InsertColumn(0, (LPCTSTR)"��ϢID", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(1, (LPCTSTR) "������", LVCFMT_LEFT, 80);
	m_ctrlList.InsertColumn(2, (LPCTSTR)"����ʱ��", LVCFMT_LEFT, 120);
	m_ctrlList.InsertColumn(3, (LPCTSTR)"����", LVCFMT_LEFT, 200);
	m_ctrlList.InsertColumn(4, (LPCTSTR) "��Ϣ����", LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(5, (LPCTSTR) "δ��", LVCFMT_CENTER, 50);
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDialogCtrl();

	if (m_haveNoRead > 0)
	{
		// ���ָ�����m_pTipDlg��ֵΪNULL����Ի���δ��������Ҫ��̬����  
		if (NULL == m_dlg)
		{
			// ������ģ̬�Ի���ʵ��  
			m_dlg = new CRemindReceiveDlg();
			m_dlg->Create(IDD_DIALOG_REMIND, this);

		}
		// ��ʾ��ģ̬�Ի���  
		m_dlg->m_intNumberOfMessage = m_haveNoRead;
		m_dlg->UpdateData(FALSE);
		m_dlg->ShowWindow(SW_SHOW);

	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


//��ʼ���ؼ�����
void CReceiveBoxDlg::InitDialogCtrl()
{
	while (m_ctrlList.GetItemCount()>0)
	{
		m_ctrlList.DeleteItem(0);
	}
	try
	{
		//Connect to the database
		//��receive_infor ���������ʾ
		CReceiveSet rs(&theApp.m_DB);
		CString strSQL;
		strSQL.Format("select * from receive_infor where receiver='%s'",
			theApp.m_strUserName);
		if (!rs.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
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
//��������ӵ�list��
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
	//��nIndex һ�в��� ����
	m_ctrlList.InsertItem(&lvItem);// ID
	m_ctrlList.SetItemText(nIndex, 1, sender);// 
	temp = start.Format("%Y-%m-%d %X");
	m_ctrlList.SetItemText(nIndex, 2, temp);// 
	m_ctrlList.SetItemText(nIndex, 3, infor);// 
	m_ctrlList.SetItemText(nIndex, 4, level);
	if (isRead)temp = "";
	else temp = "��";
	m_ctrlList.SetItemText(nIndex, 5, temp);// 
}


void CReceiveBoxDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CMenu menuTray;
	CPoint point;
	int id;
	GetCursorPos(&point);
	//�����������˵���ʱ��,�˵�ʧȥ�����ò˵��Զ��ر�
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
// �Ҽ��˵��Ĳ鿴����
void CReceiveBoxDlg::RMRead()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("��ѡ��Ҫ�鿴����Ϣ��", "��ȷ��",
			MB_ICONQUESTION | MB_OK);
		return;
	}

	CReadInforDlg dlg;
	dlg.m_strSenderOrRecever = "�����ˣ�";
	dlg.m_strName = m_ctrlList.GetItemText(iItem, 1);
	dlg.m_strInforId = m_ctrlList.GetItemText(iItem, 0);
	dlg.m_strTime = m_ctrlList.GetItemText(iItem, 2);
	dlg.m_strLevel = m_ctrlList.GetItemText(iItem, 4);
	dlg.m_strInfor = m_ctrlList.GetItemText(iItem, 3);
	if (dlg.DoModal() == IDOK)
	{
	}
	if (m_ctrlList.GetItemText(iItem, 5) == "��")
	{
		try
		{
			//������Ϣ����Ϊ�Ѷ�
			CString strSQL;
			CReceiveSet ss(&theApp.m_DB);
			strSQL.Format("select * from receive_infor where message_id=%s",
				m_ctrlList.GetItemText(iItem, 0));
			if (!ss.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			{
				MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
				return;
			}
			if (!ss.IsEOF())
			{
				CString update;
				update.Format("update receive_infor set is_read =%d where message_id =%d",
					1, ss.m_message_id);
				theApp.m_DB.ExecuteSQL(update);
			}
			else MessageBox("���ݿ�������ݳ���!", "���ݿ����", MB_OK);
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
//�Ҽ��˵���ɾ������
void CReceiveBoxDlg::RMDelete()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("��ѡ��Ҫɾ������Ϣ��", "��ȷ��",
			MB_ICONQUESTION | MB_OK);
		return;
	}
	int  id = atoi(m_ctrlList.GetItemText(iItem, 0));
	try{
		CString str;
		str.Format("����Ҫɾ��:\"ID:%d,������:%s\n����ʱ�䣺%s\n����:%s\n����:%s\"��\n���\"ȷ��\"��ť,����Ϣ����ɾ����",
			id, m_ctrlList.GetItemText(iItem, 1), 
			m_ctrlList.GetItemText(iItem, 2),
			m_ctrlList.GetItemText(iItem, 3),
			m_ctrlList.GetItemText(iItem, 4));
			if (MessageBoxA(str, "��ȷ��",
				MB_ICONQUESTION | MB_YESNO) == IDNO) return;
			//��start_work ��ɾ���ϰ��¼
			CString drop;
			drop.Format("delete from receive_infor where message_id = %d", id);
			theApp.m_DB.ExecuteSQL(drop);
			InitDialogCtrl();
			MessageBoxA("ɾ����Ϣ�ɹ���", "�ɹ�ɾ��",
				MB_ICONINFORMATION | MB_OK);
	}
	catch (CDBException ex){
		AfxMessageBox(ex.m_strError);
		AfxMessageBox(ex.m_strStateNativeOrigin);
	}
}