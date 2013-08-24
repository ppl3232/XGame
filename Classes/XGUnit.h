#ifndef __XG_UNIT_H__
#define __XG_UNIT_H__

#include "cocos2d.h"
#include "XGPlayer.h"
#include "XGDisplay.h"
#include "XGGameData.h"

class XGUnit: public cocos2d::CCObject
{
// constructor/destructor
public:
    XGUnit();
    virtual ~XGUnit();

// override
public:
	
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);
	virtual bool init(XGPlayer* Player, XGDisplay* Canvas, cocos2d::CCPoint& Pos, const char* Texture);
	static XGUnit* create(XGPlayer* Player, XGDisplay* Canvas, cocos2d::CCPoint& Pos, const char* Texture);

// method
public:
	virtual void setPosition(const cocos2d::CCPoint &Pos);
	virtual cocos2d::CCPoint &getPosition();
	// turn logic
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
	

	// battle logic
	virtual void TakeDamage(int DamageAmount, XGUnit* DamageCauser);
	virtual bool Died(XGUnit* Killer);


	// getter & setter
	int getActionPoint() {return CurActionPoint;}

	cocos2d::CCSprite* getSprite();
	EUnitType getType(){return Type;}

// member
public:
	EUnitType						Type;
	int								CurActionPoint;
	XGPlayer*						Player;
	cocos2d::CCSprite*				Sprite;

	cocos2d::CCPoint				Position;
	XGDisplay*						Canvas;

	int								Health;
	int								HealthMax;
	int								Power;
	int								Speed;
	int								Range;

	bool							bDead;


};

#endif  // __XG_UNIT_H__
