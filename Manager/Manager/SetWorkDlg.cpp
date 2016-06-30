// SetWorkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Manager.h"
#include "SetWorkDlg.h"
#include "afxdialogex.h"
#include"attend_table.h"
#include"course_table.h"
#include"excel9.h"

// CSetWorkDlg 对话框

IMPLEMENT_DYNAMIC(CSetWorkDlg, CDialogEx)

CSetWorkDlg::CSetWorkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetWorkDlg::IDD, pParent)
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
	, m_strWeek(_T(""))
	, m_strSetInfor(_T(""))
{

}

CSetWorkDlg::~CSetWorkDlg()
{
}

void CSetWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ctrlWeek);
	DDX_Text(pDX, IDC_EDIT_S112, m_Monday12);
	DDX_Text(pDX, IDC_EDIT_S134, m_Monday34);
	DDX_Text(pDX, IDC_EDIT_S156, m_Monday56);
	DDX_Text(pDX, IDC_EDIT_S178, m_Monday78);
	DDX_Text(pDX, IDC_EDIT_S212, m_Tuesday12);
	DDX_Text(pDX, IDC_EDIT_S234, m_Tuesday34);
	DDX_Text(pDX, IDC_EDIT_S256, m_Tuesday56);
	DDX_Text(pDX, IDC_EDIT_S278, m_Tuesday78);
	DDX_Text(pDX, IDC_EDIT_S312, m_Wednesday12);
	DDX_Text(pDX, IDC_EDIT_S334, m_Wednesday34);
	DDX_Text(pDX, IDC_EDIT_S356, m_Wednesday56);
	DDX_Text(pDX, IDC_EDIT_S378, m_Wednesday78);
	DDX_Text(pDX, IDC_EDIT_S412, m_Thursday12);
	//  DDX_Text(pDX, IDC_EDIT_434, m_Thursday56);
	DDX_Text(pDX, IDC_EDIT_S434, m_Thursday34);
	DDX_Text(pDX, IDC_EDIT_S456, m_Thursday56);
	DDX_Text(pDX, IDC_EDIT_S478, m_Thursday78);
	//  DDX_Control(pDX, IDC_EDIT_512, m_Sunday12);
	DDX_Text(pDX, IDC_EDIT_S512, m_Friday12);
	DDX_Text(pDX, IDC_EDIT_S534, m_Friday34);
	DDX_Text(pDX, IDC_EDIT_S556, m_Friday56);
	DDX_Text(pDX, IDC_EDIT_S578, m_Friday78);
	DDX_Text(pDX, IDC_EDIT_S612, m_Saturday12);
	DDX_Text(pDX, IDC_EDIT_S634, m_Saturday34);
	DDX_Text(pDX, IDC_EDIT_S656, m_Saturday56);
	DDX_Text(pDX, IDC_EDIT_S678, m_Saturday78);
	DDX_Text(pDX, IDC_EDIT_S712, m_Sunday12);
	DDX_Text(pDX, IDC_EDIT_S734, m_Sunday34);
	DDX_Text(pDX, IDC_EDIT_S756, m_Sunday56);
	DDX_Text(pDX, IDC_EDIT_S778, m_Sunday78);
	DDX_Text(pDX, IDC_EDIT1, m_strExtra);
	DDX_CBString(pDX, IDC_COMBO1, m_strWeek);
	DDX_Text(pDX, IDC_EDIT2, m_strSetInfor);
}


BEGIN_MESSAGE_MAP(CSetWorkDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BT_SET_ATWORK, &CSetWorkDlg::OnBnClickedBtSetAtwork)
	ON_BN_CLICKED(IDC_BT_SET_EXPORT, &CSetWorkDlg::OnBnClickedBtSetExport)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSetWorkDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDCBT_SET_DELETE, &CSetWorkDlg::OnBnClickedSetDelete)
END_MESSAGE_MAP()


// CSetWorkDlg 消息处理程序


void CSetWorkDlg::OnBnClickedBtSetAtwork()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString wa;
	wa.Format("即将设置第%d周的值班表，是否继续？", m_intWeek);
	if (MessageBox(wa, "请确定", MB_ICONQUESTION | MB_YESNO) == IDNO)return;
	try
	{
		//Connect to the database
		CAttend_tableSet recordset(&theApp.m_DB);
		CString strSQL;
		strSQL.Format("select * from attend_table where week_number=%d", m_intWeek);
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBoxA("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		if (!recordset.IsEOF())//存在且未锁定，则更新
		{
			CString update;
			update.Format("update attend_table set "
				"Monday12='%s',Monday34='%s',Monday56='%s',Monday78='%s',"
				"Tuesday12='%s',Tuesday34='%s',Tuesday56='%s',Tuesday78='%s',"
				"Wednesday12='%s',Wednesday34='%s',Wednesday56='%s',Wednesday78='%s',"
				"Thursday12='%s',Thursday34='%s',Thursday56='%s',Thursday78='%s',"
				"Friday12=%d,Friday34=%d,Friday56=%d,Friday78=%d,"
				"Saturday12='%s',Saturday34='%s',Saturday56='%s',Saturday78='%s',"
				"Sunday12='%s',Sunday34='%s',Sunday56='%s',Sunday78='%s',"
				"extra_infor='%s' where week_number=%d"
				, m_Monday12, m_Monday34, m_Monday56, m_Monday78,
				m_Tuesday12, m_Tuesday34, m_Tuesday56, m_Tuesday78,
				m_Wednesday12, m_Wednesday34, m_Wednesday56, m_Wednesday78,
				m_Thursday12, m_Thursday34, m_Thursday56, m_Thursday78,
				m_Friday12, m_Friday34, m_Friday56, m_Friday78,
				m_Saturday12, m_Saturday34, m_Saturday56, m_Saturday78,
				m_Sunday12, m_Sunday34, m_Sunday56, m_Sunday78,
				m_strExtra, m_intWeek);

			theApp.m_DB.ExecuteSQL(update);
			CString str;
			str.Format("成功更新第%d周的时间值班表！", m_intWeek);
			MessageBoxA(str, "更新成功", MB_ICONINFORMATION | MB_OK);

		}
		else//不存在则添加
		{
			CString insert;
			insert.Format("insert into attend_table("
				"Monday12,Monday34,Monday56,Monday78,"
				"Tuesday12,Tuesday34,Tuesday56,Tuesday78,"
				"Wednesday12,Wednesday34,Wednesday56,Wednesday78,"
				"Thursday12,Thursday34,Thursday56,Thursday78,"
				"Friday12,Friday34,Friday56,Friday78,"
				"Saturday12,Saturday34,Saturday56,Saturday78,"
				"Sunday12,Sunday34,Sunday56,Sunday78,"
				"extra_infor,week_number) values("
				"'%s','%s','%s','%s',"
				"'%s','%s','%s','%s',"
				"'%s','%s','%s','%s',"
				"'%s','%s','%s','%s',"
				"'%s','%s','%s','%s',"
				"'%s','%s','%s','%s',"
				"'%s','%s','%s','%s',"
				"'%s',%d)"
				, m_Monday12, m_Monday34, m_Monday56, m_Monday78,
				m_Tuesday12, m_Tuesday34, m_Tuesday56, m_Tuesday78,
				m_Wednesday12, m_Wednesday34, m_Wednesday56, m_Wednesday78,
				m_Thursday12, m_Thursday34, m_Thursday56, m_Thursday78,
				m_Friday12, m_Friday34, m_Friday56, m_Friday78,
				m_Saturday12, m_Saturday34, m_Saturday56, m_Saturday78,
				m_Sunday12, m_Sunday34, m_Sunday56, m_Sunday78,
				m_strExtra, m_intWeek);

			theApp.m_DB.ExecuteSQL(insert);
			CString str;
			str.Format("成功添加第%d周的时间值班表！", m_intWeek);
			GetDlgItem(IDCBT_SET_DELETE)->EnableWindow(TRUE);
			MessageBoxA(str, "添加成功", MB_ICONINFORMATION |MB_OK);
		}
		m_strSetInfor = "该周值班表已经设置！";
		recordset.Close();

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


BOOL CSetWorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (int i = 0; i < 24; i++)
	{
		CString str;
		str.Format("第%d周", i);
		m_ctrlWeek.AddString(str);
	}
	m_intWeek = theApp.m_nowWeek;
	m_strWeek.Format("第%d周", m_intWeek);
	ShowSheet();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void ExportTo(Range &range, Range &cols, _Worksheet &sheet,
	CString index, CString values)
{
	range = sheet.GetRange(COleVariant(_T(index)), COleVariant(_T(index)));
	range.SetValue(COleVariant(_T(values)));
	cols = range.GetEntireColumn();
	cols.AutoFit();
}
void CSetWorkDlg::OnBnClickedBtSetExport()
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

	//获得坐标为（A，1）和（A，1）的两个单元格
	range = sheet.GetRange(COleVariant(_T("C1")), COleVariant(_T("C1")));
	//设置单元格内容
	CString str;
	str.Format("招办第%d周值班表", m_intWeek);
	range.SetValue(COleVariant(str+m_strSetInfor));
	//选择整列，并设置宽度为自适应
	//cols =range.GetColumns();
	cols = range.GetEntireColumn();
	cols.AutoFit();
	/*ExportTo(range, cols, sheet, "时间\\星期","A2" );
	ExportTo(range, cols, sheet, "星期一","B2");
	ExportTo(range, cols, sheet,  "星期二","C2");
	ExportTo(range, cols, sheet,  "星期三","D2");
	ExportTo(range, cols, sheet,  "星期四","E2");
	ExportTo(range, cols, sheet, "星期五","F2");
	ExportTo(range, cols, sheet, "星期六","G2");
	ExportTo(range, cols, sheet, "星期日","H2");

	ExportTo(range, cols, sheet, "第12节", "A3");
	ExportTo(range, cols, sheet, m_Monday12, "B3");
	ExportTo(range, cols, sheet, m_Tuesday12, "C3");
	ExportTo(range, cols, sheet, m_Wednesday12, "D3");
	ExportTo(range, cols, sheet, m_Thursday12, "E3");
	ExportTo(range, cols, sheet, m_Friday12, "F3");
	ExportTo(range, cols, sheet, m_Saturday12, "G3");
	ExportTo(range, cols, sheet, m_Sunday12, "H3");
	
	ExportTo(range, cols, sheet, "第34节", "A4");
	ExportTo(range, cols, sheet, m_Monday34, "B4");
	ExportTo(range, cols, sheet, m_Tuesday34, "C4");
	ExportTo(range, cols, sheet, m_Wednesday34, "D4");
	ExportTo(range, cols, sheet, m_Thursday34, "E4");
	ExportTo(range, cols, sheet, m_Friday34, "F4");
	ExportTo(range, cols, sheet, m_Saturday34, "G4");
	ExportTo(range, cols, sheet, m_Sunday34, "H4");
	ExportTo(range, cols, sheet, "第56节", "A5");
	ExportTo(range, cols, sheet, m_Monday56, "B5");
	ExportTo(range, cols, sheet, m_Tuesday56, "C5");
	ExportTo(range, cols, sheet, m_Wednesday56, "D5");
	ExportTo(range, cols, sheet, m_Thursday56, "E5");
	ExportTo(range, cols, sheet, m_Friday56, "F5");
	ExportTo(range, cols, sheet, m_Saturday56, "G5");
	ExportTo(range, cols, sheet, m_Sunday56, "H5");
	ExportTo(range, cols, sheet, "第78节", "A6");
	ExportTo(range, cols, sheet, m_Monday78, "B6");
	ExportTo(range, cols, sheet, m_Tuesday78, "C6");
	ExportTo(range, cols, sheet, m_Wednesday78, "D6");
	ExportTo(range, cols, sheet, m_Thursday78, "E6");
	ExportTo(range, cols, sheet, m_Friday78, "F6");
	ExportTo(range, cols, sheet, m_Saturday78, "G6");
	ExportTo(range, cols, sheet, m_Sunday78, "H6");
	ExportTo(range, cols, sheet, m_strExtra, "C8");
	*/
	
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


void CSetWorkDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int iPos = m_ctrlWeek.GetCurSel();//当前选中的行。
	m_ctrlWeek.SetCurSel(iPos);//设置第n行内容为显示的内容。
	m_ctrlWeek.GetLBText(iPos, m_strWeek);
	m_intWeek = iPos;//box从0开始，周数也是从0开始
	ShowSheet();
	UpdateData(FALSE);
}
void CSetWorkDlg::ShowSheet()//显示空余时间表
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
		CAttend_tableSet recordset(&theApp.m_DB);
		CString strSQL;

		strSQL.Format("select * from attend_table where week_number=%d", m_intWeek);
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBox("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		if (!recordset.IsEOF())//先在值班表找
		{
			GetDlgItem(IDCBT_SET_DELETE)->EnableWindow(TRUE);
			
			m_Monday12 = recordset.m_Monday12;
			m_Monday34 = recordset.m_Monday34;
			m_Monday56 = recordset.m_Monday56;
			m_Monday78 = recordset.m_Monday78;
			m_Tuesday12 = recordset.m_Tuesday12;
			m_Tuesday34 = recordset.m_Tuesday34;
			m_Tuesday56 = recordset.m_Tuesday56;
			m_Tuesday78 = recordset.m_Tuesday78;
			m_Wednesday12 = recordset.m_Wednesday12;
			m_Wednesday34 = recordset.m_Wednesday34;
			m_Wednesday56 = recordset.m_Wednesday56;
			m_Wednesday78 = recordset.m_Wednesday78;
			m_Thursday12 = recordset.m_Thursday12;
			m_Thursday34 = recordset.m_Thursday34;
			m_Thursday56 = recordset.m_Thursday56;
			m_Thursday78 = recordset.m_Thursday78;
			m_Friday12 = recordset.m_Friday12;
			m_Friday34 = recordset.m_Friday34;
			m_Friday56 = recordset.m_Friday56;
			m_Friday78 = recordset.m_Friday78;
			m_Saturday12 = recordset.m_Saturday12;
			m_Saturday34 = recordset.m_Saturday34;
			m_Saturday56 = recordset.m_Saturday56;
			m_Saturday78 = recordset.m_Saturday78;
			m_Sunday12 = recordset.m_Sunday12;
			m_Sunday34 = recordset.m_Sunday34;
			m_Sunday56 = recordset.m_Sunday56;
			m_Sunday78 = recordset.m_Sunday78;
			m_strExtra = recordset.m_extra_infor;
			m_strSetInfor.Format("该周值班表已经设置！");
		}
		else//若该周值班表未设置，则显示每个人的空余时间
		{
			GetDlgItem(IDCBT_SET_DELETE)->EnableWindow(FALSE);

			m_strSetInfor.Format("该周值班表未设置！");
			CCourseSet recordset(&theApp.m_DB);
			CString strSQL;

			strSQL.Format("select * from course_table where week_number=%d", m_intWeek);
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
			recordset.Close();//CCourseSet
		}
		recordset.Close();//CAttend_tableSet
		
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

void CSetWorkDlg::OnBnClickedSetDelete()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString wa;
	wa.Format("即将删除第%d周的值班表，是否继续？", m_intWeek);
	if (MessageBox(wa, "请确定", MB_ICONQUESTION|MB_YESNO) == IDNO)return;
	try
	{
		//Connect to the database
		CAttend_tableSet recordset(&theApp.m_DB);
		CString strSQL;
		strSQL.Format("select * from attend_table where week_number=%d", m_intWeek);
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBoxA("打开数据库失败!", "数据库错误", MB_OK);
			return;
		}
		if (!recordset.IsEOF())//存在且，则删除
		{
			CString drop;
			drop.Format("delete from attend_table where week_number=%d", m_intWeek);

			theApp.m_DB.ExecuteSQL(drop);
			CString str;
			str.Format("成功删除第%d周的时间值班表！", m_intWeek);
			MessageBoxA(str, "删除成功", MB_ICONINFORMATION | MB_OK);
			ShowSheet();
		}
		else//不存在
		{
			CString str;
			str.Format("第%d周的时间值班表未设置！", m_intWeek);
			MessageBoxA(str, "删除失败", MB_OK);
		}
		recordset.Close();
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
