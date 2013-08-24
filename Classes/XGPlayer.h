#ifndef __XGPLAYER_H__
#define __XGPLAYER_H__

#include "cocos2d.h"
#include "XGBattle.h"
#include "XGDisplay.h"
#include "XGGameData.h"

class XGBattle;

class XGPlayer : public cocos2d::CCObject
{
	// constructor & destructor
public:
	XGPlayer();
	virtual ~XGPlayer();

	// create & init
public:
	static XGPlayer* create(XGBattle* battle);
	virtual bool init(XGBattle* battle);

	// method
public:
	virtual bool CheckForEndTurn();


	virtual void BeginTurn();
	virtual void EndTurn();
	

	virtual bool SpawnTeam(XGDisplay* Canvas, cocos2d::CCArray* TeamInfo);
	virtual XGUnit* SpawnUnit(EUnitType type, XGDisplay* Canvas, cocos2d::CCPoint& Pos);

	// member
public:
	XGBattle*			Battle;
	cocos2d::CCArray*	Units;


};

#endif