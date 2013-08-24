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
	static XGAIPlayer* create(XGBattle* battle);
	virtual bool init(XGBattle* battle);

	// method
	virtual void BeginTurn();
	virtual void EndTurn();

	virtual void AITacticsSimple(XGUnit* Unit);

	virtual XGUnit* FindClosestTarget(XGUnit* Unit);
	virtual cocos2d::CCPoint& FindClosestPointWithTarget(XGUnit* Unit, XGUnit* Target);
	virtual cocos2d::CCArray* GetAttackPos(XGUnit* Unit);
	virtual cocos2d::CCArray* GetAllTargets();
	virtual AttackPos* GetBestAttackPos(XGUnit* Unit, cocos2d::CCArray* PotentialPos);
	virtual XGPlayer* GetEnemyPlayer();
	virtual float CalAttackPos(XGUnit* Unit, AttackPos* ap);

public:

	// member
public:

};

#endif