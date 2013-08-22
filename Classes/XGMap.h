#ifndef __XG_MAP_H__
#define __XG_MAP_H__

#include "cocos2d.h"

#include "XGGameInfo.h"
#include "XGTile.h"

class XGMap: public cocos2d::CCObject
{
// constructor/destructor
public:
    XGMap();
    virtual ~XGMap();

// override
public:
	virtual bool init(int mapSizeX, int mapSizeY);

// method
public:
	static XGMap* create(int mapSizeX, int mapSizeY);

	XGTile* getTileAt(int x, int y);

// member
protected:
	unsigned int					MapSizeX, MapSizeY;
	cocos2d::CCArray*				TileInfo;
};

#endif  // __XG_MAP_H__
