#pragma once
#include "ILogicEntry.h"

class SFDatabaseProxy;

class LogicEntry : public ILogicEntry
{
public:
	LogicEntry(void);

	virtual ~LogicEntry(void);

	virtual BOOL ProcessPacket(SFCommand* pCommand);

	SFMessage* GetDBMessage();

	BOOL RecallDBMessage( SFMessage* pMessage );

	void SetLogic(ILogicEntry* pLogic)
	{
		m_pLogicEntry = pLogic;
	}

protected:

private:
	ILogicEntry* m_pLogicEntry;

	SFObjectPool<SFMessage> m_DBMessagePool;
};