#include "XGMap.h"

USING_NS_CC;

XGMap::XGMap()
	: TileNumX(10)
	, TileNumY(10)
	, TileInfo(NULL)
{
}

XGMap::~XGMap()
{
}

bool XGMap::init()
{
	do
	{
		unsigned int tileTotalNum = TileNumX*TileNumY;
		TileInfo = CCArray::createWithCapacity(tileTotalNum);
		CC_BREAK_IF(!TileInfo);
		// Store in row
		bool initTileFailed = false;
		for (unsigned int i = 0; i < tileTotalNum; i++)
		{
			XGTile* tile = XGTile::createWithXY(i%TileNumX, i/TileNumX);
			if (tile == NULL)
			{
				initTileFailed = true;
				break;
			}
			TileInfo->addObject(tile);
		}
		CC_BREAK_IF(initTileFailed);
		TileInfo->retain();

		return true;
	}
	while (false);

	return false;
}

XGMap* XGMap::create()
{
	XGMap* pReturnValue = new XGMap();
	if (pReturnValue && pReturnValue->init())
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

XGTile* XGMap::getTileAt(int x, int y)
{
	return dynamic_cast<XGTile*>(TileInfo->objectAtIndex(y*TileNumX+x));
}
