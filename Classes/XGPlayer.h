#ifndef __XGPLAYER_H__
#define __XGPLAYER_H__

#include "cocos2d.h"

#include "XGGameData.h"
#include "XGGameInfo.h"

#include "XGBattle.h"

class XGControlCenter;
class XGUnit;

class XGPlayer : public cocos2d::CCObject
{
	// constructor & destructor
public:
	XGPlayer();
	virtual ~XGPlayer();

	// create & init
public:
	static XGPlayer* create(XGControlCenter* controlCenter, XGBattle* battle);
	virtual bool init(XGControlCenter* controlCenter, XGBattle* battle);

	// method
public:
	virtual bool CheckForEndTurn();


	virtual void BeginTurn();
	virtual void EndTurn();
	
	virtual bool SpawnTeam(XGGameInfo* info, cocos2d::CCArray* TeamInfo);
	virtual XGUnit* SpawnUnit(XGGameInfo* info, EUnitType type, TilePoint Pos);

	virtual void OnUnitMoveEnd(XGUnit* unit);
	virtual void OnUnitTurnEnd(XGUnit* unit);


	// member
public:
	XGControlCenter*	ControlCenter;
	XGBattle*			Battle;
	cocos2d::CCArray*	Units;
};

#endif