#pragma once


// CEditRecordDlg �Ի���

class CEditRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditRecordDlg)

public:
	CEditRecordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEditRecordDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_EDIT_RECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
