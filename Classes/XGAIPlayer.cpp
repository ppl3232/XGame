#include "XGAIPlayer.h"

#include "XGPlayer.h"
#include "XGUnit.h"
#include "XGTile.h"

USING_NS_CC;

XGAIPlayer::XGAIPlayer()
{

}

XGAIPlayer::~XGAIPlayer()
{

}

XGAIPlayer* XGAIPlayer::create(XGControlCenter* controlCenter, XGBattle* battle)
{
	XGAIPlayer* player = new XGAIPlayer();
	if(player && player->init(controlCenter, battle))
	{
		player->autorelease();
		return player;
	}
	else
	{
		CC_SAFE_DELETE(player);
		return NULL;
	}
}


bool XGAIPlayer::init(XGControlCenter* controlCenter, XGBattle* battle)
{
	bool ret = false;
	do 
	{
		XGPlayer::init(controlCenter, battle);
		ret = true;
	} while (0);

	return ret;
}


// ai logic

void XGAIPlayer::BeginTurn()
{
	CCLOG("[Turn] BeginTurn %p", this);
	XGPlayer::BeginTurn();
	
	XGUnit* NextActionUnit = GetNextAvailableUnit();
	if(NextActionUnit != NULL)
	{
		AIThinking(NextActionUnit);
		AIExecuteMove(NextActionUnit);
	}
	else
	{
		EndTurn();
	}
	
}

void XGAIPlayer::AIThinking(XGUnit* unit)
{
	CCLOG("[Game] AIThinking");

	CCArray* PossibleInfo = GetCombatInfo(unit);
	if(PossibleInfo->count() != 0)
	{
		XGAICombatInfo* info = GetBestCombatInfo(unit, PossibleInfo);
		info->SetAIAction(EAction_MoveAttack);
		unit->SetAICombatInfo(info);
	}
	else
	{
		XGUnit* target = FindClosestTarget(unit);
		if(target != NULL)
		{
			XGAICombatInfo* info = XGAICombatInfo::create();
			TilePoint pos = FindClosestPointWithTarget(unit, target);
			info->SetAICombatInfo(EAction_Approach, pos, NULL);
			unit->SetAICombatInfo(info);
		}
	}
}

void XGAIPlayer::AIExecuteMove(XGUnit* unit)
{
	XGAICombatInfo* info = unit->GetAICombatInfo();

	CCLOG("[Game] AIExecuteMove %p %d-%d",unit,info->Position.x, info->Position.y);

	if(info != NULL)
	{
		unit->ActionMove(info->Position);
	}
	else
	{
		CCLOG("[Warn] info == null");
		unit->ActionForceEndTurn();
		OnUnitTurnEnd(unit);
	}
}

void XGAIPlayer::AIEXecuteAttack(XGUnit* unit)
{
	XGAICombatInfo* info = unit->GetAICombatInfo();

	CCLOG("[Game] AIEXecuteAttack %p %p",unit,info);

	if(info != NULL)
	{
		unit->ActionAttack(info->Target);
	}
	else
	{
		CCLOG("[Warn] info == null");
		unit->ActionForceEndTurn();
		OnUnitTurnEnd(unit);
	}
}

void XGAIPlayer::OnUnitMoveEnd(XGUnit* unit)
{
	XGAICombatInfo* info = unit->GetAICombatInfo();
	if(info->AIAction == EAction_MoveAttack)
	{
		AIEXecuteAttack(unit);
	}
	else if(info->AIAction == EAction_Approach)
	{
		unit->ActionForceEndTurn();
		OnUnitTurnEnd(unit);
	}
	else
	{
		CCLOG("[Warn] AIAction == null");
		unit->ActionForceEndTurn();
		OnUnitTurnEnd(unit);
	}
}


void XGAIPlayer::OnUnitTurnEnd(XGUnit* unit)
{
	CCLOG("[AI] OnUnitTurnEnd %p",unit);
	XGUnit* NextActionUnit = GetNextAvailableUnit();
	if(NextActionUnit != NULL)
	{
		AIThinking(NextActionUnit);
		AIExecuteMove(NextActionUnit);
	}
	else
	{
		EndTurn();
	}
}

XGUnit* XGAIPlayer::GetNextAvailableUnit()
{
	CCLOG("[Game] GetNextAvailableUnit");

	for(unsigned int i = 0; i < Units->count(); i++)
	{
		XGUnit* kUnit = dynamic_cast<XGUnit*>(Units->objectAtIndex(i));
		if(kUnit->IsAvailable())
		{
			return kUnit;
		}
	}



	return NULL;
}



void XGAIPlayer::EndTurn()
{
	XGPlayer::EndTurn();
	CCLOG("[Turn] EndTurn %p", this);
}






XGAICombatInfo* XGAIPlayer::GetBestCombatInfo(XGUnit* Unit, cocos2d::CCArray* PotentialPos)
{
	if(PotentialPos == NULL)
		return NULL;

	int MaxScore = 0;
	XGAICombatInfo* BestInfo = NULL;
	for(unsigned int i = 0; i < PotentialPos->count(); i++)
	{
		XGAICombatInfo* info = dynamic_cast<XGAICombatInfo*>(PotentialPos->objectAtIndex(i));
		int score = EvaluteCombatInfo(Unit, info);
		if(score > MaxScore)
		{
			MaxScore = score;
			BestInfo = info;
		}

	}

	return BestInfo;
}


float XGAIPlayer::EvaluteCombatInfo(XGUnit* Unit, XGAICombatInfo* info)
{
	int score = 2.718;

	if(Unit->Power >= info->Target->Health)
	{
		score *= 1.5;
	}
	else if (info->Target->GetHealthRatio() < 0.3f)
	{
		score *= 1.2;
	}
	
	return score;
}

CCArray* XGAIPlayer::GetCombatInfo(XGUnit* Unit)
{
	CCArray* PotentialPos = CCArray::create();
	CCArray* MoveableTiles = Unit->GetMoveableTiles();
	for(unsigned int i = 0; i < MoveableTiles->count(); i++)
	{
		XGTile* mTile = dynamic_cast<XGTile*>(MoveableTiles->objectAtIndex(i));
		CCArray* AttackableTiles = Unit->GetAttackableTiles(mTile->Position);
		for(unsigned int j = 0; j < AttackableTiles->count(); j++)
		{
			XGTile* aTile = dynamic_cast<XGTile*>(AttackableTiles->objectAtIndex(j));
			CCArray* AllTargets = GetAllTargets();
			for(unsigned int k = 0; k < AllTargets->count(); k++)
			{
				XGUnit* tUnit = dynamic_cast<XGUnit*>(AllTargets->objectAtIndex(k));
				if(tUnit->Position.equals(aTile->Position))
				{
					XGAICombatInfo* info = XGAICombatInfo::create();
					info->SetAICombatInfo(EAction_None, mTile->Position, tUnit);
					PotentialPos->addObject(info);
				}
			}
		}

	}

	return PotentialPos;

}



XGUnit* XGAIPlayer::FindClosestTarget(XGUnit* Unit)
{
	XGUnit* ClosestTarget = NULL;
	int MinDis = 1000;
	CCArray* AllTargets = GetAllTargets();
	for(unsigned int i = 0; i < AllTargets->count(); i++)
	{
		XGUnit* kUnit = dynamic_cast<XGUnit*>(AllTargets->objectAtIndex(i));
		int dis = GetDistance(kUnit->Position, Unit->Position);
		if(dis < MinDis)
		{
			MinDis = dis;
			ClosestTarget = kUnit;
		}
	}

	return ClosestTarget;
}

TilePoint XGAIPlayer::FindClosestPointWithTarget(XGUnit* Unit, XGUnit* Target)
{
	int MinDis = 1000;
	TilePoint pos;
	CCArray* MoveableTiles = Unit->GetMoveableTiles();
	for(unsigned int i = 0; i < MoveableTiles->count(); i++)
	{
		XGTile* tile = dynamic_cast<XGTile*>(MoveableTiles->objectAtIndex(i));
		int dis = GetDistance(tile->Position, Target->Position);
		if(dis < MinDis)
		{
			MinDis = dis;
			pos = tile->Position;
		}
	}

	return TilePoint(pos.x, pos.y);
}




CCArray* XGAIPlayer::GetAllTargets()
{
	XGPlayer* Player = GetEnemyPlayer();
	return Player->Units;
}

XGPlayer* XGAIPlayer::GetEnemyPlayer()
{
	CCObject* PlayerObj = NULL;
	CCARRAY_FOREACH(Battle->arrPlayers, PlayerObj)
	{
		XGPlayer* Player = dynamic_cast<XGPlayer*>(PlayerObj);
		if(this != Player)
		{
			return Player;
		}
	}

	return NULL;
}

