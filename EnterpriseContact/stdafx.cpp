
// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// EnterpriseContact.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"

MYSQL* sqlConnection;
MYSQL sqlConnect;
MYSQL_RES* sqlResult;
MYSQL_ROW sqlRow;
int sqlQueryStatus;

void ExecuteQuery(const char* query)
{
	sqlQueryStatus = mysql_query(sqlConnection, query);

	if(sqlQueryStatus != 0)
	{
		CString strError = _T("");
		strError = mysql_error(&sqlConnect);
		AfxMessageBox(strError);
	}
	sqlResult = mysql_store_result(sqlConnection);
}