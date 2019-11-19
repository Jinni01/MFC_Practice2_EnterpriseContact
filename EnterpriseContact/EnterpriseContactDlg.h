
// EnterpriseContactDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "ContactAddDlg.h"
#include "ContactViewDlg.h"

class CContactAddDlg;
class CContactViewDlg;

// CEnterpriseContactDlg ��ȭ ����
class CEnterpriseContactDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CEnterpriseContactDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_EC_MAIN_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
