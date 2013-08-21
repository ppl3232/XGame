#ifndef __XG_GAME_SCENE_H__
#define __XG_GAME_SCENE_H__

#include "cocos2d.h"

class XGGameScene: public cocos2d::CCScene
{
// constructor/destructor
public:
    XGGameScene();
    virtual ~XGGameScene();

// override
public:
	virtual bool init();

// method
public:
	CREATE_FUNC(XGGameScene);
};

#endif  // __XG_GAME_SCENE_H__

