#include "XGControlCenter.h"

USING_NS_CC;

XGControlCenter::XGControlCenter()
	: GameInfo(NULL)
{
}

XGControlCenter::~XGControlCenter()
{
}

bool XGControlCenter::init(XGGameInfo* pGameInfo)
{
	do
	{
		GameInfo = pGameInfo;
		return true;
	}
	while (false);

	return false;
}

XGControlCenter* XGControlCenter::create(XGGameInfo* pGameInfo)
{
	XGControlCenter* pReturnValue = new XGControlCenter();

	if (pReturnValue && pReturnValue->init(pGameInfo))
	{
		pReturnValue->autorelease();
	}
	else
	{
		if (pReturnValue)
		{
			delete pReturnValue;
		}
		pReturnValue = NULL;
	}

	return pReturnValue;
}
