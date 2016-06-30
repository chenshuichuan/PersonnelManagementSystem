// AdminDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "AdminDlg.h"
#include "afxdialogex.h"
#include"person.h"
#include"DeletePersonDlg.h"
#include"AddUserDlg.h"
#include"excel9.h"

// CAdminDlg �Ի���

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


// CAdminDlg ��Ϣ�������


void CAdminDlg::OnBnClickedBtaExport()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_ctrlList.GetItemCount() == 0)
	{
		MessageBoxA("��ǰ�б���û�����ݿ��Ե���,��������ݣ�", "��������", MB_ICONERROR | MB_OK);
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
		MessageBoxA("�����޷�����ExcelӦ��,�����а�װExcel��������", "��������",
			MB_ICONERROR | MB_OK);
		return;
	}
	books = app.GetWorkbooks();
	book = books.Add(covOptional);
	sheets = book.GetWorksheets();
	sheet = sheets.GetItem(COleVariant((short)1));

	//�������Ϊ��A��1���ͣ�A��1����������Ԫ��
	range = sheet.GetRange(COleVariant(_T("C1")), COleVariant(_T("C1")));
	//���õ�Ԫ������ΪHello Excel
	range.SetValue(COleVariant("ͨѶ¼"));
	//ѡ�����У������ÿ��Ϊ����Ӧ
	//cols =range.GetColumns();
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("A2")), COleVariant(_T("A2")));
	range.SetValue(COleVariant(_T("����")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("B2")), COleVariant(_T("B2")));
	range.SetValue(COleVariant(_T("�绰")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("C2")), COleVariant(_T("C2")));
	range.SetValue(COleVariant(_T("�Ա�")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("D2")), COleVariant(_T("D2")));
	range.SetValue(COleVariant(_T("ѧԺ")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("E2")), COleVariant(_T("E2")));
	range.SetValue(COleVariant(_T("רҵ")));

	range = sheet.GetRange(COleVariant(_T("F2")), COleVariant(_T("F2")));
	range.SetValue(COleVariant(_T("�꼶")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("G2")), COleVariant(_T("G2")));
	range.SetValue(COleVariant(_T("����")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("H2")), COleVariant(_T("H2")));
	range.SetValue(COleVariant(_T("��ע")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("I2")), COleVariant(_T("I2")));
	range.SetValue(COleVariant(_T("���")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	int i = 0, size = m_ctrlList.GetItemCount();
	while (i < size)
	{
		//ȡ��id
		//�������Ϊ��A��i+3���ͣ�A��i+3����������Ԫ��
		CString index;
		index.Format("A%d", i + 3);
		range = sheet.GetRange(COleVariant(index), COleVariant(index));
		//���õ�Ԫ������Ϊ
		range.SetValue(COleVariant(m_ctrlList.GetItemText(i, 0)));
		//ѡ�����У������ÿ��Ϊ����Ӧ
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
	//��ʾExcel��
	app.SetVisible(TRUE);
	app.SetUserControl(TRUE);
	//book.Save();
	//app.Quit();
	//�ͷŶ��� 
	range.ReleaseDispatch();
	sheet.ReleaseDispatch();
	sheets.ReleaseDispatch();
	book.ReleaseDispatch();
	books.ReleaseDispatch();
	app.ReleaseDispatch();
	CString str;
	str.Format("�ɹ����� %d �����ݼ�¼��", size);
	MessageBoxA(str, "�����ɹ�",
		MB_ICONEXCLAMATION | MB_OK);

}



//��ʼ���ؼ�����
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
			MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
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
//��������ӵ�list��
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
	//��nIndex һ�в�����ϵ����Ϣ����
	m_ctrlList.InsertItem(&lvItem);// ID
	m_ctrlList.SetItemText(nIndex, 1, telephone);
	if(sex)temp ="��";
	else temp = "Ů";
	m_ctrlList.SetItemText(nIndex, 2, temp);
	m_ctrlList.SetItemText(nIndex, 3, academy);
	m_ctrlList.SetItemText(nIndex, 4, major);
	m_ctrlList.SetItemText(nIndex, 5, grade);
	m_ctrlList.SetItemText(nIndex, 6, depart);
	m_ctrlList.SetItemText(nIndex, 7, extra);
	m_ctrlList.SetItemText(nIndex, 8, introduction);

}

//�Ҽ��˵�����ӹ���
void CAdminDlg::RMAdd()
{
	CAddUserDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		try{
			int sex = 0;
			if (dlg.m_strSex == "��")sex = 1;
			else sex = 0;

			CString insert;
			insert.Format("insert into person(pname,id,sex,academy,major,"
				"telephone,join_date,post,introduction,department,passwd,privilege) "
				"values('%s','%s',%d,'%s','%s','%s','%s','%s','%s','%s','%s',%s)",
				dlg.m_strName,dlg.m_strID,sex,dlg.m_strAcademy,
				dlg.m_strMajor,dlg.m_strPhone,dlg.m_strJoinDate,dlg.m_strPost,
				dlg.m_strIntroduction,dlg.m_strDepart,dlg.m_strPasswd,dlg.m_strPrivilige);
			theApp.m_DB.ExecuteSQL(insert);

			InitDialogCtrl();//���������б�
			MessageBoxA("�ɹ������Ա��Ϣ,�´�����ϵͳ����ʹ�ø��˺ŵ�¼��", "��ӳɹ�",
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
		MessageBox("�����Ϣʧ�ܣ�������д�����ݸ�ʽ������������д��", "���ʧ��", MB_OK);
	}

}
//�Ҽ��˵��ı༭����
void CAdminDlg::RMEdit()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("��ѡ��Ҫ�޸ĵ���Ϣ��", "��ȷ��",
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
				dlg.m_strSex = "��";
			else dlg.m_strSex = "Ů";

			if (dlg.DoModal() == IDOK)
			{
				int sex = 0;
				if (dlg.m_strSex == "��")sex = 1;
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

				InitDialogCtrl();//���������б�
				MessageBoxA("�ɹ�������Ա��Ϣ��", "���³ɹ�",
					MB_ICONEXCLAMATION | MB_OK);			
			}
			rs.Close();
			return;
		}
		else MessageBox("�������ݳ����������ݿ⣡", "�༭ʧ��", MB_OK);
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
	MessageBox("������Ϣʧ�ܣ�������д�����ݸ�ʽ������������д��", "����ʧ��", MB_OK);
}
//�Ҽ��˵���ɾ������
void CAdminDlg::RMDelete()
{
	int iItem = m_ctrlList.GetNextItem(-1, LVNI_SELECTED);
	if (iItem == -1)
	{
		MessageBoxA("��ѡ��Ҫɾ������Ϣ��", "��ȷ��",
			MB_ICONQUESTION | MB_OK);
		return;
	}
	CString strName = m_ctrlList.GetItemText(iItem, 0);
	if (strName == theApp.m_strUserName)
	{
		if(MessageBoxA("����Ҫɾ���Լ����˻���Ϣ��ɾ�����´ν��޷���½��", "��ȷ��",
			MB_ICONQUESTION | MB_YESNO)==IDNO)return;
	}
	CDeletePersonDlg dlg;
	dlg.m_strName = strName;

	if (dlg.DoModal() == IDOK)
	{
		try{

			//��person ��ɾ����¼
			CString drop;
			drop.Format("delete from person where pname = '%s'", strName);
			theApp.m_DB.ExecuteSQL(drop);
			if (dlg.m_intTwo)
			{
				//course_table ��
				drop.Format("delete from course_table where pname = '%s'", strName);
				theApp.m_DB.ExecuteSQL(drop);
				//receive_infor ��
				drop.Format("delete from receive_infor where receiver = '%s'", strName);
				theApp.m_DB.ExecuteSQL(drop);
				//send_infor ��
				drop.Format("delete from send_infor where sender = '%s'", strName);
				theApp.m_DB.ExecuteSQL(drop);
				//start_work ��
				drop.Format("delete from start_work where signer = '%s'", strName);
				theApp.m_DB.ExecuteSQL(drop);

				//register_infor ��
				drop.Format("delete from register_infor where signer = '%s'", strName);
				theApp.m_DB.ExecuteSQL(drop);
			}
			InitDialogCtrl();//���������б�
			MessageBoxA("ɾ����Ϣ�ɹ���", "�ɹ�ɾ��",
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	m_ctrlList.InsertColumn(0, (LPCTSTR)"����", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(1, (LPCTSTR) "�绰", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(2, (LPCTSTR)"�Ա�", LVCFMT_LEFT, 40);
	m_ctrlList.InsertColumn(3, (LPCTSTR)"ѧԺ", LVCFMT_LEFT, 100);
	m_ctrlList.InsertColumn(4, (LPCTSTR) "רҵ", LVCFMT_CENTER, 100);
	m_ctrlList.InsertColumn(5, (LPCTSTR) "�꼶", LVCFMT_CENTER, 50);
	m_ctrlList.InsertColumn(6, (LPCTSTR)"����", LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(7, (LPCTSTR)"��ע", LVCFMT_LEFT, 50);
	m_ctrlList.InsertColumn(8, (LPCTSTR)"���", LVCFMT_LEFT, 100);



	InitDialogCtrl();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
