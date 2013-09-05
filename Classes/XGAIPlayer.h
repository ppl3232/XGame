#ifndef __XGAIPLAYER_H__
#define __XGAIPLAYER_H__

#include "XGPlayer.h"

class XGAIPlayer : public XGPlayer
{
	// constructor & destructor
public:
	XGAIPlayer();
	virtual ~XGAIPlayer();

	// create & init
public:
	static XGAIPlayer* create(XGControlCenter* controlCenter, XGBattle* battle);
	virtual bool init(XGControlCenter* controlCenter, XGBattle* battle);

	// method
	virtual void BeginTurn();
	virtual void EndTurn();

	//virtual void AITacticsSimple(XGUnit* Unit);

	virtual XGUnit* FindClosestTarget(XGUnit* Unit);
	virtual TilePoint FindClosestPointWithTarget(XGUnit* Unit, XGUnit* Target);
	virtual cocos2d::CCArray* GetCombatInfo(XGUnit* Unit);
	virtual cocos2d::CCArray* GetAllTargets();
	virtual XGAICombatInfo* GetBestCombatInfo(XGUnit* Unit, cocos2d::CCArray* PotentialPos);
	virtual XGPlayer* GetEnemyPlayer();
	virtual float EvaluteCombatInfo(XGUnit* Unit, XGAICombatInfo* info);

	virtual void OnUnitMoveEnd(XGUnit* unit);
	virtual void OnUnitTurnEnd(XGUnit* unit);

	virtual void AIThinking(XGUnit* unit);
	virtual void AIExecuteMove(XGUnit* unit);
	virtual void AIEXecuteAttack(XGUnit* unit);



	virtual XGUnit* GetNextAvailableUnit();

public:

	// member
public:

};

#endif