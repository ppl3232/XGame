#ifndef __XG_UNIT_H__
#define __XG_UNIT_H__

#include "cocos2d.h"
#include "XGPlayer.h"
#include "XGDisplay.h"
#include "XGGameData.h"

class XGPlayer;

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
	virtual void SetPosition(cocos2d::CCPoint &Pos);
	virtual cocos2d::CCPoint &getPosition();
	virtual void OnPositionChange(cocos2d::CCPoint& OldPos);

	// turn logic
	virtual void BeginTurn();
	virtual void EndTurn();
	virtual void ResetActionPoint();
	virtual bool CheckForEndTurn();
	virtual void OnNormalActionDone(int ap);
	virtual void OnEndTurnActionDone();
	virtual void ActionMove(cocos2d::CCPoint& Pos);
	virtual void ActionAttack(XGUnit* target);
	virtual void ActionSkill(XGUnit* target);
	virtual void ActionForceEndTurn();
	

	// battle logic
	virtual void TakeDamage(int DamageAmount, XGUnit* DamageCauser);
	virtual bool Died(XGUnit* Killer);

	// move
	
	virtual cocos2d::CCArray* GetMoveableTiles();
	virtual cocos2d::CCArray* GetAttackableTiles(cocos2d::CCPoint& Origin);
	virtual cocos2d::CCArray* GetPotentialAttackableTiles();

	// getter & setter
	int getActionPoint() {return CurActionPoint;}

	cocos2d::CCSprite* getSprite();

	// property
	float GetHealthRatio();
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
