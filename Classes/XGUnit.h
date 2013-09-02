#ifndef __XG_UNIT_H__
#define __XG_UNIT_H__

#include "cocos2d.h"

#include "XGGameData.h"
#include "XGGameInfo.h"
#include "NavigationHandle.h"
#include "XGTile.h"
#include "XGDisplay.h"


class XGPlayer;
class XGControlCenter;

class XGUnit: public cocos2d::CCNode
{
// constructor/destructor
public:
    XGUnit();
    virtual ~XGUnit();

// override
public:
	
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);

	virtual bool init(XGGameInfo* info, XGPlayer* Player, TilePoint Pos, const char* Texture);
	static XGUnit* create(XGGameInfo* info, XGPlayer* Player, TilePoint Pos, const char* Texture);


// method
public:
	TilePoint GetPosition();
	virtual void OnPositionChanged(TilePoint NewPos);

	// turn logic
	virtual void BeginTurn();
	virtual void EndTurn();
	virtual void ResetActionPoint();
	virtual bool CheckForEndTurn();
	virtual void OnNormalActionDone(int ap);
	virtual void OnEndTurnActionDone();
	virtual void ActionMove(TilePoint Pos);
	virtual void ActionAttack(XGUnit* target);
	virtual void ActionSkill(XGUnit* target);
	virtual void ActionForceEndTurn();

	void ScheduleMove(float dt);
	

	// battle logic
	virtual void TakeDamage(int DamageAmount, XGUnit* DamageCauser);
	virtual bool Died(XGUnit* Killer);

	// move
	
	virtual cocos2d::CCArray* GetMoveableTiles();
	virtual cocos2d::CCArray* GetAttackableTiles(TilePoint Origin);
	virtual cocos2d::CCArray* GetPotentialAttackableTiles();

	// path-finding
	virtual bool PathFindingMove(TilePoint dest);

	// getter & setter
	int getActionPoint() {return CurActionPoint;}

	// property
	float GetHealthRatio();
	EUnitType getType(){return Type;}


	// test code
	void ScheduleTest(float dt);

// member
public:
	XGControlCenter*				ControlCenter;
	XGGameInfo*						GameInfo;
	EUnitType						Type;
	int								CurActionPoint;
	XGPlayer*						Player;
	cocos2d::CCSprite*				Sprite;
	const char*						Texture;
	TilePoint						Position;

	int								Health;
	int								HealthMax;
	int								Power;
	int								MovePoint;
	int								Range;
	float							Speed;

	bool							bDead;

	NavigationHandle*				Navigation;


};

#endif  // __XG_UNIT_H__
