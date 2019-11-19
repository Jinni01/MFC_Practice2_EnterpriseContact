// ContactAddDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "EnterpriseContact.h"
#include "ContactAddDlg.h"
#include "afxdialogex.h"


// CContactAddDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CContactAddDlg, CDialogEx)

CContactAddDlg::CContactAddDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CContactAddDlg::IDD, pParent)
	, m_strEdtName(_T(""))
	, m_strEdtCRank(_T(""))
	, m_strEdtExtension(_T(""))
	, m_strEdtEmail(_T(""))
	, m_strEdtMemo(_T(""))
	, m_strEdtPhone(_T(""))
{

}

CContactAddDlg::~CContactAddDlg()
{
}

void CContactAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EC_NAME_EDT, m_strEdtName);
	DDX_Text(pDX, IDC_EC_CRANK_EDT, m_strEdtCRank);
	DDX_Control(pDX, IDC_EC_CGROUP_CBX, m_cbxCGroup);
	DDX_Control(pDX, IDC_EC_TEAM_CBX, m_cbxTeam);
	DDX_Control(pDX, IDC_EC_PART_CBX, m_cbxPart);
	DDX_Text(pDX, IDC_EC_EXTENSION_EDT, m_strEdtExtension);
	DDX_Text(pDX, IDC_EC_PHONE_EDT, m_strEdtPhone);
	DDX_Text(pDX, IDC_EC_EMAIL_EDT, m_strEdtEmail);
	DDX_Text(pDX, IDC_EC_MEMO_EDT, m_strEdtMemo);
}


BEGIN_MESSAGE_MAP(CContactAddDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_EC_CGROUP_CBX, &CContactAddDlg::OnCbnSelchangeEcCgroupCbx)
	ON_CBN_SELCHANGE(IDC_EC_TEAM_CBX, &CContactAddDlg::OnCbnSelchangeEcTeamCbx)
	ON_BN_CLICKED(IDC_EC_CONTACTPUSH_BTN, &CContactAddDlg::OnBnClickedEcContactpushBtn)
	ON_BN_CLICKED(IDC_EC_CONTACTCANCLE_BTN, &CContactAddDlg::OnBnClickedEcContactcancleBtn)
END_MESSAGE_MAP()


// CContactAddDlg 메시지 처리기입니다.

BOOL CContactAddDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	AddDropDownList(&m_cbxCGroup, "SELECT cgroup from midasit");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CContactAddDlg::AddDropDownList(CComboBox* cbx, const char* query)
{

	ExecuteQuery(query);

	while((sqlRow = mysql_fetch_row(sqlResult)) != NULL)
	{
		cbx->EnableWindow(TRUE);
		CString strTmp;
		strTmp = sqlRow[ROW_DATA_IDX];
		cbx->InsertString(cbx->GetCount() ,strTmp);
	}
}

void CContactAddDlg::OnCbnSelchangeEcCgroupCbx()
{
	int nIndex = m_cbxCGroup.GetCurSel();
	CString strName = _T("");
	m_cbxCGroup.GetLBText(nIndex, strName);

	m_cbxTeam.ResetContent();
	m_cbxTeam.AddString(_T("NULL"));
	m_cbxTeam.SetCurSel(0);
	m_cbxPart.ResetContent();
	m_cbxPart.AddString(_T("NULL"));
	m_cbxPart.SetCurSel(0);

	CString strQuery = _T("SELECT team from cgroup where name = \'" + strName + "\'");
	AddDropDownList(&m_cbxTeam, static_cast<CStringA>(strQuery));
}


void CContactAddDlg::OnCbnSelchangeEcTeamCbx()
{
	int nIndex = m_cbxTeam.GetCurSel();
	CString strName = _T("");
	m_cbxTeam.GetLBText(nIndex, strName);

	CString strQuery = _T("SELECT part from team where name = \'" + strName + "\'");
	AddDropDownList(&m_cbxPart, static_cast<CStringA>(strQuery));
}

void CContactAddDlg::OnBnClickedEcContactpushBtn()
{
	UpdateData();
	int nIndex;
	CString strCGroup, strTeam, strPart;
	
	nIndex = m_cbxCGroup.GetCurSel();
	m_cbxCGroup.GetLBText(nIndex, strCGroup);

	nIndex = m_cbxTeam.GetCurSel();
	m_cbxTeam.GetLBText(nIndex, strTeam);

	nIndex = m_cbxPart.GetCurSel();
	m_cbxPart.GetLBText(nIndex, strPart);

	CString strQuery = _T("INSERT INTO contacts values(\'" + m_strEdtName+ "\', " 
		+ "\'" + m_strEdtCRank + "\', "
		+ "\'" + strCGroup + "\', "
		+ "\'" + strTeam + "\', "
		+ "\'" + strPart + "\', "
		+ "\'" + m_strEdtExtension + "\', "
		+ "\'" + m_strEdtPhone + "\', "
		+ "\'" + m_strEdtEmail + "\', "
		+ "\'" + m_strEdtMemo + "\')"
		);
	ExecuteQuery(static_cast<CStringA>(strQuery));
	static_cast<CEnterpriseContactDlg*>(GetParent())->LoadDataFolder();

	OnOK();
}


void CContactAddDlg::OnBnClickedEcContactcancleBtn()
{
	OnOK();
}


void CContactAddDlg::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();
	delete this;
}
