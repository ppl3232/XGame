#ifndef __XG_GAME_SCENE_H__
#define __XG_GAME_SCENE_H__

#include "cocos2d.h"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  XGGameScene : private cocos2d::CCScene
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

