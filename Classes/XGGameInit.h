#ifndef __XG_GAME_INIT_H__
#define __XG_GAME_INIT_H__

#include "cocos2d.h"

class XGGameInit: public cocos2d::CCObject
{
// constructor/destructor
public:
    XGGameInit();
    virtual ~XGGameInit();

// member
public:
	cocos2d::CCArray*				Units;
	cocos2d::CCSize					MapSize;
	cocos2d::CCArray*				MapTiles;
};

#endif  // __XG_GAME_INIT_H__
