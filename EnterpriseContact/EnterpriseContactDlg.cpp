
// EnterpriseContactDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "EnterpriseContact.h"
#include "EnterpriseContactDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEnterpriseContactDlg 대화 상자



CEnterpriseContactDlg::CEnterpriseContactDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEnterpriseContactDlg::IDD, pParent)
	, m_strEdtSearch(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_EC_APPFRAME_ICN);
}

void CEnterpriseContactDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EC_CONTACTS_TRE, m_treContacts);
	DDX_Control(pDX, IDC_EC_CONTACTS_LST, m_lstContacts);
	DDX_Text(pDX, IDC_EC_SEARCH_EDT, m_strEdtSearch);
}

BEGIN_MESSAGE_MAP(CEnterpriseContactDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_EC_CONTACTS_TRE, OnTvnSelchangedEcContactsTre)
	ON_BN_CLICKED(IDC_EC_SEARCH_BTN, &CEnterpriseContactDlg::OnBnClickedEcSearchBtn)
	ON_BN_CLICKED(IDC_EC_CONTACTDELETE_BTN, &CEnterpriseContactDlg::OnBnClickedEcContactdeleteBtn)
	ON_NOTIFY(NM_DBLCLK, IDC_EC_CONTACTS_LST, &CEnterpriseContactDlg::OnNMDblclkEcContactsLst)
	ON_BN_CLICKED(IDC_EC_CONTACTADD_BTN, &CEnterpriseContactDlg::OnBnClickedEcContactaddBtn)
END_MESSAGE_MAP()


// CEnterpriseContactDlg 메시지 처리기

BOOL CEnterpriseContactDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	//extend 
	SetSqlConnection();
	SetTreeIconConfig();
	SetListIconConfig();
	LoadDataTree();
	/*m_straPopupedWindowName.SetSize(5);*/
	m_nPopupedWindowCount = 0;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CEnterpriseContactDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();

	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CEnterpriseContactDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CEnterpriseContactDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEnterpriseContactDlg::SetSqlConnection()
{
	mysql_init(&sqlConnect);;
	sqlConnection = mysql_real_connect(&sqlConnect, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, static_cast<char*>(NULL), 0);


	if(sqlConnection == NULL)
	{
		CString strError = _T("");
		strError = mysql_error(&sqlConnect);
		AfxMessageBox(strError, MB_OK);
	}
	else
	{
		mysql_query(&sqlConnect, "set names euckr"); //한글 인식
	}
}

void CEnterpriseContactDlg::SetTreeIconConfig()
{
	static CImageList imageListTreeIcon;
	imageListTreeIcon.Create(16, 16, ILC_COLOR32, 2, 0);
	imageListTreeIcon.Add(AfxGetApp()->LoadIconW(IDI_EC_FOLDERPRE_ICN));
	imageListTreeIcon.Add(AfxGetApp()->LoadIconW(IDI_EC_FOLDEREND_ICN));
	m_treContacts.SetImageList(&imageListTreeIcon, TVSIL_NORMAL);
}

void CEnterpriseContactDlg::SetListIconConfig()
{
	static CImageList imageListListIcon;
	imageListListIcon.Create(32, 32, ILC_COLOR32, 1, 0);
	imageListListIcon.Add(AfxGetApp()->LoadIconW(IDI_EC_CONTACT_ICN));
	m_lstContacts.SetImageList(&imageListListIcon, LVSIL_NORMAL);
}

void CEnterpriseContactDlg::LoadDataTree()
{
	ExecuteQuery("SELECT cgroup FROM midasit");

	MYSQL_ROW sqlRowTmp_midasit;
	MYSQL_RES sqlResult_midasit;
	HTREEITEM hItem_root, hItem_group = NULL;
	CString strTmp;

	sqlResult_midasit = *sqlResult;

	hItem_root = m_treContacts.InsertItem(_T("마이다스아이티"), 0, 1, TVI_ROOT);

	while((sqlRowTmp_midasit = mysql_fetch_row(&sqlResult_midasit)) != NULL)
	{
		strTmp = sqlRowTmp_midasit[ROW_DATA_IDX];
		hItem_group = m_treContacts.InsertItem(strTmp, 0, 1, hItem_root);

		CString strQuery = _T("SELECT team FROM cgroup WHERE name=\'" + strTmp + "\'");
		ExecuteQuery(static_cast<CStringA>(strQuery));

		MYSQL_ROW sqlRowTmp_cgroup;
		MYSQL_RES sqlResult_cgroup;
		HTREEITEM hItem_team = NULL;

		sqlResult_cgroup = *sqlResult;

		while((sqlRowTmp_cgroup = mysql_fetch_row(&sqlResult_cgroup)) != NULL)
		{
			strTmp = sqlRowTmp_cgroup[ROW_DATA_IDX];
			hItem_team = m_treContacts.InsertItem(strTmp, 0, 1, hItem_group);

			CString strQuery = _T("SELECT part FROM team WHERE name = \'" + strTmp + "\'");
			ExecuteQuery(static_cast<CStringA>(strQuery));

			MYSQL_ROW sqlRowTmp_team;
			MYSQL_RES sqlResult_team;

			sqlResult_team = *sqlResult;

			while((sqlRowTmp_team = mysql_fetch_row(&sqlResult_team)) != NULL)
			{
				strTmp = sqlRowTmp_team[ROW_DATA_IDX];
				m_treContacts.InsertItem(strTmp, 0, 1, hItem_team);
			}
		}
	}
}

void CEnterpriseContactDlg::LoadDataList(const char* query)
{
	ExecuteQuery(query);

	CString strTmp;
	int nIndex = 0;

	m_lstContacts.DeleteAllItems();
	while((sqlRow = mysql_fetch_row(sqlResult)) != NULL)
	{
		strTmp = sqlRow[ROW_DATA_IDX];
		m_lstContacts.InsertItem(nIndex, strTmp, 0);

		nIndex++;
	}
}

void CEnterpriseContactDlg::LoadDataFolder()
{
	if(m_strCurrentSelectedFolder == _T("마이다스아이티"))
	{
		LoadDataList("SELECT * FROM contacts");
	}
	else
	{
		CString strQuery = _T("SELECT * FROM contacts WHERE cgroup = \'" + m_strCurrentSelectedFolder
			+ "\' OR team = \'" + m_strCurrentSelectedFolder
			+ "\' OR part = \'" + m_strCurrentSelectedFolder + "\'");
		LoadDataList(static_cast<CStringA>(strQuery));
	}
}


void CEnterpriseContactDlg::DeleteData()
{
	if(POSITION pos = m_lstContacts.GetFirstSelectedItemPosition())
	{
		int nCountSelected = m_lstContacts.GetSelectedCount();
		CString strTmp = _T("");
		strTmp.Format(_T("선택된 %d개의 연락처를 모두 삭제하시겠습니까?"), nCountSelected);
		if(AfxMessageBox(strTmp, MB_YESNO) == IDYES)
		{
			for(int i=0; i<nCountSelected; ++i)
			{
				int nItemIdx = m_lstContacts.GetNextSelectedItem(pos);

				CString strSelectedItemText = m_lstContacts.GetItemText(nItemIdx, 0);
				CString strQuery = _T("DELETE FROM contacts where name =\'" + strSelectedItemText + "\'");
				ExecuteQuery(static_cast<CStringA>(strQuery));
			}

		}
		LoadDataFolder();
	}
	else
	{
		AfxMessageBox(_T("선택된 연락처가 없습니다."));
	}
}


void CEnterpriseContactDlg::PopupContactAddWnd()
{
	m_dlgContactAdd = new CContactAddDlg();
	m_dlgContactAdd->Create(IDD_EC_ADD_DLG, this);
	m_dlgContactAdd->ShowWindow(SW_SHOW);
}

BOOL CEnterpriseContactDlg::isWindowPopuped(const CString& name)
{
	BOOL isExist = FALSE;

	for(int i=0; i<m_straPopupedWindowName.GetSize(); ++i)
	{
		if(m_straPopupedWindowName.GetAt(i) == name)
		{
			isExist = TRUE;
			break;
		}
	}

	return isExist;
}

void CEnterpriseContactDlg::PopupContactViewWnd(const CString& name)
{
	if(isWindowPopuped(name) != TRUE)
	{
		if(m_nPopupedWindowCount < 5)
		{
			m_dlgContactView = new CContactViewDlg(name);
			m_dlgContactView->Create(IDD_EC_VIEW_DLG, this);
			m_dlgContactView->ShowWindow(SW_SHOW);

			m_straPopupedWindowName.Add(name);
			m_nPopupedWindowCount++;
		}
		else{
			AfxMessageBox(_T("연락처 함께 보기는 5개의 창 까지만 지원합니다."));
		}
	}
}


int CEnterpriseContactDlg::SearchAtCStringArray(const CString& str, const CStringArray& p)
{
	int nIndex = -1;
	for(int i=0; i<p.GetSize(); ++i)
	{
		if(p.GetAt(i) == str)
		{
			nIndex = i;
			break;
		}
	}

	return nIndex;
}


void CEnterpriseContactDlg::ContactViewWndClosed(const CString& name)
{
	int nIndex = SearchAtCStringArray(name, m_straPopupedWindowName);
	m_straPopupedWindowName.RemoveAt(nIndex);
	m_nPopupedWindowCount--;
}


void CEnterpriseContactDlg::OnTvnSelchangedEcContactsTre(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	m_strCurrentSelectedFolder = m_treContacts.GetItemText(pNMTreeView->itemNew.hItem);

	LoadDataFolder();

	*pResult = 0;
}


void CEnterpriseContactDlg::OnBnClickedEcSearchBtn()
{
	UpdateData();
	CString strQuery = _T("SELECT * from contacts WHERE name like \'%" + m_strEdtSearch + "%\'");
	LoadDataList(static_cast<CStringA>(strQuery));
}


void CEnterpriseContactDlg::OnBnClickedEcContactdeleteBtn()
{
	DeleteData();
}


void CEnterpriseContactDlg::OnBnClickedEcContactaddBtn()
{
	PopupContactAddWnd();
}


void CEnterpriseContactDlg::OnNMDblclkEcContactsLst(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CString strSelectedItemText = m_lstContacts.GetItemText(pNMItemActivate->iItem, 0);
	if(pNMItemActivate->iItem != -1)
	{
		PopupContactViewWnd(strSelectedItemText);
	}

	*pResult = 0;
}


BOOL CEnterpriseContactDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)             
		{  
			return true;
		}
		if(pMsg->wParam == VK_ESCAPE)
		{
			return true;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}