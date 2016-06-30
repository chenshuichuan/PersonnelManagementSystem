// SignDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "SignDlg.h"
#include "afxdialogex.h"
#include"start_work.h"
#include"register_infor.h"
#include"EditSignDlg.h"

// CSignDlg �Ի���

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


// CSignDlg ��Ϣ�������

//�ϰ�ǩ����ť
void CSignDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

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
			MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
			return;
		}
		if (!ss.IsEOF())
		{
			//��������������Ƿ���յļ�¼ ���

			MessageBox("�㻹���ϰ�ǩ����¼û��ǩ�°࣬����ǩ�°࣡\n����޷���������ҹ���Ա��", "����", MB_OK);
		}
		else//�����ϰ�ǩ����Ϣ
		{
			CRecordset rs;
			rs.m_pDatabase = &theApp.m_DB;
			CString sql = "Select max(start_id) from start_work";
			//��ȡ ���IDֵ
			rs.Open(CRecordset::dynaset, sql);
			int id=0;
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

//�°�ǩ����ť
void CSignDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
			MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
			return;
		}
		if (!ss.IsEOF())//�ҵ��ϰ�ǩ����Ϣ����������ֵ��ǩ����¼
		{
			CRecordset rs;
			rs.m_pDatabase = &theApp.m_DB;
			CString sql = "Select max(sign_id) from register_infor";
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

			//��register_infor ���������
			CString startTime,ti, insert;
			if (tm.GetDay() != ss.m_start_time.GetDay())
			{
				MessageBox("�ҵ������ݴ������ҹ���Ա����", "�޷�ǩ��", MB_OK);
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

			//��start_work ��ɾ���ϰ��¼
			CString drop;
			drop.Format("delete from start_work where start_id = %d", ss.m_start_id);
			theApp.m_DB.ExecuteSQL(drop);

			SignSucceed(true);//����ɹ���Ϣ
		}
		else MessageBox("�㻹û���ϰ�ǩ���������ϰ�ǩ����", "����", MB_OK);
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
	//Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����
	//LVS_EX_FULLROWSELECT ȫ��ѡ��
	DWORD dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |
		LVS_EX_HEADERDRAGDROP | LVS_EX_ONECLICKACTIVATE | LVS_EX_UNDERLINEHOT;
	m_ctrlList.SetExtendedStyle(dwExStyle);
	//��ȡ�б�ؼ�����
	CRect rect;
	m_ctrlList.GetClientRect(&rect);
	int wide = rect.Width();//ȡ���б�ؼ����
	//��ʼ����ϵ���б�ؼ�
	m_ctrlList.InsertColumn(0, (LPCTSTR)"��ϢID", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(1, (LPCTSTR) "ǩ��", LVCFMT_LEFT, 80);
	m_ctrlList.InsertColumn(2, (LPCTSTR)"�ϰ�ǩ��ʱ��", LVCFMT_LEFT, 120);
	m_ctrlList.InsertColumn(3, (LPCTSTR)"�°�ǩ��ʱ��", LVCFMT_LEFT, 120);
	m_ctrlList.InsertColumn(4, (LPCTSTR) "��ʱ", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(5, (LPCTSTR) "��Ϣ����", LVCFMT_CENTER, 80);
	m_ctrlList.InsertColumn(6, (LPCTSTR)"��ע��Ϣ", LVCFMT_LEFT, 200);
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDialogCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//��ʼ���ؼ�����
void CSignDlg::InitDialogCtrl()
{
	while (m_ctrlList.GetItemCount()>0)
	{
		m_ctrlList.DeleteItem(0);
	}
	try
	{
		//Connect to the database
		//��register_infor ��Ľ����������ʾ
		CRegisterSet rs(&theApp.m_DB);
		CString strSQL;
		CTime tm;
		tm = CTime::GetCurrentTime();
		strSQL = "select * from register_infor";
		if (!rs.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			//if (!recordset.Open(CRecordset::dynaset,strSQL))
		{
			MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
			return;
		}

		while (!rs.IsEOF())
		{
			if (rs.m_start_time.GetMonth()==tm.GetMonth()&&
				rs.m_start_time.GetDay()==tm.GetDay())//������ǩ������Ϣ��ʾ
				AddInforToListBox(rs.m_sign_id,rs.m_signer,rs.m_start_time,
				rs.m_end_time,rs.m_working_hours,FALSE,rs.m_extra_infor);
			rs.MoveNext();
		}

		rs.Close();

		//��start_work �������ȫ����ʾ
		CSignSet ss(&theApp.m_DB);
		strSQL = "select * from start_work";
		if (!ss.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			//if (!recordset.Open(CRecordset::dynaset,strSQL))
		{
			MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
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
//��������ӵ�list��
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
	//��nIndex һ�в�����ϵ����Ϣ����
	m_ctrlList.InsertItem(&lvItem);// ID
	m_ctrlList.SetItemText(nIndex, 1, signer);//ǩ����
	temp = start.Format("%Y-%m-%d %X");
	m_ctrlList.SetItemText(nIndex, 2, temp);//�ϰ�ǩ��ʱ��
	temp = end.Format("%Y-%m-%d %X");
	if ((int)hours == -1 && !lock)
	{
		temp = "����Ŭ��������~~~";
		hours = 0;
	}
	else if ((int)hours == -1 && lock)
	{
		temp = "";
		hours = 0;
	}
	m_ctrlList.SetItemText(nIndex, 3, temp);//�°�

	temp.Format("%4.2f", hours);
	m_ctrlList.SetItemText(nIndex, 4, temp);
	if (lock)temp = "��";
	else temp = " ";
	m_ctrlList.SetItemText(nIndex, 5, temp);//�������
	m_ctrlList.SetItemText(nIndex, 6, extra);//��������
}

//sys=true��ʾ�ϰ�ǩ���ɹ�����Ϣ��false ��ʾ�°�ǩ���ɹ�����Ϣ
void CSignDlg::SignSucceed(bool sys)
{
	CString str, ti; //��ȡϵͳʱ��
	CString welcome;
	CTime tm;
	tm = CTime::GetCurrentTime();
	ti.Format("%d��%d��ǩ���ɹ�~~~",tm.GetHour(),tm.GetMinute());

	if (sys)//�ϰ�ǩ��
	{
		if ((tm.GetHour() == 7 || tm.GetHour() == 13) && tm.GetMinute() < 56)
			welcome = "\n������ǰ����Ӵ������Ŭ��~~~";
		if ((tm.GetHour() == 8 || tm.GetHour() == 14) && tm.GetMinute()>5)
			welcome = "\n����ٵ���Ӵ���´�����һ��ѽ~~~";
	}
	else//�°�ǩ��
	{
		welcome = "\n�������������ݰ�~~~";
	}
	srand((unsigned)time(NULL));
	int i = rand() % 10;
	if (i % 2 == 0)welcome = "";
	InitDialogCtrl();//ˢ�¿ؼ��б������

	MessageBox(ti+welcome, "ǩ���ɹ�", MB_OK);
}

//�Ҽ��˵��Ľ�����������
//lock ����true ˵������Ҫ����������Ϊ����
void CSignDlg::LockAddUnLock(bool lock)
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("��ѡ��Ҫ��������Ϣ��", "��ȷ��",
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
				if (MessageBoxA("���\"ȷ��\"��ť,����Ϣ��������", "��ȷ��",
					MB_ICONQUESTION | MB_YESNO) == IDNO)return;

				CString update;
				update.Format("update start_work set is_lock =%d "
					"where start_id =%d",
					0,id);
				theApp.m_DB.ExecuteSQL(update);
				m_ctrlList.SetItemText(iItem, 5, "");
				MessageBoxA("�ɹ�������ǩ����Ϣ��", "�����ɹ�",
					MB_ICONINFORMATION | MB_OK);
			}
			else if (rs.m_is_lock == FALSE&&lock == true)
			{
				if (MessageBoxA("���\"ȷ��\"��ť,����Ϣ��������", "��ȷ��",
					MB_ICONQUESTION | MB_YESNO) == IDNO)return;

				CString update;
				update.Format("update start_work set is_lock =%d "
					"where start_id =%d",
					1, id);
				theApp.m_DB.ExecuteSQL(update);
				m_ctrlList.SetItemText(iItem, 5, "��");
				MessageBoxA("�ɹ�������ǩ����Ϣ��", "�����ɹ�",
					MB_ICONINFORMATION | MB_OK);
			}
			UpdateData(FALSE);
			rs.Close();
			return;
		}
		//�����ߵ�����˵�����ϰ�ǩ������ û���ҵ�Ҫ�޸ĵ���Ϣ
		MessageBoxA("δ�ҵ�ѡ�����Ϣ,ֻ���޸�δǩ�°����Ϣ��", "��ȷ��",
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
//�Ҽ��˵��ı༭����
void CSignDlg::RMEdit()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("��ѡ��Ҫ�޸ĵ���Ϣ��", "��ȷ��",
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
			str.Format("%d��%d��", rs.m_start_time.GetYear(), rs.m_start_time.GetMonth());
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
				
				//���쿪ʼʱ��
				CTime st(rs.m_start_time.GetYear(), rs.m_start_time.GetMonth()
					, startDay, startHour,startMin,0);
				//�������ʱ�� endDay==0ʱ����ʱ�佫����
				CTime et(rs.m_start_time.GetYear(), rs.m_start_time.GetMonth()
					, endDay, endHour, endMin, 0);
				CRecordset crs;
				crs.m_pDatabase = &theApp.m_DB;
				CString sql1 = "Select max(sign_id) from register_infor";
				//��ȡ ���IDֵ
				crs.Open(CRecordset::dynaset, sql1);
				int idl = 0;
				if (!crs.IsEOF())
				{
					CDBVariant var;
					//��ID�ֶ�
					crs.GetFieldValue((short)0, var, SQL_C_SLONG);
					if (var.m_dwType != DBVT_NULL)
					{
						idl = var.m_iVal;
					}
					var.Clear();
				}
				if (idl < 1)idl = 10;
				crs.Close();

				//��register_infor ���������
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

				//��start_work ��ɾ���ϰ��¼
				CString drop;
				drop.Format("delete from start_work where start_id = %d", id);
				theApp.m_DB.ExecuteSQL(drop);
				MessageBoxA("�ɹ��޸ĸ�ǩ����Ϣ��", "�޸ĳɹ�",
					MB_ICONINFORMATION | MB_OK);
				InitDialogCtrl();//ˢ�¿ؼ�����
			}
			return;//��������������������
		}

		//�����ߵ�����˵�����ϰ�ǩ������ û���ҵ�Ҫ�޸ĵ���Ϣ
		MessageBoxA("δ�ҵ�ѡ�����Ϣ,ֻ���޸�δǩ�°����Ϣ��", "��ȷ��",
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
//�Ҽ��˵���ɾ������
void CSignDlg::RMDelete()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("��ѡ��Ҫɾ������Ϣ��", "��ȷ��",
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
			if (rs.m_is_lock)strLock = "����";
			else strLock = "δ����";
			str.Format("����Ҫɾ��:\"%d,%s,%s,%s\"��\n���\"ȷ��\"��ť,����Ϣ����ɾ����",
				id,signer,rs.m_start_time.Format("%Y-%m-%d %X"),strLock);
			if (MessageBoxA(str, "��ȷ��",
				MB_ICONQUESTION | MB_YESNO) == IDNO) return;
			//��start_work ��ɾ���ϰ��¼
			CString drop;
			drop.Format("delete from start_work where start_id = %d", id);
			theApp.m_DB.ExecuteSQL(drop);
			InitDialogCtrl();
			MessageBoxA("ɾ����Ϣ�ɹ���", "�ɹ�ɾ��",
				MB_ICONINFORMATION | MB_OK);		
		}
		//�����ߵ�����˵�����ϰ�ǩ������ û���ҵ�Ҫ�޸ĵ���Ϣ
		else MessageBoxA("δ�ҵ�ѡ�����Ϣ,��ǰ����ֻ��ɾ��δǩ�°����Ϣ��", "��ȷ��",
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	if (theApp.m_privilege)//����Ȩ��֧��
	{
		CMenu menuTray;
		CPoint point;
		int id;
		GetCursorPos(&point);
		//�����������˵���ʱ��,�˵�ʧȥ�����ò˵��Զ��ر�
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
