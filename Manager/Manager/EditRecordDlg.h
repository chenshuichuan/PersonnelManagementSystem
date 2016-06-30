#pragma once


// CEditRecordDlg 对话框

class CEditRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditRecordDlg)

public:
	CEditRecordDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CEditRecordDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_EDIT_RECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_intStartDay;
	CString m_strName;
	CString m_strYearMonth;
	CString m_strEndYM;
	int m_intStartHour;
	int m_intStartMin;
	int m_intEndDay;
	int m_intEndHour;
	int m_intEndMin;
	CString m_strWorkHour;
	int m_intWeek;
	CString m_strExtraInfor;
	virtual void OnOK();
};
