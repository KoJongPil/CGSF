#include "stdafx.h"
#include "SFMySQLAdaptorImpl.h"
#include "SFMySQL.h"
#include "MySQLPool.h"
#include "DBMsg.h"
#include "SFSendDBRequest.h"

SFMySQLAdaptorImpl::SFMySQLAdaptorImpl(void)
{
	
}


SFMySQLAdaptorImpl::~SFMySQLAdaptorImpl(void)
{
	
}

BOOL SFMySQLAdaptorImpl::RegisterDBService()
{
	m_Dispatch.RegisterMessage(DBMSG_LOGIN, std::tr1::bind(&SFMySQLAdaptorImpl::OnLogin, this, std::tr1::placeholders::_1));

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
BOOL SFMySQLAdaptorImpl::OnLogin( BasePacket* pPacket )
{
	SFMySQL* pMySQL = GetObject();
	MySQLPool* pMySqlPool = pMySQL->GetMySqlPool();
	SFMessage* pMessage = (SFMessage*)pPacket;

	int Result = -1;
	char userName[100];
	char password[100];
	*pMessage >> userName;
	*pMessage >> password;
	char szQuery[100];
	sprintf_s(szQuery, "SELECT * FROM tblLogin WHERE UserName = '%s' AND Password = '%s'", userName, password);

	sql::Connection *con;
	sql::Statement* stmt;
	sql::ResultSet* res;

	/*Get a connection from the pool*/
	if((con= pMySqlPool->GetConnectionFromPool()) == 0)
	{
		LOG(ERROR) << "mysql connection get fail!!";
		return FALSE;
	}
	
	con->setSchema("test");
	stmt = con->createStatement();
	res = stmt->executeQuery(szQuery);
	
	if(1 == res->rowsCount())
		Result = 0;

	delete res;
	delete stmt;

	/*Release the connection back into the pool*/
	pMySqlPool->ReleaseConnectionToPool(con);

////////////////////////////////////////////////////////////////////////////////
//����� ���� ������� ������ �� ���
////////////////////////////////////////////////////////////////////////////////
	SFMessage* pMsg = SFDatabase::GetInitMessage(pMessage->GetCommand(), pMessage->GetOwnerSerial());
	*pMsg << Result;
	SFSendDBRequest::SendToLogic(pMsg);
	
	return TRUE;
}
