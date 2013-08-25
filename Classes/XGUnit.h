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

class XGUnit: public cocos2d::CCObject
{
// constructor/destructor
public:
    XGUnit();
    virtual ~XGUnit();

// override
public:
	
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);

	virtual bool init(XGGameInfo* info, XGPlayer* Player, cocos2d::CCPoint& Pos, const char* Texture);
	static XGUnit* create(XGGameInfo* info, XGPlayer* Player, cocos2d::CCPoint& Pos, const char* Texture);


// method
public:
	cocos2d::CCPoint& GetPosition();
	virtual void OnPositionChanged(cocos2d::CCPoint& NewPos);

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

	// path-finding
	virtual bool PathFindingMove(cocos2d::CCPoint& dest);

	// getter & setter
	int getActionPoint() {return CurActionPoint;}

	// property
	float GetHealthRatio();
	EUnitType getType(){return Type;}

// member
public:
	XGControlCenter*				ControlCenter;
	XGGameInfo*						GameInfo;
	EUnitType						Type;
	int								CurActionPoint;
	XGPlayer*						Player;
	cocos2d::CCSprite*				Sprite;
	const char*						Texture;
	XGDisplay*						Canvas;
	cocos2d::CCPoint				Position;

	int								Health;
	int								HealthMax;
	int								Power;
	int								Move;
	int								Range;

	bool							bDead;

	NavigationHandle*				Navigation;


};

#endif  // __XG_UNIT_H__
