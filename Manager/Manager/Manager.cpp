
// Manager.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Manager.h"
#include "ManagerDlg.h"
#include "SkinPlusPlus.h"
#include<fstream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CManagerApp

BEGIN_MESSAGE_MAP(CManagerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CManagerApp ����

CManagerApp::CManagerApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CManagerApp ����
CManagerApp theApp;


// CManagerApp ��ʼ��

BOOL CManagerApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	InitializeSkin("XPCorona.ssk");
	
	LoadConfigInfor();//
	OpenDB();

	CManagerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
		//dlg.OnClose();//����Ƿ�����δǩ�°࣬����
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	m_DB.Close();//�ر����ݿ�
	SaveConfigInfor();
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

//�����ݿ�
void CManagerApp::OpenDB()
{
	try
	{
		//Connect to the database
		// NO DSN required!!
		m_DB.Open(NULL,
			FALSE,
			FALSE,
			"ODBC;DRIVER={Microsoft Access Driver (*.mdb)};DBQ=datadb.mdb;PWD=zhaosheng123;UID=admin;");

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

//����ϵͳ������Ϣ
void CManagerApp::LoadConfigInfor()
{
	CTime tm;
	tm = CTime::GetCurrentTime();
	try{
			ifstream ifile;
			ifile.open("config_infor.txt");
			string str;
			CString s;
			int num, i;
			if (ifile)
			{
				ifile >> str >> num;
				//s.Format("%s %d", StringToCString(str), num);
				//AfxMessageBox(s);
				ifile >> str >> i;
				if (i == 1&&tm.GetDayOfWeek() == 2)
					num++;
				theApp.m_nowWeek = num;
				//s.Format("%s %d", StringToCString(str), num);
				//AfxMessageBox(s);

			}
			else AfxMessageBox("����������Ϣʧ������ϵ����Ա��");
			ifile.close();
		}
		catch (...)
		{
			AfxMessageBox("����������Ϣʧ������ϵ����Ա��");
		}
}

//���浱ǰϵͳ��������Ϣ
void CManagerApp::SaveConfigInfor()
{
	try{
		fstream ifile;
		ifile.open("config_infor.txt");
		int i=0;
		if (ifile)
		{
			CTime tm;
			tm = CTime::GetCurrentTime();
			if (tm.GetDayOfWeek() == 2)//����1
				i=0;
			else i = 1;
			ifile << "//���ļ�Ϊϵͳ�������ص�������Ϣ�ļ�,��ȡ�ļ�ʱ�̶�Ϊһ��ע�ͣ�һ������" << endl
				<<theApp.m_nowWeek<<endl
				<<"//�����Ƿ��һ"<<endl<<i;

		}
		else AfxMessageBox("����������Ϣʧ��,����ϵ����Ա��");
		ifile.close();
	}
	catch (...)
	{
		AfxMessageBox("����������Ϣʧ�ܣ�����ϵ����Ա��");
	}
}
string CManagerApp::CStringToString(const CString &cstr)
{
	string tempstr(CString::StringLength(cstr), '0');
	for (int i = 0; i < CString::StringLength(cstr); i++)
	{
		tempstr[i] = (char)cstr[i];
	}
	return tempstr;
}
CString CManagerApp::StringToCString(const string &str)
{
	CString tempcstr(str.c_str());
	return tempcstr;
}
