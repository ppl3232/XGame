#include "XGMap.h"

USING_NS_CC;

XGMap::XGMap()
	: MapSizeX(10)
	, MapSizeY(10)
	, TileInfo(NULL)
{
}

XGMap::~XGMap()
{
}

bool XGMap::init(int mapSizeX, int mapSizeY)
{
	do
	{
		MapSizeX = mapSizeX;
		MapSizeY = mapSizeY;

		unsigned int tileTotalNum = MapSizeX*MapSizeY;
		TileInfo = CCArray::createWithCapacity(tileTotalNum);
		CC_BREAK_IF(!TileInfo);
		// Store in row
		bool initTileFailed = false;
		for (unsigned int i = 0; i < tileTotalNum; i++)
		{
			XGTile* tile = XGTile::createWithXY(i%MapSizeX, i/MapSizeY);
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

XGMap* XGMap::create(int mapSizeX, int mapSizeY)
{
	XGMap* pReturnValue = new XGMap();
	if (pReturnValue && pReturnValue->init(mapSizeX, mapSizeY))
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
	return dynamic_cast<XGTile*>(TileInfo->objectAtIndex(y*MapSizeX+x));
}

unsigned int XGMap::getSizeX()
{
	return MapSizeX;
}

unsigned int XGMap::getSizeY()
{
	return MapSizeY;
}

unsigned int XGMap::getTileNum()
{
	return MapSizeX*MapSizeY;
}
