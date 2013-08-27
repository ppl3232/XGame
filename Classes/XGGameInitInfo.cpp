#include "XGGameInitInfo.h"

USING_NS_CC;

XGGameInitInfo::XGGameInitInfo()
	: MapSize(0, 0)
	, MapTiles(NULL)
	, PlayerUnits(NULL)
	, EnemyUnits(NULL)
{
}

XGGameInitInfo::~XGGameInitInfo()
{
	if (MapTiles)
	{
		MapTiles->release();
	}
}

bool XGGameInitInfo::initDebug()
{
	do
	{
		MapSize = TileMapSize(10, 10);
		int EnemyNum = 2,
			PlayerNum = 2;

		MapTiles = CCArray::createWithCapacity(MapSize.getTileNum());
		CC_BREAK_IF(!MapTiles);
		float blockPercent = 0.1f; // 10% to block
		for (int i = 0; i < MapSize.getTileNum(); i++)
		{
			XGTile* pTile = XGTile::create(TilePoint::createFromIndex(i, MapSize));
			CC_BREAK_IF(!pTile);
			if (CCRANDOM_0_1() <= blockPercent)
			{
				pTile->bBlock = true;
			}
			MapTiles->addObject(pTile);
		}
		MapTiles->retain();

		PlayerUnits = CCArray::createWithCapacity(PlayerNum);
		CC_BREAK_IF(!PlayerUnits);
		//for (int i = 0; i < PlayerNum; i++)
		//{
		//	int randomIndex = rand()%MapSize.getTileNum();
		//	TilePoint pos;

		//	pos = TilePoint::createFromIndex(randomIndex, MapSize)
		//	XGUnitInfo* pUnitInfo = XGUnitInfo::create(
		//		EUT_Footman, );
		//	CC_BREAK_IF(!pUnitInfo);
		//	PlayerUnits->addObject(pUnitInfo);
		//}
		//CC_BREAK_IF(PlayerUnits.count() != PlayerNum);
		PlayerUnits->retain();

		EnemyUnits = CCArray::createWithCapacity(EnemyNum);
		CC_BREAK_IF(!PlayerUnits);
		//for (int i = 0; i < PlayerNum; i++)
		//{
		//	int randomIndex = rand()%MapSize.getTileNum();
		//	TilePoint pos;

		//	pos = TilePoint::createFromIndex(randomIndex, MapSize)
		//	XGUnitInfo* pUnitInfo = XGUnitInfo::create(
		//		EUT_Footman, );
		//	CC_BREAK_IF(!pUnitInfo);
		//	PlayerUnits->addObject(pUnitInfo);
		//}
		//CC_BREAK_IF(PlayerUnits.count() != PlayerNum);
		EnemyUnits->retain();

		return true;
	}
	while(false);
	return false;
}

XGGameInitInfo* XGGameInitInfo::create()
{
	XGGameInitInfo* pReturnValue = new XGGameInitInfo();
	if (pReturnValue)
	{
		pReturnValue->autorelease();
	}
	return pReturnValue;
}

XGGameInitInfo* XGGameInitInfo::createDebug()
{
	XGGameInitInfo* pReturnValue = new XGGameInitInfo();
	if (pReturnValue)
	{
		if (pReturnValue->initDebug())
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
