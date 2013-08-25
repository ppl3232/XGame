#include "XGTile.h"
#include "XGGameData.h"
USING_NS_CC;

// XGTilePoint
XGTilePoint::XGTilePoint()
{
	setPoint(0, 0);
}

XGTilePoint::XGTilePoint(int x, int y)
{
	setPoint(x, y);
}

XGTilePoint::XGTilePoint(const XGTilePoint& other)
{
	setPoint(other.x, other.y);
}

XGTilePoint& XGTilePoint::operator = (const XGTilePoint& other)
{
	setPoint(other.x, other.y);
	return *this;
}

void XGTilePoint::setPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool XGTilePoint::equals(const XGTilePoint& target) const
{
	return (target.x == x && target.y == y);
}


// XGMapSize
XGMapSize::XGMapSize()
{
	setSize(0, 0);
}

XGMapSize::XGMapSize(int width, int height)
{
	setSize(width, height);
}

XGMapSize::XGMapSize(const XGMapSize& other)
{
	setSize(other.width, other.height);
}

XGMapSize& XGMapSize::operator = (const XGMapSize& other)
{
	setSize(other.width, other.height);
	return *this;
}

void XGMapSize::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

bool XGMapSize::equals(const XGMapSize& target) const
{
	return (target.width == width && target.height == height);
}

int XGMapSize::getTileNum() const
{
	return width*height;
}


// XGTile
XGTile::XGTile()
	: Position(-1, -1)
	, Geography(eTileGeo_Normal)
	, bBlock(false)	
{
}

XGTile::~XGTile()
{
}

bool XGTile::init(cocos2d::CCPoint& position)
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

XGTile* XGTile::create(cocos2d::CCPoint& position)
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
	return create(ccp(x, y));
}

int XGTile::tileDistanceTo(XGTile* pTarget)
{
	return GetDistance(Position, pTarget->Position);
}
