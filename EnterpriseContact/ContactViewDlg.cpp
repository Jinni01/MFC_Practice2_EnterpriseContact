// ContactViewDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EnterpriseContact.h"
#include "ContactViewDlg.h"
#include "afxdialogex.h"


// CContactViewDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CContactViewDlg, CDialogEx)

CContactViewDlg::CContactViewDlg(const CString& name, CWnd* pParent /*=NULL*/)
	: CDialogEx(CContactViewDlg::IDD, pParent)
	, m_strEdtName(name)
	, m_strEdtNameBackup(name)
	, m_strEdtExtension(_T(""))
	, m_strEdtPhone(_T(""))
	, m_strEdtEmail(_T(""))
	, m_strEdtMemo(_T(""))
	, m_strEdtPart(_T(""))
	, m_bIsModify(FALSE)
{
}

CContactViewDlg::~CContactViewDlg()
{
}

void CContactViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EC_NAME_EDT, m_strEdtName);
	DDX_Text(pDX, IDC_EC_CRANK_EDT, m_strEdtCRank);
	DDX_Text(pDX, IDC_EC_CGROUP_EDT, m_strEdtCGroup);
	DDX_Text(pDX, IDC_EC_TEAM_EDT, m_strEdtTeam);
	DDX_Text(pDX, IDC_EC_PART_EDT, m_strEdtPart);
	DDX_Text(pDX, IDC_EC_EXTENSION_EDT, m_strEdtExtension);
	DDX_Text(pDX, IDC_EC_PHONE_EDT, m_strEdtPhone);
	DDX_Text(pDX, IDC_EC_EMAIL_EDT, m_strEdtEmail);
	DDX_Text(pDX, IDC_EC_MEMO_EDT, m_strEdtMemo);
	DDX_Control(pDX, IDC_EC_NAME_EDT, m_edtName);
	DDX_Control(pDX, IDC_EC_CRANK_EDT, m_edtCRank);
	DDX_Control(pDX, IDC_EC_CGROUP_EDT, m_edtCGroup);
	DDX_Control(pDX, IDC_EC_TEAM_EDT, m_edtTeam);
	DDX_Control(pDX, IDC_EC_PART_EDT, m_edtPart);
	DDX_Control(pDX, IDC_EC_EXTENSION_EDT, m_edtExtension);
	DDX_Control(pDX, IDC_EC_PHONE_EDT, m_edtPhone);
	DDX_Control(pDX, IDC_EC_EMAIL_EDT, m_edtEmail);
	DDX_Control(pDX, IDC_EC_MEMO_EDT, m_edtMemo);
	DDX_Control(pDX, IDC_EC_CGROUP_CBX, m_cbxCGroup);
	DDX_Control(pDX, IDC_EC_TEAM_CBX, m_cbxTeam);
	DDX_Control(pDX, IDC_EC_PART_CBX, m_cbxPart);
	DDX_Control(pDX, IDC_EC_CONTACTMODIFY_BTN, m_btnModify);
	DDX_Control(pDX, IDC_EC_CONTACTOK_BTN, m_btnOk);
}


BEGIN_MESSAGE_MAP(CContactViewDlg, CDialogEx)
	ON_BN_CLICKED(IDC_EC_CONTACTMODIFY_BTN, &CContactViewDlg::OnBnClickedEcContactmodifyBtn)
	ON_BN_CLICKED(IDC_EC_CONTACTOK_BTN, &CContactViewDlg::OnBnClickedEcContactokBtn)
	ON_CBN_SELCHANGE(IDC_EC_CGROUP_CBX, &CContactViewDlg::OnCbnSelchangeEcCgroupCbx)
	ON_CBN_SELCHANGE(IDC_EC_TEAM_CBX, &CContactViewDlg::OnCbnSelchangeEcTeamCbx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CContactViewDlg 메시지 처리기입니다.


BOOL CContactViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CContactViewDlg::SetData()
{
	m_cbxCGroup.ShowWindow(FALSE);
	m_cbxTeam.ShowWindow(FALSE);
	m_cbxPart.ShowWindow(FALSE);

	CString strQuery = _T("SELECT * FROM contacts WHERE name = \'" + m_strEdtName + "\'");
	ExecuteQuery(static_cast<CStringA>(strQuery));

	if((sqlRow = mysql_fetch_row(sqlResult)) != NULL)
	{
		m_strEdtCRank = sqlRow[ROW_CRANK];
		m_strEdtCGroup = sqlRow[ROW_CGROUP];
		m_strEdtTeam = sqlRow[ROW_TEAM];
		m_strEdtPart = sqlRow[ROW_PART];
		m_strEdtExtension = sqlRow[ROW_EXTENSION];
		m_strEdtPhone = sqlRow[ROW_PHONE];
		m_strEdtEmail = sqlRow[ROW_EMAIL];
		m_strEdtMemo = sqlRow[ROW_MEMO];

		UpdateData(FALSE);
	}
}

void CContactViewDlg::AddDropDownList(CComboBox* cbx, const char* query)
{
	ExecuteQuery(query);

	while((sqlRow = mysql_fetch_row(sqlResult)) != NULL){
		cbx->EnableWindow(TRUE);
		CString strTmp;
		strTmp = sqlRow[ROW_DATA_IDX];
		cbx->InsertString(cbx->GetCount() ,strTmp);
	}
}

void CContactViewDlg::EnableInput()
{
	m_edtCGroup.ShowWindow(FALSE);
	m_edtTeam.ShowWindow(FALSE);
	m_edtPart.ShowWindow(FALSE);
	m_cbxCGroup.ShowWindow(TRUE);
	m_cbxTeam.ShowWindow(TRUE);
	m_cbxPart.ShowWindow(TRUE);

	m_edtName.SetReadOnly(FALSE);
	m_edtCRank.SetReadOnly(FALSE);
	m_edtExtension.SetReadOnly(FALSE);
	m_edtPhone.SetReadOnly(FALSE);
	m_edtEmail.SetReadOnly(FALSE);
	m_edtMemo.SetReadOnly(FALSE);

	m_btnModify.SetWindowTextW(_T("저장"));
	m_btnOk.SetWindowTextW(_T("취소"));
}

void CContactViewDlg::DisableInput()
{
	m_edtCGroup.ShowWindow(TRUE);
	m_edtTeam.ShowWindow(TRUE);
	m_edtPart.ShowWindow(TRUE);
	m_cbxCGroup.ShowWindow(FALSE);
	m_cbxTeam.ShowWindow(FALSE);
	m_cbxPart.ShowWindow(FALSE);

	m_edtName.SetReadOnly(TRUE);
	m_edtCRank.SetReadOnly(TRUE);
	m_edtExtension.SetReadOnly(TRUE);
	m_edtPhone.SetReadOnly(TRUE);
	m_edtEmail.SetReadOnly(TRUE);
	m_edtMemo.SetReadOnly(TRUE);

	m_btnModify.SetWindowTextW(_T("수정"));
	m_btnOk.SetWindowTextW(_T("확인"));
}

void CContactViewDlg::ReSetComboBoxList(CComboBox* cbx)
{
	cbx->ResetContent();
	cbx->AddString(_T("NULL"));
	cbx->SetCurSel(0);
}

void CContactViewDlg::SetModify()
{
	if(!m_bIsModify)
	{
		EnableInput();

		ReSetComboBoxList(&m_cbxTeam);
		ReSetComboBoxList(&m_cbxPart);

		AddDropDownList(&m_cbxCGroup, "SELECT cgroup FROM midasit");

		CString strQuery = _T("SELECT cgroup, team, part FROM contacts WHERE name = \'" + m_strEdtNameBackup + "\'");
		ExecuteQuery(static_cast<CStringA>(strQuery));
		int nIdxCGroup = 0, nIdxTeam = 1, nIdxPart = 2;
		if((sqlRow = mysql_fetch_row(sqlResult)) != NULL)
		{
			CString strCgroup, strTeam, strPart;
			strCgroup = sqlRow[nIdxCGroup];
			strTeam = sqlRow[nIdxTeam];
			strPart = sqlRow[nIdxPart];
			m_cbxCGroup.SelectString(-1, strCgroup);

			CString strQueryGroup = _T("SELECT team FROM cgroup where name = \'" + strCgroup + "\'");
			AddDropDownList(&m_cbxTeam, static_cast<CStringA>(strQueryGroup));
			m_cbxTeam.SelectString(-1, strTeam);
			
			CString strQueryTeam = _T("SELECT part FROM team where name = \'" + strTeam + "\'");
			AddDropDownList(&m_cbxPart, static_cast<CStringA>(strQueryTeam));
			m_cbxPart.SelectString(-1, strPart);
		}

		m_bIsModify = TRUE;
	}
	else
	{
		DisableInput();

		UpdateData();

		m_cbxCGroup.GetLBText(m_cbxCGroup.GetCurSel(), m_strEdtCGroup);
		m_cbxTeam.GetLBText(m_cbxTeam.GetCurSel(), m_strEdtTeam);
		m_cbxPart.GetLBText(m_cbxPart.GetCurSel(), m_strEdtPart);

		UpdateData(FALSE);

		CString strQuery = _T("UPDATE contacts SET name = \'" + m_strEdtName + "\', "
			+ "crank = \'" + m_strEdtCRank + "\', " 
			+ "cgroup = \'" + m_strEdtCGroup + "\' ,"
			+ "team = \'" + m_strEdtTeam + "\' ,"
			+ "part = \'" + m_strEdtPart + "\' ,"
			+ "extension = \'" + m_strEdtExtension + "\' ,"
			+ "phone = \'" + m_strEdtPhone + "\' ,"
			+ "email = \'" + m_strEdtEmail + "\' ,"
			+ "memo = \'" + m_strEdtMemo + "\'"
			+ "WHERE name = \'" + m_strEdtNameBackup + "\'");

		ExecuteQuery(static_cast<CStringA>(strQuery));

		static_cast<CEnterpriseContactDlg*>(GetParent())->LoadDataFolder();

		m_bIsModify = FALSE;
	}
}


void CContactViewDlg::OnCbnSelchangeEcCgroupCbx()
{
	ReSetComboBoxList(&m_cbxTeam);
	ReSetComboBoxList(&m_cbxPart);

	int nIndex = m_cbxCGroup.GetCurSel();
	CString strName = _T("");
	m_cbxCGroup.GetLBText(nIndex, strName);

	CString strQuery = _T("SELECT team from cgroup where name = \'" + strName + "\'");
	AddDropDownList(&m_cbxTeam, static_cast<CStringA>(strQuery));
}


void CContactViewDlg::OnCbnSelchangeEcTeamCbx()
{
	int nIndex = m_cbxTeam.GetCurSel();
	CString strName = _T("");
	m_cbxTeam.GetLBText(nIndex, strName);

	CString strQuery = _T("SELECT part from team where name = \'" + strName + "\'");
	AddDropDownList(&m_cbxPart, static_cast<CStringA>(strQuery));
}


void CContactViewDlg::OnBnClickedEcContactmodifyBtn()
{
	SetModify();
}


void CContactViewDlg::OnBnClickedEcContactokBtn()
{
	OnOK();
}


void CContactViewDlg::OnOK()
{
	static_cast<CEnterpriseContactDlg*>(GetParent())->ContactViewWndClosed(m_strEdtNameBackup);
	CDialogEx::OnOK();
}


void CContactViewDlg::OnClose()
{
	static_cast<CEnterpriseContactDlg*>(GetParent())->ContactViewWndClosed(m_strEdtNameBackup);
	CDialogEx::OnClose();
}


void CContactViewDlg::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();
	delete this;
}
