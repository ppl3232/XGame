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

	XGTile* getTileAt(int x, int y);

	unsigned int getSizeX();
	unsigned int getSizeY();
	unsigned int getTileNum();


	cocos2d::CCArray* GetTilesWithinRange(cocos2d::CCPoint origin, int range);

	void SetOccupied(cocos2d::CCPoint& Pos);
	void ClearOccupied(cocos2d::CCPoint& Pos);

	// member
protected:
	cocos2d::CCArray*				TileInfo;

	CC_SYNTHESIZE_PASS_BY_REF(cocos2d::CCSize, MapSize, MapSize);
};

#endif  // __XG_MAP_H__
