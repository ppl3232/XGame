#ifndef __XG_UNIT_H__
#define __XG_UNIT_H__

#include "cocos2d.h"
#include "XGPlayer.h"

// definition
enum UnitType
{
	eUnit_Player,
	eUnit_Enemy,
	eUnit_Neutral,
	eUnit_Unknown
};

const int MAX_ACTION_POINT = 2;

class XGUnit: public cocos2d::CCObject
{
// constructor/destructor
public:
    XGUnit();
    virtual ~XGUnit();

// override
public:
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);

// method
public:
	virtual bool init();

	virtual void BeginTurn();
	virtual void EndTurn();
	virtual void ResetActionPoint();
	virtual bool CheckForEndTurn();

	virtual void OnNormalActionDone();
	virtual void OnEndTurnActionDone();
	virtual void ActionMove(XGUnit* target);
	virtual void ActionAttack(XGUnit* target);
	virtual void ActionSkill(XGUnit* target);
	virtual void ActionForceEndTurn();

	

	UnitType getType() {return Type;}
	int getActionPoint() {return CurActionPoint;}

// member
public:
	UnitType						Type;
	int								CurActionPoint;

	XGPlayer*						Player;


};

#endif  // __XG_UNIT_H__
