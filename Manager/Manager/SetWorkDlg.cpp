// SetWorkDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Manager.h"
#include "SetWorkDlg.h"
#include "afxdialogex.h"
#include"attend_table.h"
#include"course_table.h"
#include"excel9.h"

// CSetWorkDlg �Ի���

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


// CSetWorkDlg ��Ϣ�������


void CSetWorkDlg::OnBnClickedBtSetAtwork()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString wa;
	wa.Format("�������õ�%d�ܵ�ֵ����Ƿ������", m_intWeek);
	if (MessageBox(wa, "��ȷ��", MB_ICONQUESTION | MB_YESNO) == IDNO)return;
	try
	{
		//Connect to the database
		CAttend_tableSet recordset(&theApp.m_DB);
		CString strSQL;
		strSQL.Format("select * from attend_table where week_number=%d", m_intWeek);
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBoxA("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
			return;
		}
		if (!recordset.IsEOF())//������δ�����������
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
			str.Format("�ɹ����µ�%d�ܵ�ʱ��ֵ���", m_intWeek);
			MessageBoxA(str, "���³ɹ�", MB_ICONINFORMATION | MB_OK);

		}
		else//�����������
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
			str.Format("�ɹ���ӵ�%d�ܵ�ʱ��ֵ���", m_intWeek);
			GetDlgItem(IDCBT_SET_DELETE)->EnableWindow(TRUE);
			MessageBoxA(str, "��ӳɹ�", MB_ICONINFORMATION |MB_OK);
		}
		m_strSetInfor = "����ֵ����Ѿ����ã�";
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	for (int i = 0; i < 24; i++)
	{
		CString str;
		str.Format("��%d��", i);
		m_ctrlWeek.AddString(str);
	}
	m_intWeek = theApp.m_nowWeek;
	m_strWeek.Format("��%d��", m_intWeek);
	ShowSheet();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	//���õ�Ԫ������
	CString str;
	str.Format("�а��%d��ֵ���", m_intWeek);
	range.SetValue(COleVariant(str+m_strSetInfor));
	//ѡ�����У������ÿ��Ϊ����Ӧ
	//cols =range.GetColumns();
	cols = range.GetEntireColumn();
	cols.AutoFit();
	/*ExportTo(range, cols, sheet, "ʱ��\\����","A2" );
	ExportTo(range, cols, sheet, "����һ","B2");
	ExportTo(range, cols, sheet,  "���ڶ�","C2");
	ExportTo(range, cols, sheet,  "������","D2");
	ExportTo(range, cols, sheet,  "������","E2");
	ExportTo(range, cols, sheet, "������","F2");
	ExportTo(range, cols, sheet, "������","G2");
	ExportTo(range, cols, sheet, "������","H2");

	ExportTo(range, cols, sheet, "��12��", "A3");
	ExportTo(range, cols, sheet, m_Monday12, "B3");
	ExportTo(range, cols, sheet, m_Tuesday12, "C3");
	ExportTo(range, cols, sheet, m_Wednesday12, "D3");
	ExportTo(range, cols, sheet, m_Thursday12, "E3");
	ExportTo(range, cols, sheet, m_Friday12, "F3");
	ExportTo(range, cols, sheet, m_Saturday12, "G3");
	ExportTo(range, cols, sheet, m_Sunday12, "H3");
	
	ExportTo(range, cols, sheet, "��34��", "A4");
	ExportTo(range, cols, sheet, m_Monday34, "B4");
	ExportTo(range, cols, sheet, m_Tuesday34, "C4");
	ExportTo(range, cols, sheet, m_Wednesday34, "D4");
	ExportTo(range, cols, sheet, m_Thursday34, "E4");
	ExportTo(range, cols, sheet, m_Friday34, "F4");
	ExportTo(range, cols, sheet, m_Saturday34, "G4");
	ExportTo(range, cols, sheet, m_Sunday34, "H4");
	ExportTo(range, cols, sheet, "��56��", "A5");
	ExportTo(range, cols, sheet, m_Monday56, "B5");
	ExportTo(range, cols, sheet, m_Tuesday56, "C5");
	ExportTo(range, cols, sheet, m_Wednesday56, "D5");
	ExportTo(range, cols, sheet, m_Thursday56, "E5");
	ExportTo(range, cols, sheet, m_Friday56, "F5");
	ExportTo(range, cols, sheet, m_Saturday56, "G5");
	ExportTo(range, cols, sheet, m_Sunday56, "H5");
	ExportTo(range, cols, sheet, "��78��", "A6");
	ExportTo(range, cols, sheet, m_Monday78, "B6");
	ExportTo(range, cols, sheet, m_Tuesday78, "C6");
	ExportTo(range, cols, sheet, m_Wednesday78, "D6");
	ExportTo(range, cols, sheet, m_Thursday78, "E6");
	ExportTo(range, cols, sheet, m_Friday78, "F6");
	ExportTo(range, cols, sheet, m_Saturday78, "G6");
	ExportTo(range, cols, sheet, m_Sunday78, "H6");
	ExportTo(range, cols, sheet, m_strExtra, "C8");
	*/
	
	//�б���
	range = sheet.GetRange(COleVariant(_T("A2")), COleVariant(_T("A2")));
	range.SetValue(COleVariant(_T("ʱ��\\����")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("B2")), COleVariant(_T("B2")));
	range.SetValue(COleVariant(_T("����һ")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("C2")), COleVariant(_T("C2")));
	range.SetValue(COleVariant(_T("���ڶ�")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("D2")), COleVariant(_T("D2")));
	range.SetValue(COleVariant(_T("������")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("E2")), COleVariant(_T("E2")));
	range.SetValue(COleVariant(_T("������")));

	range = sheet.GetRange(COleVariant(_T("F2")), COleVariant(_T("F2")));
	range.SetValue(COleVariant(_T("������")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("G2")), COleVariant(_T("G2")));
	range.SetValue(COleVariant(_T("������")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	range = sheet.GetRange(COleVariant(_T("H2")), COleVariant(_T("H2")));
	range.SetValue(COleVariant(_T("������")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

	//�б���
	range = sheet.GetRange(COleVariant(_T("A3")), COleVariant(_T("A3")));
	range.SetValue(COleVariant(_T("��12��")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("A4")), COleVariant(_T("A4")));
	range.SetValue(COleVariant(_T("��34��")));
	cols = range.GetEntireColumn();
	cols.AutoFit();
	range = sheet.GetRange(COleVariant(_T("A5")), COleVariant(_T("A5")));
	range.SetValue(COleVariant(_T("��56��")));
	cols = range.GetEntireColumn();
	cols.AutoFit(); 
	range = sheet.GetRange(COleVariant(_T("A6")), COleVariant(_T("A6")));
	range.SetValue(COleVariant(_T("��78��")));
	cols = range.GetEntireColumn();
	cols.AutoFit();

    //����һ
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

	//���ڶ�
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

	//������
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
	//������
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
	//������
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

	//������
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

	//������
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

	str.Format("�ɹ��������ݼ�¼��");
	MessageBoxA(str, "�����ɹ�",
		MB_ICONEXCLAMATION | MB_OK);
}


void CSetWorkDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int iPos = m_ctrlWeek.GetCurSel();//��ǰѡ�е��С�
	m_ctrlWeek.SetCurSel(iPos);//���õ�n������Ϊ��ʾ�����ݡ�
	m_ctrlWeek.GetLBText(iPos, m_strWeek);
	m_intWeek = iPos;//box��0��ʼ������Ҳ�Ǵ�0��ʼ
	ShowSheet();
	UpdateData(FALSE);
}
void CSetWorkDlg::ShowSheet()//��ʾ����ʱ���
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
			MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
			return;
		}
		if (!recordset.IsEOF())//����ֵ�����
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
			m_strSetInfor.Format("����ֵ����Ѿ����ã�");
		}
		else//������ֵ���δ���ã�����ʾÿ���˵Ŀ���ʱ��
		{
			GetDlgItem(IDCBT_SET_DELETE)->EnableWindow(FALSE);

			m_strSetInfor.Format("����ֵ���δ���ã�");
			CCourseSet recordset(&theApp.m_DB);
			CString strSQL;

			strSQL.Format("select * from course_table where week_number=%d", m_intWeek);
			if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
			{
				MessageBox("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
				return;
			}

			while (!recordset.IsEOF())
			{
				//�����ʱ���пգ�����뵽����ʱ���
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString wa;
	wa.Format("����ɾ����%d�ܵ�ֵ����Ƿ������", m_intWeek);
	if (MessageBox(wa, "��ȷ��", MB_ICONQUESTION|MB_YESNO) == IDNO)return;
	try
	{
		//Connect to the database
		CAttend_tableSet recordset(&theApp.m_DB);
		CString strSQL;
		strSQL.Format("select * from attend_table where week_number=%d", m_intWeek);
		if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
		{
			MessageBoxA("�����ݿ�ʧ��!", "���ݿ����", MB_OK);
			return;
		}
		if (!recordset.IsEOF())//�����ң���ɾ��
		{
			CString drop;
			drop.Format("delete from attend_table where week_number=%d", m_intWeek);

			theApp.m_DB.ExecuteSQL(drop);
			CString str;
			str.Format("�ɹ�ɾ����%d�ܵ�ʱ��ֵ���", m_intWeek);
			MessageBoxA(str, "ɾ���ɹ�", MB_ICONINFORMATION | MB_OK);
			ShowSheet();
		}
		else//������
		{
			CString str;
			str.Format("��%d�ܵ�ʱ��ֵ���δ���ã�", m_intWeek);
			MessageBoxA(str, "ɾ��ʧ��", MB_OK);
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
