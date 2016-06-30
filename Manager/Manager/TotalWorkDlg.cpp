// TotalWorkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "TotalWorkDlg.h"
#include "afxdialogex.h"
#include"course_table.h"
#include"excel9.h"
// CTotalWorkDlg 对话框

IMPLEMENT_DYNAMIC(CTotalWorkDlg, CDialogEx)

CTotalWorkDlg::CTotalWorkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTotalWorkDlg::IDD, pParent)
	, m_strComb(_T(""))
	, m_Monday12(_T(""))
	, m_Monday34(_T(""))
	, m_Monday56(_T(""))
	, m_Monday78(_T(""))
	, m_Tuesday12(_T(""))
	, m_Tuesday34(_T(""))
	, m_Tuesday56(_T(""))
	, m_Tuesday78(_T(""))
	, m_Wednesday12(_T(""))
	, m_Wednesday34(_T(""))
	, m_Wednesday56(_T(""))
	, m_Wednesday78(_T(""))
	, m_Thursday12(_T(""))
	, m_Thursday34(_T(""))
	, m_Thursday56(_T(""))
	, m_Thursday78(_T(""))
	, m_Friday12(_T(""))
	, m_Friday34(_T(""))
	, m_Friday56(_T(""))
	, m_Friday78(_T(""))
	, m_Saturday12(_T(""))
	, m_Saturday34(_T(""))
	, m_Saturday56(_T(""))
	, m_Saturday78(_T(""))
	, m_Sunday12(_T(""))
	, m_Sunday34(_T(""))
	, m_Sunday56(_T(""))
	, m_Sunday78(_T(""))
	, m_strExtra(_T(""))
{

}

CTotalWorkDlg::~CTotalWorkDlg()
{
}

void CTotalWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlComb);
	DDX_CBString(pDX, IDC_COMBO1, m_strComb);
	DDX_Text(pDX, IDC_EDIT_112, m_Monday12);
	DDX_Text(pDX, IDC_EDIT_134, m_Monday34);
	DDX_Text(pDX, IDC_EDIT_156, m_Monday56);
	DDX_Text(pDX, IDC_EDIT_178, m_Monday78);
	DDX_Text(pDX, IDC_EDIT_212, m_Tuesday12);
	DDX_Text(pDX, IDC_EDIT_234, m_Tuesday34);
	DDX_Text(pDX, IDC_EDIT_256, m_Tuesday56);
	DDX_Text(pDX, IDC_EDIT_278, m_Tuesday78);
	DDX_Text(pDX, IDC_EDIT_312, m_Wednesday12);
	DDX_Text(pDX, IDC_EDIT_334, m_Wednesday34);
	DDX_Text(pDX, IDC_EDIT_356, m_Wednesday56);
	DDX_Text(pDX, IDC_EDIT_378, m_Wednesday78);
	DDX_Text(pDX, IDC_EDIT_412, m_Thursday12);
	//  DDX_Text(pDX, IDC_EDIT_434, m_Thursday56);
	DDX_Text(pDX, IDC_EDIT_434, m_Thursday34);
	DDX_Text(pDX, IDC_EDIT_456, m_Thursday56);
	DDX_Text(pDX, IDC_EDIT_478, m_Thursday78);
	//  DDX_Control(pDX, IDC_EDIT_512, m_Sunday12);
	DDX_Text(pDX, IDC_EDIT_512, m_Friday12);
	DDX_Text(pDX, IDC_EDIT_534, m_Friday34);
	DDX_Text(pDX, IDC_EDIT_556, m_Friday56);
	DDX_Text(pDX, IDC_EDIT_578, m_Friday78);
	DDX_Text(pDX, IDC_EDIT_612, m_Saturday12);
	DDX_Text(pDX, IDC_EDIT_634, m_Saturday34);
	DDX_Text(pDX, IDC_EDIT_656, m_Saturday56);
	DDX_Text(pDX, IDC_EDIT_678, m_Saturday78);
	DDX_Text(pDX, IDC_EDIT_712, m_Sunday12);
	DDX_Text(pDX, IDC_EDIT_734, m_Sunday34);
	DDX_Text(pDX, IDC_EDIT_756, m_Sunday56);
	DDX_Text(pDX, IDC_EDIT_778, m_Sunday78);
	DDX_Text(pDX, IDC_EDIT1, m_strExtra);
}


BEGIN_MESSAGE_MAP(CTotalWorkDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTotalWorkDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CTotalWorkDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTotalWorkDlg 消息处理程序


BOOL CTotalWorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (int i = 0; i < 24; i++)
	{
		CString str;
		str.Format("第%d周", i);
		m_ctrlComb.AddString(str);
	}
	m_intWeek = theApp.m_nowWeek;
	m_strComb.Format("第%d周", m_intWeek);
	ShowSheet();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CTotalWorkDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlComb.GetCurSel();//当前选中的行。
	m_ctrlComb.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlComb.GetLBText(iPos, m_strComb);
	m_intWeek = iPos;//box从0开始，周数也是从0开始
	ShowSheet();
	UpdateData(FALSE);
}
void CTotalWorkDlg::ShowSheet()//显示空余时间表
{
	m_Monday12 = "";
	m_Monday34 = "";
	m_Monday56 = "";
	m_Monday78 = "";
	m_Tuesday12 = "";
	m_Tuesday34 = "";
	m_Tuesday56 = "";
	m_Tuesday78 = "";
	m_Wednesday12 = "";
	m_Wednesday34 = "";
	m_Wednesday56 = "";
	m_Wednesday78 = "";
	m_Thursday12 = "";
	m_Thursday34 = "";
	m_Thursday56 = "";
	m_Thursday78 = "";
	m_Friday12 = "";
	m_Friday34 = "";
	m_Friday56 = "";
	m_Friday78 = "";
	m_Saturday12 = "";
	m_Saturday34 = "";
	m_Saturday56 = "";
	m_Saturday78 = "";
	m_Sunday12 = "";
	m_Sunday34 = "";
	m_Sunday56 = "";
	m_Sunday78 = "";

	m_strExtra = "";

	try
	{
		//Connect to the database
		CCourseSet recordset(&theApp.m_DB);
		CString strSQL;

		strSQL.Format( "select * from course_table where week_number=%d",m_intWeek);
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}

		while (!recordset.IsEOF())
		{
			//如果该时间有空，则加入到空余时间表
			if (recordset.m_Monday12)m_Monday12 += recordset.m_pname + ",";
			if (recordset.m_Monday34)m_Monday34 += recordset.m_pname + ",";
			if (recordset.m_Monday56)m_Monday56 += recordset.m_pname + ",";
			if (recordset.m_Monday78)m_Monday78 += recordset.m_pname + ",";
			if (recordset.m_Tuesday12)m_Tuesday12 += recordset.m_pname + ",";
			if (recordset.m_Tuesday34)m_Tuesday34 += recordset.m_pname + ",";
			if (recordset.m_Tuesday56)m_Tuesday56 += recordset.m_pname + ",";
			if (recordset.m_Tuesday78)m_Tuesday78 += recordset.m_pname + ",";
			if (recordset.m_Wednesday12)m_Wednesday12 += recordset.m_pname + ",";
			if (recordset.m_Wednesday34)m_Wednesday34 += recordset.m_pname + ",";
			if (recordset.m_Wednesday56)m_Wednesday56 += recordset.m_pname + ",";
			if (recordset.m_Wednesday78)m_Wednesday78 += recordset.m_pname + ",";
			if (recordset.m_Thursday12)m_Thursday12 += recordset.m_pname + ",";
			if (recordset.m_Thursday34)m_Thursday34 += recordset.m_pname + ",";
			if (recordset.m_Thursday56)m_Thursday78 += recordset.m_pname + ",";
			if (recordset.m_Thursday78)m_Thursday78 += recordset.m_pname + ",";
			if (recordset.m_Friday12)m_Friday12 += recordset.m_pname + ",";
			if (recordset.m_Friday34)m_Friday34 += recordset.m_pname + ",";
			if (recordset.m_Friday56)m_Friday56 += recordset.m_pname + ",";
			if (recordset.m_Friday78)m_Friday78 += recordset.m_pname + ",";
			if (recordset.m_Saturday12)m_Saturday12 += recordset.m_pname + ",";
			if (recordset.m_Saturday34)m_Saturday34 += recordset.m_pname + ",";
			if (recordset.m_Saturday56)m_Saturday56 += recordset.m_pname + ",";
			if (recordset.m_Saturday78)m_Saturday78 += recordset.m_pname + ",";
			if (recordset.m_Sunday12)m_Sunday12 += recordset.m_pname + ",";
			if (recordset.m_Sunday34)m_Sunday34 += recordset.m_pname + ",";
			if (recordset.m_Sunday56)m_Sunday56 += recordset.m_pname + ",";
			if (recordset.m_Sunday78)m_Sunday78 += recordset.m_pname + ",";

			if (recordset.m_extra_infor.GetLength() > 0)
			{
				m_strExtra += recordset.m_pname + ":" + recordset.m_extra_infor + ",";
			}
			recordset.MoveNext();

		}
		recordset.Close();
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
	UpdateData(FALSE);
}

void CTotalWorkDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

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

	//获得坐标为（C，1）单元格
	range = sheet.GetRange(COleVariant(_T("C1")), COleVariant(_T("C1")));
	//设置单元格内容
	CString str;
	str.Format("招办第%d周空余时间表", m_intWeek);
	range.SetValue(COleVariant(str));
	//选择整列，并设置宽度为自适应
	//cols =range.GetColumns();
	cols = range.GetEntireColumn();
	cols.AutoFit();
	
	//列标题
	range = sheet.GetRange(COleVariant(_T("A2")), COleVariant(_T("A2")));
	range.SetValue(COleVariant(_T("时间\\星期")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("B2")), COleVariant(_T("B2")));
	range.SetValue(COleVariant(_T("星期一")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("C2")), COleVariant(_T("C2")));
	range.SetValue(COleVariant(_T("星期二")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("D2")), COleVariant(_T("D2")));
	range.SetValue(COleVariant(_T("星期三")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("E2")), COleVariant(_T("E2")));
	range.SetValue(COleVariant(_T("星期四")));

	range = sheet.GetRange(COleVariant(_T("F2")), COleVariant(_T("F2")));
	range.SetValue(COleVariant(_T("星期五")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("G2")), COleVariant(_T("G2")));
	range.SetValue(COleVariant(_T("星期六")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("H2")), COleVariant(_T("H2")));
	range.SetValue(COleVariant(_T("星期天")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	//行标题
	range = sheet.GetRange(COleVariant(_T("A3")), COleVariant(_T("A3")));
	range.SetValue(COleVariant(_T("第12节")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("A4")), COleVariant(_T("A4")));
	range.SetValue(COleVariant(_T("第34节")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("A5")), COleVariant(_T("A5")));
	range.SetValue(COleVariant(_T("第56节")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("A6")), COleVariant(_T("A6")));
	range.SetValue(COleVariant(_T("第78节")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	//星期一
	range = sheet.GetRange(COleVariant(_T("B3")), COleVariant(_T("B3")));
	range.SetValue(COleVariant(_T(m_Monday12)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("B4")), COleVariant(_T("B4")));
	range.SetValue(COleVariant(_T(m_Monday34)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("B5")), COleVariant(_T("B5")));
	range.SetValue(COleVariant(_T(m_Monday56)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("B6")), COleVariant(_T("B6")));
	range.SetValue(COleVariant(_T(m_Monday78)));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	//星期二
	range = sheet.GetRange(COleVariant(_T("C3")), COleVariant(_T("C3")));
	range.SetValue(COleVariant(_T(m_Tuesday12)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("C4")), COleVariant(_T("C4")));
	range.SetValue(COleVariant(_T(m_Tuesday34)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("C5")), COleVariant(_T("C5")));
	range.SetValue(COleVariant(_T(m_Tuesday56)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("C6")), COleVariant(_T("C6")));
	range.SetValue(COleVariant(_T(m_Thursday78)));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	//星期三
	range = sheet.GetRange(COleVariant(_T("D3")), COleVariant(_T("D3")));
	range.SetValue(COleVariant(_T(m_Wednesday12)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("D4")), COleVariant(_T("D4")));
	range.SetValue(COleVariant(_T(m_Wednesday34)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("D5")), COleVariant(_T("D5")));
	range.SetValue(COleVariant(_T(m_Wednesday56)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("D6")), COleVariant(_T("D6")));
	range.SetValue(COleVariant(_T(m_Wednesday78)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	//星期四
	range = sheet.GetRange(COleVariant(_T("E3")), COleVariant(_T("E3")));
	range.SetValue(COleVariant(_T(m_Thursday12)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("E4")), COleVariant(_T("E4")));
	range.SetValue(COleVariant(_T(m_Thursday34)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("E5")), COleVariant(_T("E5")));
	range.SetValue(COleVariant(_T(m_Thursday56)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("E6")), COleVariant(_T("E6")));
	range.SetValue(COleVariant(_T(m_Thursday78)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	//星期五
	range = sheet.GetRange(COleVariant(_T("F3")), COleVariant(_T("F3")));
	range.SetValue(COleVariant(_T(m_Friday12)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("F4")), COleVariant(_T("F4")));
	range.SetValue(COleVariant(_T(m_Friday34)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("F5")), COleVariant(_T("F5")));
	range.SetValue(COleVariant(_T(m_Friday56)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("F6")), COleVariant(_T("F6")));
	range.SetValue(COleVariant(_T(m_Friday78)));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	//星期六
	range = sheet.GetRange(COleVariant(_T("G3")), COleVariant(_T("G3")));
	range.SetValue(COleVariant(_T(m_Saturday12)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("G4")), COleVariant(_T("G4")));
	range.SetValue(COleVariant(_T(m_Saturday34)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("G5")), COleVariant(_T("G5")));
	range.SetValue(COleVariant(_T(m_Saturday56)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("G6")), COleVariant(_T("G6")));
	range.SetValue(COleVariant(_T(m_Saturday78)));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	//星期天
	range = sheet.GetRange(COleVariant(_T("H3")), COleVariant(_T("H3")));
	range.SetValue(COleVariant(_T(m_Sunday12)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("H4")), COleVariant(_T("H4")));
	range.SetValue(COleVariant(_T(m_Sunday34)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("H5")), COleVariant(_T("H5")));
	range.SetValue(COleVariant(_T(m_Sunday56)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("H6")), COleVariant(_T("H6")));
	range.SetValue(COleVariant(_T(m_Sunday78)));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("C7")), COleVariant(_T("C7")));
	range.SetValue(COleVariant(_T(m_strExtra)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
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

	str.Format("成功导出数据记录！");
	MessageBoxA(str, "导出成功",
		MB_ICONEXCLAMATION | MB_OK);
}
