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

	cocos2d::CCArray* GetTilesWithinRange(cocos2d::CCPoint& origin, int range);
	cocos2d::CCArray* GetWalkableTileWithinRange(cocos2d::CCPoint& origin, int range);
	std::vector<cocos2d::CCPoint> GetAdjacentPos(cocos2d::CCPoint& origin);

	void SetOccupied(cocos2d::CCPoint& Pos);
	void ClearOccupied(cocos2d::CCPoint& Pos);

	// member
public:

	XGMapSize						MapSize;
	cocos2d::CCArray*				TileInfo;
};

#endif  // __XG_MAP_H__
