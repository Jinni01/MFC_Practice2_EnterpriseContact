
// EnterpriseContactDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "ContactAddDlg.h"
#include "ContactViewDlg.h"

class CContactAddDlg;
class CContactViewDlg;

// CEnterpriseContactDlg 대화 상자
class CEnterpriseContactDlg : public CDialogEx
{
// 생성입니다.
public:
	CEnterpriseContactDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_EC_MAIN_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	//control
	CTreeCtrl m_treContacts;
	CListCtrl m_lstContacts;
	CString m_strEdtSearch;
	CString m_strCurrentSelectedFolder;
	//other dlg 
	CContactAddDlg* m_dlgContactAdd;
	CContactViewDlg* m_dlgContactView;
	//values
	CStringArray m_straPopupedWindowName;
	int m_nPopupedWindowCount;
public:
	void SetSqlConnection();
	void SetTreeIconConfig();
	void SetListIconConfig();
	void LoadDataTree();
	void LoadDataList(const char* query);
	void LoadDataFolder();
	void DeleteData();
	void PopupContactAddWnd();
	BOOL isWindowPopuped(const CString& name);
	int SearchAtCStringArray(const CString& str, const CStringArray& p);
	void ContactViewWndClosed(const CString& name);
	void PopupContactViewWnd(const CString& name);
	afx_msg void OnTvnSelchangedEcContactsTre(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEcSearchBtn();
	afx_msg void OnBnClickedEcContactdeleteBtn();
	afx_msg void OnNMDblclkEcContactsLst(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEcContactaddBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
