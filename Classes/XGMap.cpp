#include "XGMap.h"
#include "NavigationHandle.h"

USING_NS_CC;

XGMap::XGMap()
	: MapSize(0, 0)
	, TileInfo(NULL)
{
}

XGMap::~XGMap()
{
}

bool XGMap::init(XGGameInitInfo* pInitInfo)
{
	do
	{
		CC_BREAK_IF(!pInitInfo);
		MapSize = pInitInfo->MapSize;
		//TileInfo = dynamic_cast<CCArray*>(pInitInfo->MapTiles->copy());
		//it seems copy doesn't work here
		TileInfo = pInitInfo->MapTiles;
		CC_BREAK_IF(!TileInfo);
		CC_BREAK_IF(int(MapSize.width)*int(MapSize.height) != TileInfo->count());
		TileInfo->retain();

		//debug
		//for (int i = 0; i < TileInfo->count(); i++)
		//{
		//	XGTile* pTile = dynamic_cast<XGTile*>(TileInfo->objectAtIndex(i));
		//	CCLOG("[Debug] TileInfo status %d", pTile->bBlock);
		//}

		return true;
	}
	while (false);

	return false;
}

XGMap* XGMap::create(XGGameInitInfo* pInitInfo)
{
	XGMap* pReturnValue = new XGMap();
	if (pReturnValue)
	{
		if(pReturnValue->init(pInitInfo))
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




CCArray* XGMap::GetTilesWithinRange(TilePoint origin, int range)
{
	XGTile* OriginTile = getTileAt(origin.x, origin.y);
	CCArray* Tiles = CCArray::create();
	CCObject* TileObj = NULL;
	CCARRAY_FOREACH(TileInfo, TileObj)
	{
		XGTile* kTile = dynamic_cast<XGTile*>(TileObj);
		if(kTile->tileDistanceTo(OriginTile) <= range)
		{
			Tiles->addObject(kTile);
		}
	}

	return Tiles;
}


CCArray* XGMap::GetWalkableTileWithinRange(TilePoint origin, int range)
{
	CCArray* TileInRange = GetTilesWithinRange(origin, range);
	CCArray* TileRemove = CCArray::create();
	CCObject* TileObj = NULL;
	CCARRAY_FOREACH(TileInRange, TileObj)
	{
		XGTile* kTile = dynamic_cast<XGTile*>(TileObj);
		if(kTile->bBlock)
		{
			TileRemove->addObject(kTile);
		}
	}

	TileInRange->removeObjectsInArray(TileRemove);

	return TileInRange;
}

std::vector<TilePoint> XGMap::GetAdjacentPos(TilePoint origin)
{
	std::vector<TilePoint> AdjacentPos;
	CCArray* TileInRange = GetWalkableTileWithinRange(origin, 1);
	CCObject* TileObj = NULL;
	CCARRAY_FOREACH(TileInRange, TileObj)
	{
		XGTile* kTile = dynamic_cast<XGTile*>(TileObj);
		if(!kTile->Position.equals(origin))
		{
			AdjacentPos.push_back(kTile->Position);
		}
	}
	return AdjacentPos;
}


void XGMap::SetOccupied(TilePoint Pos)
{
	XGTile* tile = getTileAt(Pos.x, Pos.y);
	tile->bBlock = true;
}

void XGMap::ClearOccupied(TilePoint Pos)
{
	XGTile* tile = getTileAt(Pos.x, Pos.y);
	tile->bBlock = false;
}



//debug
bool XGMap::CheckPath(cocos2d::CCArray* path)
{
	for(int i = 0; i < path->count(); i++)
	{
		TilePoint* pos = dynamic_cast<TilePoint*>(path->objectAtIndex(i));
		XGTile* tile = getTileAt(pos->x, pos->y);
		if(tile->bBlock)
		{
			CCLog("[WARN] path with block!!!!!!!");
			return false;
		}
	}

	return true;
}