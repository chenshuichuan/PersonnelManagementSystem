
// Manager.cpp : 定义应用程序的类行为。
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


// CManagerApp 构造

CManagerApp::CManagerApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CManagerApp 对象
CManagerApp theApp;


// CManagerApp 初始化

BOOL CManagerApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	InitializeSkin("XPCorona.ssk");
	
	LoadConfigInfor();//
	OpenDB();

	CManagerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  在此放置处理何时用
		//  “取消”来关闭对话框的代码
		//dlg.OnClose();//检查是否有人未签下班，提醒
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	m_DB.Close();//关闭数据库
	SaveConfigInfor();
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

//打开数据库
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

//加载系统配置信息
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
			else AfxMessageBox("加载配置信息失败请联系管理员！");
			ifile.close();
		}
		catch (...)
		{
			AfxMessageBox("加载配置信息失败请联系管理员！");
		}
}

//保存当前系统的配置信息
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
			if (tm.GetDayOfWeek() == 2)//星期1
				i=0;
			else i = 1;
			ifile << "//此文件为系统启动加载的配置信息文件,读取文件时固定为一行注释，一行数据" << endl
				<<theApp.m_nowWeek<<endl
				<<"//周数是否加一"<<endl<<i;

		}
		else AfxMessageBox("保存配置信息失败,请联系管理员！");
		ifile.close();
	}
	catch (...)
	{
		AfxMessageBox("保存配置信息失败，请联系管理员！");
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
