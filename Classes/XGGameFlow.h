#ifndef __XG_GAME_FLOW_H__
#define __XG_GAME_FLOW_H__

#include "cocos2d.h"

#include "XGUnit.h"

class XGGameFlow: public cocos2d::CCObject
{
// definition
public:
	enum TurnType
	{
		eTurn_Player,
		eTurn_Enemy,
		eTurn_Neutral
	};

// constructor/destructor
protected:
    XGGameFlow();
    virtual ~XGGameFlow();

// method
public:
	virtual bool init();

	static XGGameFlow* create();

	cocos2d::CCArray* getCurrentTurnUnits();
	XGUnit* getNextActableUnit();

	virtual void updateTurn();
	virtual void finishTurn();

protected:


// member
protected:
	TurnType						CurrentTurn;

	cocos2d::CCArray*				PlayerUnits;
	cocos2d::CCArray*				EnemyUnits;
	cocos2d::CCArray*				NeutralUnits;

	cocos2d::CCArray*				CurrentActableUnits;
};

#endif  // __XG_GAME_FLOW_H__
