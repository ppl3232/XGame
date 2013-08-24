#include "XGTile.h"
#include "XGGameData.h"
USING_NS_CC;

XGTile::XGTile()
	: Position(-1, -1)
	, Geography(eTileGeo_Normal)
	, bBlock(false)	
{
}

XGTile::~XGTile()
{
}

bool XGTile::init(CCPoint position)
{
	do
	{
		Position = position;

		return true;
	}
	while(0);

	return false;
}

CCObject* XGTile::copyWithZone(CCZone* pZone)
{
	XGTile* pReturnValue = new XGTile();
	if (pReturnValue)
	{
		pReturnValue->Position = Position;
		pReturnValue->Geography = Geography;
	}
	return pReturnValue;
}

XGTile* XGTile::create(CCPoint position)
{
	XGTile* pReturnValue = new XGTile();
	if (pReturnValue)
	{
		if (pReturnValue->init(position))
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

XGTile* XGTile::createWithXY(int x, int y)
{
	return create(CCPoint(x, y));
}

int XGTile::tileDistanceTo(XGTile* pTarget)
{
	return GetDistance(Position, pTarget->Position);
}
