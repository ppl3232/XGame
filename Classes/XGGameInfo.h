#ifndef __XG_GAME_INFO_H__
#define __XG_GAME_INFO_H__

#include "cocos2d.h"

class XGInput;
class XGControlCenter;
class XGDisplay;
class XGMap;
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

	XGInput* getInput();
	XGDisplay* getDisplay();
	XGControlCenter* getControlCenter();
	XGMap* getMap();

// member
protected:
	// input
	XGInput*						GameInput;
	static const int				InputZOrder = 100000;

	// display
	XGDisplay*						GameDisplay;
	static const int				DisplayZOrder = 0;

	// control center
	XGControlCenter*				ControlCenter;

	// map
	XGMap*							Map;
};

#endif  // __XG_GAME_INFO_H__
