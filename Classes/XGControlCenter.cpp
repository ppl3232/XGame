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

void XGControlCenter::spawnUnit(XGUnit* pUnit, TilePoint desPos)
{
	GameInfo->getDisplay()->addTileObject(desPos, pUnit->Texture);
}

//void XGControlCenter::moveUnit(XGUnit* pUnit, TilePoint desPos)
//{
//	GameInfo->getDisplay()->moveTileObject(pUnit->GetPosition(), desPos);
//}


void XGControlCenter::moveUnit(XGUnit* pUnit, CCArray* Path)
{
	GameInfo->getDisplay()->moveTileObject(pUnit, Path);
}

void XGControlCenter::dieUnit(XGUnit* pUnit)
{
	if(!GameInfo->getDisplay()->removeTileObject(pUnit->GetPosition()))
	{
		CCLog("[warn] remove unit failed %d %d",pUnit->GetPosition().x, pUnit->GetPosition().y);

	}
}

void XGControlCenter::potentiallyMoveUnit(XGUnit* pUnit, CCArray* desPos)
{
	GameInfo->getDisplay()->debugDrawPath(desPos);
}
