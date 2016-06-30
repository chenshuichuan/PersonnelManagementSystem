// SendBoxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "SendBoxDlg.h"
#include "afxdialogex.h"
#include"send_infor.h"
#include"ReadInforDlg.h"
#include"SendInforDlg.h"
#include"person.h"

// CSendBoxDlg �Ի���

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


// CSendBoxDlg ��Ϣ�������


BOOL CSendBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����
	//LVS_EX_FULLROWSELECT ȫ��ѡ��
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |
		LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT;
	m_ctrlList.SetExtendedStyle(dwExStyle);
	//��ʼ����ϵ���б�ؼ�
	m_ctrlList.InsertColumn(0, (LPCTSTR)"��ϢID", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(1, (LPCTSTR) "�ռ���", LVCFMT_LEFT, 80);
	m_ctrlList.InsertColumn(2, (LPCTSTR)"����ʱ��", LVCFMT_LEFT, 120);
	m_ctrlList.InsertColumn(3, (LPCTSTR)"����", LVCFMT_LEFT, 200);
	m_ctrlList.InsertColumn(4, (LPCTSTR) "��Ϣ����", LVCFMT_CENTER, 80);
	//m_ctrlList.InsertColumn(5, (LPCTSTR) "δ��", LVCFMT_CENTER, 50);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDialogCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//��ʼ���ؼ�����
void CSendBoxDlg::InitDialogCtrl()
{
	while (m_ctrlList.GetItemCount()>0)
	{
		m_ctrlList.DeleteItem(0);
	}
	try
	{
		//Connect to the database
		//��receive_infor ���������ʾ
		CSendSet rs(&theApp.m_DB);
		CString strSQL;
		strSQL.Format("select * from send_infor where sender='%s'",
			theApp.m_strUserName);
		if (!rs.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
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
//��������ӵ�list��
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
	//��nIndex һ�в��� ����
	m_ctrlList.InsertItem(&lvItem);// ID
	m_ctrlList.SetItemText(nIndex, 1, sender);// 
	temp = start.Format("%Y-%m-%d %X");
	m_ctrlList.SetItemText(nIndex, 2, temp);// 
	m_ctrlList.SetItemText(nIndex, 3, infor);// 
	m_ctrlList.SetItemText(nIndex, 4, level);
	
}


void CSendBoxDlg::OnBnClickedBtsRead()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RMRead();
}


void CSendBoxDlg::OnBnClickedBtsDelete()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RMDelete();
}


void CSendBoxDlg::OnBnClickedBtsSeng()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CSendInforDlg dlg;
	dlg.m_strSender = theApp.m_strUserName;
	CTime tm;
	tm = CTime::GetCurrentTime();
	dlg.m_strSendTime = tm.Format("%Y-%m-%d %X");

	if (dlg.DoModal() == IDOK)
	{
		CString str,receiver;
		if (dlg.m_strLevel == "ȫ��")
		{
			str.Format("select * from person");
			receiver = "ȫ����Ա";
		}
		else if (dlg.m_strLevel == "����")
		{
			str.Format("select * from person where department='%s'", dlg.m_strDepart);
			receiver = dlg.m_strDepart;
		}
		else if (dlg.m_strLevel == "����")
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
				MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
				return;
			}
			if (!ss.IsEOF())//�ҵ���Ϣ
			{
				CRecordset rs;
				rs.m_pDatabase = &theApp.m_DB;
				CString sql = "Select max(message_id) from send_infor";
				//��ȡ ���IDֵ
				rs.Open(CRecordset::dynaset, sql);
				int id = 0;
				if (!rs.IsEOF())
				{
					CDBVariant var;
					//��ID�ֶ�
					rs.GetFieldValue((short)0, var, SQL_C_SLONG);
					if (var.m_dwType != DBVT_NULL)
					{
						id = var.m_iVal;
					}
					var.Clear();
				}
				if (id < 1)id = 1;
				rs.Close();

				//��send_infor ���������
				//
				CString insert;
				insert.Format("insert into send_infor(message_id,message_infor,sender"
					",send_date,message_level,receiver)"
					" values(%d,'%s','%s','%s','%s','%s')", id + 1,
					dlg.m_strInfor, theApp.m_strUserName,
					dlg.m_strSendTime, dlg.m_strLevel, receiver);
				theApp.m_DB.ExecuteSQL(insert);
				

				//��receive_infor����Ӽ�¼
				sql = "Select max(message_id) from receive_infor";
				//��ȡ ���IDֵ
				rs.Open(CRecordset::dynaset, sql);
				if (!rs.IsEOF())
				{
					CDBVariant var;
					//��ID�ֶ�
					rs.GetFieldValue((short)0, var, SQL_C_SLONG);
					if (var.m_dwType != DBVT_NULL)
					{
						id = var.m_iVal;
					}
					var.Clear();
				}
				if (id < 1)id = 1;
				rs.Close();

				while (!ss.IsEOF())//�ҵ���Ϣ
				{
					if (ss.m_pname == theApp.m_strUserName)
					{
						ss.MoveNext();
						continue;//���ø��Լ���
					}
					insert.Format("insert into receive_infor(message_id,message_infor,sender"
						",send_date,message_level,receiver,is_read)"
						" values(%d,'%s','%s','%s','%s','%s',%d)", ++id,
						dlg.m_strInfor, theApp.m_strUserName,
						dlg.m_strSendTime, dlg.m_strLevel, ss.m_pname,0);
					theApp.m_DB.ExecuteSQL(insert);
					ss.MoveNext();
				}
				MessageBoxA("��Ϣ���ͳɹ���", "�ɹ�����",
					MB_ICONINFORMATION | MB_OK);
				InitDialogCtrl();//ˢ���б�
			}
			else MessageBox("���ݿ�δ�ҵ��ռ��ˣ��������ݿ⣡", "����", MB_OK);
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
//�Ҽ��˵��Ĳ鿴����
void CSendBoxDlg::RMRead()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("��ѡ��Ҫ�鿴����Ϣ��", "��ȷ��",
			MB_ICONQUESTION | MB_OK);
		return;
	}
	
	CReadInforDlg dlg;
	dlg.m_strSenderOrRecever = "�ռ��ˣ�";
	dlg.m_strName = m_ctrlList.GetItemText(iItem, 1);
	dlg.m_strInforId =m_ctrlList.GetItemText(iItem, 0);
	dlg.m_strTime = m_ctrlList.GetItemText(iItem, 2);
	dlg.m_strLevel = m_ctrlList.GetItemText(iItem, 4);
	dlg.m_strInfor = m_ctrlList.GetItemText(iItem, 3);
	if (dlg.DoModal() == IDOK)
	{
	}

	
}
//�Ҽ��˵���ɾ������
void CSendBoxDlg::RMDelete()
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
		str.Format("����Ҫɾ��:\"ID:%d,�ռ���:%s\n����ʱ�䣺%s\n����:%s\n����:%s\"��\n���\"ȷ��\"��ť,����Ϣ����ɾ����",
			id, m_ctrlList.GetItemText(iItem, 1),
			m_ctrlList.GetItemText(iItem, 2),
			m_ctrlList.GetItemText(iItem, 3),
			m_ctrlList.GetItemText(iItem, 4));
		if (MessageBoxA(str, "��ȷ��",
			MB_ICONQUESTION | MB_YESNO) == IDNO) return;
		//��start_work ��ɾ���ϰ��¼
		CString drop;
		drop.Format("delete from send_infor where message_id = %d", id);
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
