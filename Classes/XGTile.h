#ifndef __XG_TILE_H__
#define __XG_TILE_H__

#include "cocos2d.h"

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

// method
public:
	static XGTile* create(cocos2d::CCPoint position);
	static XGTile* createWithXY(int x, int y);

	cocos2d::CCPoint getPosition();
	TileGeoType getGeography();

	int tileDistanceTo(XGTile* pTarget);

// member
protected:
	cocos2d::CCPoint				Position;
	TileGeoType						Geography;
};

#endif  // __XG_TILE_H__
