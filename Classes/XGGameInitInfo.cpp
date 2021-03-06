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
	if (PlayerUnits)
	{
		PlayerUnits->release();
	}
	if (EnemyUnits)
	{
		EnemyUnits->release();
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

		//debug
		//for (int i = 0; i < MapTiles->count(); i++)
		//{
		//	XGTile* pTile = dynamic_cast<XGTile*>(MapTiles->objectAtIndex(i));
		//	CCLOG("[Debug] MapTiles status %d", pTile->bBlock);
		//}

		PlayerUnits = CCArray::createWithCapacity(PlayerNum);
		CC_BREAK_IF(!PlayerUnits);
		for (int i = 0; i < PlayerNum; i++)
		{
			int randomIndex;
			TilePoint pos;
			do
			{
				randomIndex = rand()%MapSize.getTileNum();
				pos = TilePoint::createFromIndex(randomIndex, MapSize);
				XGTile* pTile = dynamic_cast<XGTile*>(
					MapTiles->objectAtIndex(randomIndex));
				if (pTile && !pTile->bBlock)
				{
					CCObject* pUnitObj = NULL;
					bool posValid = true;
					CCARRAY_FOREACH(PlayerUnits, pUnitObj)
					{
						XGUnitInfo* pUnitInfo = dynamic_cast<XGUnitInfo*>(pUnitObj);
						if (pUnitInfo->SpawnLocation.equals(pos))
						{
							posValid = false;
							break;
						}
					}
					CC_BREAK_IF(posValid);
				}
			}
			while (true);
			XGUnitInfo* pUnitInfo = XGUnitInfo::create(EUT_Footman, pos);
			CC_BREAK_IF(!pUnitInfo);
			PlayerUnits->addObject(pUnitInfo);
		}
		CC_BREAK_IF(PlayerUnits->count() != PlayerNum);
		PlayerUnits->retain();

		EnemyUnits = CCArray::createWithCapacity(EnemyNum);
		CC_BREAK_IF(!EnemyUnits);
		for (int i = 0; i < EnemyNum; i++)
		{
			int randomIndex;
			TilePoint pos;
			do
			{
				randomIndex = rand()%MapSize.getTileNum();
				pos = TilePoint::createFromIndex(randomIndex, MapSize);
				XGTile* pTile = dynamic_cast<XGTile*>(
					MapTiles->objectAtIndex(randomIndex));
				if (pTile && !pTile->bBlock)
				{
					CCObject* pUnitObj = NULL;
					bool posPlayerValid = true;
					CCARRAY_FOREACH(EnemyUnits, pUnitObj)
					{
						XGUnitInfo* pUnitInfo = dynamic_cast<XGUnitInfo*>(pUnitObj);
						if (pUnitInfo->SpawnLocation.equals(pos))
						{
							posPlayerValid = false;
							break;
						}
					}
					bool posEnemyValid = true;
					CCARRAY_FOREACH(EnemyUnits, pUnitObj)
					{
						XGUnitInfo* pUnitInfo = dynamic_cast<XGUnitInfo*>(pUnitObj);
						if (pUnitInfo->SpawnLocation.equals(pos))
						{
							posEnemyValid = false;
							break;
						}
					}
					CC_BREAK_IF(posPlayerValid && posEnemyValid);
				}
			}
			while (true);
			XGUnitInfo* pUnitInfo = XGUnitInfo::create(EUT_Grunt, pos);
			CC_BREAK_IF(!pUnitInfo);
			EnemyUnits->addObject(pUnitInfo);
		}
		CC_BREAK_IF(EnemyUnits->count() != EnemyNum);
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
