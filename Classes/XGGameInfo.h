#ifndef __XG_GAME_INFO_H__
#define __XG_GAME_INFO_H__

#include "cocos2d.h"

/*
 * code standard:
 * Generally use CamelCase,
 * local variables and function use lower case CamelCase,
 * class member use upper case CamelCase
 * bool class member use upper case CamelCase with a 'b' prefix (e.g. bShot)
 */

class XGGameInitInfo;
class XGControlCenter;
class XGGameFlow;
class XGMap;
class XGInput;
class XGDisplay;
class XGBattle;
class XGPlayer;
class XGAIPlayer;

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

	XGGameInitInfo* getGameInitInfo(const char* filename);

	XGInput* getInput();
	XGDisplay* getDisplay();
	XGControlCenter* getControlCenter();
	XGMap* getMap();

	bool InitBattle();
	void DestoryBattle();


	// config function 
	cocos2d::CCArray* getHumanTeam(int num);
	cocos2d::CCArray* getOrcTeam(int num);


// member
protected:
	// control center
	XGControlCenter*				ControlCenter;

	// game flow (turn based)
	XGGameFlow*						GameFlow;

	// map
	XGMap*							Map;

	// input
	XGInput*						GameInput;
	static const int				InputZOrder = 100000;

	// display
	XGDisplay*						GameDisplay;
	static const int				DisplayZOrder = 0;

	// battle
	XGBattle*						Battle;
};

#endif  // __XG_GAME_INFO_H__
