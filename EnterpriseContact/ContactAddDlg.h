#pragma once
#include "afxwin.h"
#include "EnterpriseContactDlg.h"


// CContactAddDlg 대화 상자입니다.

class CEnterpriseContactDlg;

class CContactAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CContactAddDlg)

public:
	CContactAddDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CContactAddDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_EC_ADD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CString m_strEdtName;
	CString m_strEdtCRank;
	CComboBox m_cbxCGroup;
	CComboBox m_cbxTeam;
	CComboBox m_cbxPart;
	CString m_strEdtExtension;
	CString m_strEdtPhone;
	CString m_strEdtEmail;
	CString m_strEdtMemo;
public:
	void AddDropDownList(CComboBox* cbx, const char* query);
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeEcCgroupCbx();
	afx_msg void OnCbnSelchangeEcTeamCbx();
	afx_msg void OnBnClickedEcContactpushBtn();
	afx_msg void OnBnClickedEcContactcancleBtn();
	virtual void PostNcDestroy();
};
