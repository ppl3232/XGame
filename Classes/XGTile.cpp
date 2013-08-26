#include "XGTile.h"
#include "XGGameData.h"
USING_NS_CC;

// TilePoint
TilePoint::TilePoint()
{
	setPoint(0, 0);
}

TilePoint::TilePoint(int x, int y)
{
	setPoint(x, y);
}

TilePoint::TilePoint(const TilePoint& other)
{
	setPoint(other.x, other.y);
}

TilePoint TilePoint::operator = (const TilePoint other)
{
	setPoint(other.x, other.y);
	return *this;
}

void TilePoint::setPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool TilePoint::equals(const TilePoint target) const
{
	return (target.x == x && target.y == y);
}


// TileMapSize
TileMapSize::TileMapSize()
{
	setSize(0, 0);
}

TileMapSize::TileMapSize(int width, int height)
{
	setSize(width, height);
}

TileMapSize::TileMapSize(const TileMapSize& other)
{
	setSize(other.width, other.height);
}

TileMapSize& TileMapSize::operator = (const TileMapSize& other)
{
	setSize(other.width, other.height);
	return *this;
}

void TileMapSize::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

bool TileMapSize::equals(const TileMapSize& target) const
{
	return (target.width == width && target.height == height);
}

int TileMapSize::getTileNum() const
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

bool XGTile::init(TilePoint position)
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

XGTile* XGTile::create(TilePoint position)
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
	return create(TilePoint(x, y));
}

int XGTile::tileDistanceTo(XGTile* pTarget)
{
	return GetDistance(Position, pTarget->Position);
}
