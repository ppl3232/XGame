#ifndef __XGPLAYER_H__
#define __XGPLAYER_H__

#include "cocos2d.h"

#include "XGGameData.h"

class XGBattle;
class XGUnit;

class XGPlayer : public cocos2d::CCObject
{
	// constructor & destructor
public:
	XGPlayer();
	virtual ~XGPlayer();

	// create & init
public:
	CREATE_FUNC(XGPlayer);
	virtual bool init();

	// method
public:
	virtual bool CheckForEndTurn();


	virtual void BeginTurn();
	virtual void EndTurn();
	

	virtual bool SpawnTeam(cocos2d::CCArray* TeamInfo);
	virtual XGUnit* SpawnUnit(EUnitType type, cocos2d::CCPoint& Pos);

	// member
public:
	XGBattle*			Battle;
	cocos2d::CCArray*	Units;


};

#endif