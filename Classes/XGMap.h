#ifndef __XG_MAP_H__
#define __XG_MAP_H__

#include "cocos2d.h"

#include "XGGameInitInfo.h"
#include "XGTile.h"

class XGMap: public cocos2d::CCObject
{
// constructor/destructor
public:
    XGMap();
    virtual ~XGMap();

// override
public:
	virtual bool init(XGGameInitInfo* pInitInfo);

// method
public:
	static XGMap* create(XGGameInitInfo* pInitInfo);

	XGTile* getTileAt(int x, int y)
	{
		return dynamic_cast<XGTile*>(
			TileInfo->objectAtIndex(y*MapSize.width+x));		
	}

	XGMapSize getMapSize()
	{
		return MapSize;
	}


// member
protected:
	XGMapSize						MapSize;
	cocos2d::CCArray*				TileInfo;
};

#endif  // __XG_MAP_H__
