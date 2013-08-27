#ifndef __XG_GAME_INIT_H__
#define __XG_GAME_INIT_H__

#include "cocos2d.h"

#include "XGGameData.h"

class XGGameInitInfo: public cocos2d::CCObject
{
// constructor/destructor
public:
    XGGameInitInfo();
    virtual ~XGGameInitInfo();

// method
public:
	virtual bool initDebug();

public:
	static XGGameInitInfo* create();
	static XGGameInitInfo* createDebug();

// member
public:
	TileMapSize						MapSize;
	// storage XGTile
	cocos2d::CCArray*				MapTiles;
	// storage XGUnitInfo
	cocos2d::CCArray*				PlayerUnits;
	// storage XGUnitInfo
	cocos2d::CCArray*				EnemyUnits;
};

#endif  // __XG_GAME_INIT_H__
