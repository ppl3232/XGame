#ifndef __XG_GAME_INIT_H__
#define __XG_GAME_INIT_H__

#include "cocos2d.h"

#include "XGTile.h"

class XGGameInitInfo: public cocos2d::CCObject
{
// constructor/destructor
public:
    XGGameInitInfo();
    virtual ~XGGameInitInfo();

// method
public:
	static XGGameInitInfo* create();

// member
public:
	XGMapSize						MapSize;
	cocos2d::CCArray*				MapTiles;
	cocos2d::CCArray*				Units;
};

#endif  // __XG_GAME_INIT_H__
