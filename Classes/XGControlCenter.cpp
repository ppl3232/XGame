#include "XGControlCenter.h"

#include "XGUnit.h"
#include "XGDisplay.h"

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

	if (pReturnValue)
	{
		if (pReturnValue->init(pGameInfo))
		{
			pReturnValue->autorelease();
		}
		else
		{
			delete pReturnValue;
			pReturnValue = NULL;
		}
	}

	return pReturnValue;
}

void XGControlCenter::spawnUnit(XGUnit* pUnit, XGTilePoint desPos)
{
	GameInfo->getDisplay()->addTileObject(desPos, pUnit->Texture);
}

void XGControlCenter::moveUnit(XGUnit* pUnit, XGTilePoint desPos)
{
	GameInfo->getDisplay()->moveTileObject(pUnit->GetPosition(), desPos);
}

void XGControlCenter::dieUnit(XGUnit* pUnit)
{
	GameInfo->getDisplay()->removeTileObject(pUnit->GetPosition());
}
