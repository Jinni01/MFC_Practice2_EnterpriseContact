#pragma once
#include "afxwin.h"
#include "EnterpriseContactDlg.h"

class CEnterpriseContactDlg;

// CContactViewDlg 대화 상자입니다.

class CContactViewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CContactViewDlg)

public:
	CContactViewDlg(const CString& name, CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CContactViewDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_EC_VIEW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CString m_strEdtName;
	CString m_strEdtNameBackup;
	CString m_strEdtCRank;
	CString m_strEdtCGroup;
	CString m_strEdtTeam;
	CString m_strEdtPart;
	CString m_strEdtExtension;
	CString m_strEdtPhone;
	CString m_strEdtEmail;
	CString m_strEdtMemo;
	CEdit m_edtName;
	CEdit m_edtCRank;
	CEdit m_edtCGroup;
	CEdit m_edtTeam;
	CEdit m_edtPart;
	CEdit m_edtExtension;
	CEdit m_edtPhone;
	CEdit m_edtEmail;
	CEdit m_edtMemo;
	CComboBox m_cbxCGroup;
	CComboBox m_cbxTeam;
	CComboBox m_cbxPart;
	CButton m_btnModify;
	CButton m_btnOk;
	BOOL m_bIsModify;
public:
	virtual BOOL OnInitDialog();
	void SetData();
	void AddDropDownList(CComboBox* cbx, const char* query);
	void EnableInput();
	void DisableInput();
	void ReSetComboBoxList(CComboBox* cbx);
	void SetModify();
	afx_msg void OnBnClickedEcContactmodifyBtn();
	afx_msg void OnCbnSelchangeEcCgroupCbx();
	afx_msg void OnBnClickedEcContactokBtn();
	afx_msg void OnCbnSelchangeEcTeamCbx();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void PostNcDestroy();
};