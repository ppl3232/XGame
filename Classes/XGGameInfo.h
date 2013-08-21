#ifndef __XG_GAME_INFO_H__
#define __XG_GAME_INFO_H__

#include "cocos2d.h"

class XGInput;
class XGControlCenter;
class XGGameInfo: public cocos2d::CCLayer
{
// constructor/destructor
public:
    XGGameInfo();
    virtual ~XGGameInfo();

// override
public:
	virtual bool init();

// method
public:
	CREATE_FUNC(XGGameInfo);

// member
protected:
	// input
	XGInput*						GameInput;
	static const int				InputZOrder = 100000;

	// control center
	XGControlCenter*				ControlCenter;
};

#endif  // __XG_GAME_INFO_H__
