#ifndef __XG_UNIT_H__
#define __XG_UNIT_H__

#include "cocos2d.h"

#include "XGGameData.h"
#include "XGTile.h"

class XGPlayer;
class XGControlCenter;

class XGUnit: public cocos2d::CCObject
{
// constructor/destructor
public:
    XGUnit();
    virtual ~XGUnit();

// override
public:
	
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);
	virtual bool init(XGControlCenter* ControlCenter, XGPlayer* Player, XGTilePoint Pos, const char* Texture);
	static XGUnit* create(XGControlCenter* ControlCenter, XGPlayer* Player, XGTilePoint Pos, const char* Texture);

// method
public:
	XGTilePoint& GetPosition();
	virtual void OnPositionChanged(XGTilePoint NewPos);

	// turn logic
	virtual void BeginTurn();
	virtual void EndTurn();
	virtual void ResetActionPoint();
	virtual bool CheckForEndTurn();
	virtual void OnNormalActionDone(int ap);
	virtual void OnEndTurnActionDone();
	virtual void ActionMove(XGTilePoint Pos);
	virtual void ActionAttack(XGUnit* target);
	virtual void ActionSkill(XGUnit* target);
	virtual void ActionForceEndTurn();
	

	// battle logic
	virtual void TakeDamage(int DamageAmount, XGUnit* DamageCauser);
	virtual bool Died(XGUnit* Killer);

	// move
	
	virtual cocos2d::CCArray* GetMoveableTiles();
	virtual cocos2d::CCArray* GetAttackableTiles(XGTilePoint Origin);
	virtual cocos2d::CCArray* GetPotentialAttackableTiles();

	// getter & setter
	int getActionPoint() {return CurActionPoint;}

	// property
	float GetHealthRatio();
	EUnitType getType(){return Type;}

// member
public:
	XGControlCenter*				ControlCenter;

	EUnitType						Type;
	int								CurActionPoint;
	XGPlayer*						Player;

	const char*						Texture;

	XGTilePoint						Position;

	int								Health;
	int								HealthMax;
	int								Power;
	int								Speed;
	int								Range;

	bool							bDead;


};

#endif  // __XG_UNIT_H__
