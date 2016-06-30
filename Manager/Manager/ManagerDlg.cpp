
// ManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "ManagerDlg.h"
#include "afxdialogex.h"
#include"person.h"
#include "MainFramDlg.h"
#include"start_work.h"
#include<GL\glut.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define ABS(x) ((x)<0 ? -(x) : (x)>0 ? (x) : 0)

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CManagerDlg �Ի���



CManagerDlg::CManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManagerDlg::IDD, pParent)
	, m_strPasswd(_T(""))
	, m_strUserName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDL_PASSWD, m_strPasswd);
	DDX_Control(pDX, IDC_CBL_USER, m_ctrUser);
	DDX_CBString(pDX, IDC_CBL_USER, m_strUserName);
}

BEGIN_MESSAGE_MAP(CManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_CBL_USER, &CManagerDlg::OnCbnSelchangeCblUser)
	ON_BN_CLICKED(IDC_BTL_LOGIN, &CManagerDlg::OnBnClickedBtlLogin)
	ON_WM_CLOSE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CHAR()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CManagerDlg ��Ϣ�������

BOOL CManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	InitCtrl();//�Զ���ĳ�ʼ���ؼ�
	CheckSign();

	InitOpenGL();//
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	static BOOL     bBusy = FALSE;
	if (bBusy) 	return;
	bBusy = TRUE;
	glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	mydraw();
	glFinish();
	SwapBuffers(wglGetCurrentDC());
	bBusy = FALSE;
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CManagerDlg::InitOpenGL()
{
	my_pDC = NULL;
	mytbar = FALSE;
	mysbar = FALSE;

	lkey = TRUE;
	jd = 0.0f;
	bh[0][0] = 1.0f;
	bh[0][1] = 0.1f;
	bh[1][0] = 46.0f;
	bh[1][1] = 30.0f;
	bh[0][2] = 0.0f;
	bh[1][2] = 30.0f;
	for (int i = 0; i<8; i++){
		bh[i + 2][0] = 1.0f*(rand() - rand()) / RAND_MAX;
		bh[i + 2][2] = 1.0f*rand() / RAND_MAX;
	};
	myfirst();
	mylist();

	//SetTimer(1, 120, NULL);
	CRect rect;
	GetClientRect(&rect);
	int cy = rect.Height();
	int cx = rect.Width();
	if (cy > 0)
	{
		my_oldRect.right = cx;
		my_oldRect.bottom = cy;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1.0, 1.0, -1.0*cy / cx, 1.0*cy / cx, 5.0, 40.0);
		glViewport(0, 0, cx, cy);
	}
	RedrawWindow();
	Invalidate(FALSE);

}
void CManagerDlg::InitCtrl()
{
	while (m_ctrUser.GetCount()>0)
	{
		m_ctrUser.DeleteString(0);
	}
	try
	{
		//Connect to the database
		Cperson recordset(&theApp.m_DB);
		CString strSQL;

		strSQL = "select * from person";
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			//if (!recordset.Open(CRecordset::dynaset,strSQL))
		{
			MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
			return;
		}

		while (!recordset.IsEOF())
		{
			m_ctrUser.AddString(recordset.m_pname);
			recordset.MoveNext();
		}

		
		recordset.Close();
		UpdateData(FALSE);
		m_ctrUser.SetCurSel(1);
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

void CManagerDlg::OnCbnSelchangeCblUser()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iPos = m_ctrUser.GetCurSel();//��ǰѡ�е��С�
	m_ctrUser.SetCurSel(iPos);//���õ�n������Ϊ��ʾ�����ݡ�
	m_ctrUser.GetLBText(iPos, m_strUserName);
}


void CManagerDlg::OnBnClickedBtlLogin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	try
	{
		//Connect to the database
		Cperson recordset(&theApp.m_DB);
		CString strSQL;
		UpdateData(TRUE);

		if (m_strUserName.IsEmpty())
		{
			MessageBox("�������û�����", MB_OK);
			m_ctrUser.SetFocus();
			return;
		}
		//��������Ƿ�����
		if (m_strPasswd.IsEmpty())
		{
			MessageBox("���������룡", MB_OK);
			return;
		}

		strSQL.Format("select * from person where pname='%s' AND passwd='%s'",
			m_strUserName, m_strPasswd);

		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
			return;
		}
		if (recordset.GetRecordCount() == 0)
		{
			recordset.Close();
			MessageBox("�û���������������������룡", MB_OK);
			m_strPasswd = "";
			m_ctrUser.SetFocus();
			UpdateData(FALSE);
		}
		else//�û�����������֤��ȷ
		{
			//����½�û���Ϣ���浽app����
			theApp.m_strUserName=recordset.m_pname;
			theApp.m_strPasswd = recordset.m_passwd;
			theApp.m_academy = recordset.m_academy;
			theApp.m_major = recordset.m_major;
			theApp.m_sex = recordset.m_sex;
			theApp.m_introduction = recordset.m_introduction;
			theApp.m_phone = recordset.m_telephone;
			theApp.m_post = recordset.m_post;
			theApp.m_joinTime = recordset.m_join_date;
			theApp.m_department = recordset.m_department;
			theApp.m_privilege = recordset.m_privilege;
			theApp.m_id = recordset.m_id;

			//MessageBox(recordset.m_passwd+recordset.m_pname, MB_OK);

			recordset.Close();
			ShowWindow(SW_HIDE);//���ص�¼�Ի�����ʾ���Ի���
			 
			CMainFramDlg maindlg;
			INT_PTR nResponse = maindlg.DoModal();
			if (nResponse == IDOK)
			{
				InitCtrl();//���µ�¼���ڵ��˺�����
				m_strPasswd = "";
				m_ctrUser.SetFocus();

				UpdateData(FALSE);
				ShowWindow(SW_SHOW);//maindlg�е��ע����ť���˻ص�½�Ի���
			}
			
			else CDialogEx::OnOK();//�˳�����
		}
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


void CManagerDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CTime tm;
	tm = CTime::GetCurrentTime();
	bool sys = false;
	//�˴�����û�п����ļ�ʱ�Ͷ���ʱ������
	if ((tm.GetHour() == 11 || tm.GetHour() == 17) && tm.GetMinute() > 50)
		sys = true;
	if (tm.GetHour() == 12 || tm.GetHour() == 18)
		sys = true;

	if (sys)
	{
		try
		{
			//Connect to the database
			CString strSQL;

			CSignSet ss(&theApp.m_DB);
			strSQL.Format("select * from start_work where is_lock=0");
			if (!ss.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			{
				MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
				return;
			}
			if (!ss.IsEOF())//�ҵ��ϰ�ǩ����Ϣ��
			{
				Cperson rs(&theApp.m_DB);
				strSQL.Format("select * from person where pname='%s'", ss.m_signer);
				if (!rs.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
				{
					MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
					return;
				}
				CString sex;
				CString str;
				if (!rs.IsEOF())
				{
					if (rs.m_sex)sex = "��";
					else sex = "��";
				}
				
				str.Format("%s ��û��ǩ�°࣬�ǵ�����%sӴ~~~", ss.m_signer, sex);
				MessageBox(str, "���ݿ����", MB_OK);
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
	CDialogEx::OnClose();
}


void CManagerDlg::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���
	OnClose();
	CDialogEx::OnCancel();
}

//����ϰ�ǩ���������������������ݼ�����
void CManagerDlg::CheckSign()
{
	try
	{
		//Connect to the database
		//��start_work �������ȫ����ʾ
		CString strSQL;
		CSignSet ss(&theApp.m_DB);
		strSQL = "select * from start_work";
		if (!ss.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			//if (!recordset.Open(CRecordset::dynaset,strSQL))
		{
			MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
			return;
		}
		CTime tm;
		tm = CTime::GetCurrentTime();
		while (!ss.IsEOF())
		{
			bool sys = false;
			if (ss.m_start_time.GetDay() != tm.GetDay())sys = true;
			if (tm.GetHour() - ss.m_start_time.GetHour() > 4)sys = true;
			if (sys)
			{
				CString update;
				update.Format("update start_work set is_lock =%d where start_id =%d", 
					1,ss.m_start_id);
				theApp.m_DB.ExecuteSQL(update);
			}
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


void CManagerDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	char keychar;
	HCURSOR mousecusor;
	keychar = char(nChar);
	if (keychar == 'B')
	{
		//��ȡϵͳ���
		mousecusor = AfxGetApp()->LoadStandardCursor(IDC_IBEAM);
		//IDC_SIZENS IDC_CROSS
		SetCursor(mousecusor);
	}
	if (keychar == 'A')
	{
		//��ȡϵͳ���
		mousecusor = AfxGetApp()->LoadStandardCursor(IDC_SIZENS);
		//IDC_SIZENS IDC_CROSS
		SetCursor(mousecusor);
	}
	if (keychar == 'C')
	{
		//��ȡϵͳ���
		mousecusor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
		//IDC_SIZENS IDC_CROSS
		SetCursor(mousecusor);
	}
	MessageBox("keydown!", "key", MB_OK);
	//CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CManagerDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	MessageBox("keyup!", "���ݿ����", MB_OK);
	//CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CManagerDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	MessageBox("onchar!", "���ݿ����", MB_OK);
	//CDialogEx::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CManagerDlg::mypixelformat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	int pixelformat;

	if ((pixelformat = ChoosePixelFormat(my_pDC->GetSafeHdc(), &pfd)) == 0)
	{
		MessageBox("ChoosePixelFormat failed");
		return FALSE;
	}

	if (SetPixelFormat(my_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		MessageBox("SetPixelFormat failed");
		return FALSE;
	}

	return TRUE;


}

void CManagerDlg::mydraw()
{
	glTranslatef(0.0f, 0.0f, -6.0f);

	myfog();
	glPushMatrix();
	glTranslatef(bh[0][0], bh[0][1], -26.5f);
	glRotated(bh[1][0], 1.0, 0.0, 0.0);
	glRotated(bh[1][1], 0.0, 0.0, 1.0);
	moon();
	glPopMatrix();
	glRotated(12, 1.0, 0.0, 0.0);

	int j = 1;
	for (int i = 0; i<4; i++){
		glPushMatrix();
		glTranslatef(bh[i + 2][0], -0.9f, -9.0f*bh[i + 2][2] - 0.5f);
		glScalef(1.0f - bh[i + 2][2], 1.0f - bh[i + 2][2], 1.0f - bh[i + 2][2]);
		hehuac(j);
		glRotated(180, 1.0, 0.0, 0.0);
		hehuac(j);
		j = !j;
		glPopMatrix();
		glPushMatrix();
		glTranslatef(bh[i + 6][0] * 1.2f, -0.9f, -18.0f*bh[i + 6][2] - 1.0f);
		glScalef(1.2f - bh[i + 6][2], 1.2f - bh[i + 6][2], 1.2f - bh[i + 6][2]);
		glCallList(1);
		glRotated(180, 1.0, 0.0, 0.0);
		glCallList(1);
		glPopMatrix();
	};

	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.2f, 0.2f, 0.2f, 0.5f);
	glBegin(GL_QUAD_STRIP);
	glVertex3f(10.0f, -0.901f, -40.0f);
	glVertex3f(-20.0f, -0.901f, -40.0f);
	glVertex3f(1.2f, -0.901f, 1.2f);
	glVertex3f(-1.2f, -0.901f, 1.2f);
	glEnd();
	glDisable(GL_BLEND);
	glPopMatrix();

	glDisable(GL_FOG);
}

void CManagerDlg::myfirst()
{
	PIXELFORMATDESCRIPTOR pfd;
	int         n;
	HGLRC		hrc;

	my_pDC = new CClientDC(this);

	ASSERT(my_pDC != NULL);

	if (!mypixelformat())
		return;
	n = ::GetPixelFormat(my_pDC->GetSafeHdc());
	::DescribePixelFormat(my_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);


	hrc = wglCreateContext(my_pDC->GetSafeHdc());
	wglMakeCurrent(my_pDC->GetSafeHdc(), hrc);

	GetClientRect(&my_oldRect);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	UpdateData(FALSE);
}

void CManagerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������

	KillTimer(1);
	HGLRC	hrc;

	hrc = ::wglGetCurrentContext();

	::wglMakeCurrent(NULL, NULL);

	if (hrc)
		::wglDeleteContext(hrc);

	if (my_pDC)
		delete my_pDC;
}


void CManagerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 1){
		if (bh[0][0] <= -1.8f){
			bh[0][0] = 1.3f;
			bh[0][1] = -0.1f;
			bh[1][0] = 40.0f;
			bh[1][0] = 32.0f;
		}
		else{
			bh[0][0] = bh[0][0] - 0.005f;
			bh[0][1] = bh[0][1] + 0.001f;
			bh[1][0] = bh[1][0] - 0.5f;
			bh[1][0] = bh[1][0] - 0.1f;
		};
		if (bh[0][2] >= 50.0f){ bh[0][2] = -50.0f; }
		else{ bh[0][2] = bh[0][2] + 1.0f; };
		if (bh[1][2] >= 50.0f){ bh[1][2] = -50.0f; }
		else{ bh[1][2] = bh[1][2] + 1.0f; };

		if (ABS(jd) >= 6.1f){ jd = -6.0f; }
		else{ jd = jd + 0.05f; };
		Invalidate(FALSE);
	};
	CDialogEx::OnTimer(nIDEvent);
}

void CManagerDlg::moon()
{

	float rx = 1.0f;
	float ange1 = 0.0f;
	glPushMatrix();
	glScalef(0.26f, 0.26f, 0.26f);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (float i = 0; i<20; i++){
		glBegin(GL_QUAD_STRIP);
		for (float j = 0; j<363; j++){
			rx = cosf(3.1416f / 2.0f - 3.1416f / 20 * i);
			glColor3f(
				0.5f + 0.000008f*i*i*i*i*i,
				0.5f + 0.000008f*i*i*i*i*i,
				1.0f + 0.000005f*i*i*i*i*i
				);
			glVertex3f(rx*cosf(ange1),
				sinf(3.1416f / 2.0f - 3.1416f / 20 * i),
				-rx*sinf(ange1));
			rx = cosf(3.1416f / 2.0f - 3.1416f / 20 * (i + 1));
			glColor3f(
				0.5f + 0.000008f*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1),
				0.5f + 0.000008f*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1),
				1.0f + 0.000005f*(i + 1)*(i + 1)*(i + 1)*(i + 1)*(i + 1)
				);
			glVertex3f(rx*cosf(ange1),
				sinf(3.1416f / 2.0f - 3.1416f / 20 * (i + 1)),
				-rx*sinf(ange1));
			ange1 = 3.1416f / 180.0f*j;
		};
		glEnd();
	};
	glPopMatrix();

}

void CManagerDlg::heiye()
{
	glPushMatrix();
	glScalef(0.4f, 0.05f, 0.4f);
	float rx = 1.0f;
	float m = 0.0f;

	for (float i = 0; i<36; i++){
		glBegin(GL_QUAD_STRIP);
		for (float j = 0; j<(8 + ABS(m)); j = j + 0.01f){
			rx = 1.0f + 0.1f*(sinf(3.1416f / 9.0f*j * 2));
			glColor3f(0.0f,
				4.5f*ABS(cosf(3.1416f / 18.0f*i * 4)),
				0.0f
				);
			glVertex3f(rx*cosf(3.1416f / 18.0f*i)*cosf(3.1416f / 2.0f - 3.1416f / 18.0f*j),
				rx*sinf(3.1416f / 2.0f - 3.1416f / 18.0f*j),
				rx*sinf(3.1416f / 18.0f*i)*cosf(3.1416f / 2.0f - 3.1416f / 18.0f*j));
			glColor3f(0.0f,
				4.5f*ABS(cosf(3.1416f / 18.0f*(i + 1) * 4)),
				0.0f
				);
			glVertex3f(rx*cosf(3.1416f / 18.0f*(i + 1))*cosf(3.1416f / 2.0f - 3.1416f / 18.0f*j),
				rx*sinf(3.1416f / 2.0f - 3.1416f / 18.0f*j),
				rx*sinf(3.1416f / 18.0f*(i + 1))*cosf(3.1416f / 2.0f - 3.1416f / 18.0f*j));
		};
		if (ABS(m) >= 1.8f){
			m = -1.8f;
		};
		m = m + 0.1f;
		glEnd();
	};
	glPopMatrix();
}

void CManagerDlg::hehua()
{
	glPushMatrix();
	glRotated(40, 0.0, 1.0, 0.0);
	glTranslatef(0.0f, 0.1f, 0.0f);
	glScalef(0.06f, 0.08f, 0.06f);
	for (float i = 0; i<8; i++){
		glBegin(GL_QUAD_STRIP);
		for (float j = 0; j<16; j++){
			glColor3f(sinf(3.1416f / 2.0f - 3.1416f / 36.0f*j) + (sinf(3.1416f / 144.0f*i)),
				0.0f,
				cosf(3.1416f / 2.0f - 3.1416f / 12.0f*j)
				);
			glVertex3f(cosf(3.1416f / 18.0f*i)*cosf(3.1416f / 2.0f - 3.1416f / 18.0f*j),
				sinf(3.1416f / 2.0f - 3.1416f / 18.0f*j),
				sinf(3.1416f / 18.0f*i)*cosf(3.1416f / 2.0f - 3.1416f / 18.0f*j));
			glColor3f(sinf(3.1416f / 2.0f - 3.1416f / 36.0f*j) + (sinf(3.1416f / 144.0f*i)),
				0.0f,
				cosf(3.1416f / 2.0f - 3.1416f / 12.0f*j)
				);
			glVertex3f(cosf(3.1416f / 18.0f*(i + 1))*cosf(3.1416f / 2.0f - 3.1416f / 18.0f*j),
				sinf(3.1416f / 2.0f - 3.1416f / 18.0f*j),
				sinf(3.1416f / 18.0f*(i + 1))*cosf(3.1416f / 2.0f - 3.1416f / 18.0f*j));
		};
		glEnd();
	};
	glPopMatrix();
}

void CManagerDlg::hehuac(int k)
{
	for (int i = 0; i<8; i++){
		glPushMatrix();
		glRotated(45 * i, 0.0, 1.0, 0.0);
		if (k == 0){ glRotated(-ABS(bh[0][2]), 0.0, 0.0, 1.0); };
		if (k == 1){ glRotated(-ABS(bh[1][2]), 0.0, 0.0, 1.0); };
		glCallList(2);
		glPopMatrix();
	};
}

void CManagerDlg::mylist()
{
	listi = glGenLists(2);
	glListBase(listi);

	glNewList(listi, GL_COMPILE);
	heiye();
	glEndList();
	glNewList(listi + 1, GL_COMPILE);
	hehua();
	glEndList();

}

void CManagerDlg::myfog()
{
	glEnable(GL_FOG);
	GLfloat fogC[4] = { 0.5f, 0.5f, 1.0f, 1.0f };
	glFogfv(GL_FOG_COLOR, fogC);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_DENSITY, 0.025f*ABS(jd));
	glFogf(GL_FOG_START, 7.0);
	glFogf(GL_FOG_END, 9.0);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
}


void CManagerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (cy > 0)
	{
		/*CRect rect;
		GetClientRect(&rect);
		CString str;
		str.Format("cx:%d,cy:%d;width%d,height:%d",
		cx, cy, rect.Width(), rect.Height());*/
		//AfxMessageBox(str);��һ����

		my_oldRect.right = cx;
		my_oldRect.bottom = cy;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1.0, 1.0, -1.0*cy / cx, 1.0*cy / cx, 5.0, 40.0);
		glViewport(0, 0, cx, cy);
	}
	RedrawWindow();
	// TODO:  �ڴ˴������Ϣ����������
}


void CManagerDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	OnBnClickedBtlLogin();
	//CDialogEx::OnOK();
}
