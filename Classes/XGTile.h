#ifndef __XG_TILE_H__
#define __XG_TILE_H__

#include "cocos2d.h"

class TilePoint
{
public:
	int x;
	int y;

public:
	TilePoint();
	TilePoint(int x, int y);
	TilePoint(const TilePoint& other);
	TilePoint operator = (const TilePoint other);
	void setPoint(int x, int y);
	bool equals(const TilePoint target) const;
};

#define tile(x,y) TilePoint(x, y)


class TileMapSize
{
public:
	int width;
	int height;

public:
	TileMapSize();
	TileMapSize(int width, int height);
	TileMapSize(const TileMapSize& other);
	TileMapSize& operator = (const TileMapSize& other);
	void setSize(int width, int height);
	bool equals(const TileMapSize& target) const;
	int getTileNum() const;
};

class XGTile: public cocos2d::CCObject
{
// definition
public:
	enum TileGeoType
	{
		eTileGeo_Normal,
		eTileGeo_Haven
	};

// constructor/destructor
public:
    XGTile();
    virtual ~XGTile();

// override
public:
	virtual bool init(TilePoint position);

// override
public:
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);

// method
public:
	static XGTile* create(TilePoint position);
	static XGTile* createWithXY(int x, int y);

	int tileDistanceTo(XGTile* pTarget);

// member
public:
	// position of tile, not in pixel
	TilePoint				Position;
	TileGeoType						Geography;

	bool							bBlock;
};

#endif  // __XG_TILE_H__
