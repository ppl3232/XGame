#include "XGTile.h"

USING_NS_CC;

XGTile::XGTile()
	: Position(-1, -1)
	, Geography(eTileGeo_Normal)
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

XGTile* XGTile::create(CCPoint position)
{
	XGTile* pReturnValue = new XGTile();
	if (pReturnValue && pReturnValue->init(position))
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

XGTile* XGTile::createWithXY(int x, int y)
{
	return create(CCPoint(x, y));
}

int XGTile::tileDistanceTo(XGTile* pTarget)
{
	return static_cast<int>(Position.x - pTarget->Position.x + Position.y - pTarget->Position.y);
}
