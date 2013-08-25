#ifndef __XG_TILE_H__
#define __XG_TILE_H__

#include "cocos2d.h"

class XGTilePoint
{
public:
	int x;
	int y;

public:
	XGTilePoint();
	XGTilePoint(int x, int y);
	XGTilePoint(const XGTilePoint& other);
	XGTilePoint& operator = (const XGTilePoint& other);
	void setPoint(int x, int y);
	bool equals(const XGTilePoint& target) const;
};

class XGMapSize
{
public:
	int width;
	int height;

public:
	XGMapSize();
	XGMapSize(int width, int height);
	XGMapSize(const XGMapSize& other);
	XGMapSize& operator = (const XGMapSize& other);
	void setSize(int width, int height);
	bool equals(const XGMapSize& target) const;
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
	virtual bool init(cocos2d::CCPoint position);

// override
public:
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);

// method
public:
	static XGTile* create(cocos2d::CCPoint position);
	static XGTile* createWithXY(int x, int y);

	cocos2d::CCPoint getPosition();
	TileGeoType getGeography();

	int tileDistanceTo(XGTile* pTarget);

// member
protected:
	// position of tile, not in pixel
	cocos2d::CCPoint				Position;
	TileGeoType						Geography;
};

#endif  // __XG_TILE_H__
