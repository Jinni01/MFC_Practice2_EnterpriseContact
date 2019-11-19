
// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// EnterpriseContact.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

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