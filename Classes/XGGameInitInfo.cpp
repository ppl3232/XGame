#include "XGGameInitInfo.h"

USING_NS_CC;

XGGameInitInfo::XGGameInitInfo()
	: MapSize(10, 10)
	, MapTiles(NULL)
	, Units(NULL)
{
}

XGGameInitInfo::~XGGameInitInfo()
{
}

bool XGGameInitInfo::initDebugInfo()
{
	do
	{
		MapSize.setSize(10, 10);

		MapTiles = CCArray::createWithCapacity(MapSize.getTileNum());
		CC_BREAK_IF(MapTiles);
		for (int i = 0; i < MapSize.getTileNum(); i++)
		{
			XGTile* pTile = XGTile::createWithXY(i%MapSize.width, i/MapSize.width);
			MapTiles->addObject(pTile);
		}
		MapTiles->retain();

		Units = CCArray::create();
		CC_BREAK_IF(Units);
		Units->retain();

		return true;
	}
	while (false);
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

XGGameInitInfo* XGGameInitInfo::createDebugInfo()
{
	XGGameInitInfo* pReturnValue = new XGGameInitInfo();
	if (pReturnValue)
	{
		if (pReturnValue->initDebugInfo())
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
