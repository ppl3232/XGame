#include "XGMap.h"

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
		TileInfo = dynamic_cast<CCArray*>(pInitInfo->MapTiles->copy());
		CC_BREAK_IF(!TileInfo);
		CC_BREAK_IF(int(MapSize.width)*int(MapSize.height) != TileInfo->count());
		TileInfo->retain();

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

CCArray* XGMap::GetTilesWithinRange(XGTilePoint origin, int range)
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

void XGMap::SetOccupied(XGTilePoint Pos)
{
	XGTile* tile = getTileAt(Pos.x, Pos.y);
	tile->bBlock = true;
}

void XGMap::ClearOccupied(XGTilePoint Pos)
{
	XGTile* tile = getTileAt(Pos.x, Pos.y);
	tile->bBlock = false;
}
