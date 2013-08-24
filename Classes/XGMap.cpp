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
		MapSize.width = floor(MapSize.width);
		MapSize.height = floor(MapSize.height);

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
