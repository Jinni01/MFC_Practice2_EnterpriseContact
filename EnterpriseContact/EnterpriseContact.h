
// EnterpriseContact.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CEnterpriseContactApp:
// �� Ŭ������ ������ ���ؼ��� EnterpriseContact.cpp�� �����Ͻʽÿ�.
//

class CEnterpriseContactApp : public CWinApp
{
public:
	CEnterpriseContactApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CEnterpriseContactApp theApp;