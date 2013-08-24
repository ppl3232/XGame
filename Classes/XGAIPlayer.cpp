#include "XGAIPlayer.h"
#include "XGUnit.h"
#include "XGTile.h"

USING_NS_CC;

XGAIPlayer::XGAIPlayer()
{

}

XGAIPlayer::~XGAIPlayer()
{

}

XGAIPlayer* XGAIPlayer::create(XGBattle* battle)
{
	XGAIPlayer* player = new XGAIPlayer();
	if(player && player->init(battle))
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


bool XGAIPlayer::init(XGBattle* battle)
{
	bool ret = false;
	do 
	{
		XGPlayer::init(battle);
		ret = true;
	} while (0);

	return ret;
}


// ai logic

void XGAIPlayer::BeginTurn()
{
	CCLOG("[Turn] BeginTurn %p", this);
	XGPlayer::BeginTurn();

	for(int i = 0; i < Units->count(); i++)
	{
		XGUnit* kUnit = dynamic_cast<XGUnit*>(Units->objectAtIndex(i));
		AITacticsSimple(kUnit);
	}
	
}

void XGAIPlayer::EndTurn()
{
	//XGPlayer::EndTurn();
	CCLOG("[Turn] EndTurn %p", this);
}


void XGAIPlayer::AITacticsSimple(XGUnit* Unit)
{
	CCLOG("[AI] AITacticsSimple %p", Unit);

	CCArray* PotentialPos = GetAttackPos(Unit);
	if(PotentialPos->count() != 0)
	{
		AttackPos* best = GetBestAttackPos(Unit, PotentialPos);
		Unit->ActionMove(best->Position);
		Unit->ActionAttack(best->Target);
	}
	else
	{
		XGUnit* target = FindClosestTarget(Unit);
		if(target != NULL)
		{
			CCPoint pos = FindClosestPointWithTarget(Unit, target);
			Unit->ActionMove(pos);
			Unit->ActionForceEndTurn();
		}
	}
}

AttackPos* XGAIPlayer::GetBestAttackPos(XGUnit* Unit, cocos2d::CCArray* PotentialPos)
{
	if(PotentialPos == NULL)
		return NULL;

	int MaxScore = 0;
	AttackPos* BestAP = NULL;
	for(int i = 0; i < PotentialPos->count(); i++)
	{
		AttackPos* ap = dynamic_cast<AttackPos*>(PotentialPos->objectAtIndex(i));
		int score = CalAttackPos(Unit, ap);
		if(score > MaxScore)
		{
			MaxScore = score;
			BestAP = ap;
		}

	}

	return BestAP;
}


float XGAIPlayer::CalAttackPos(XGUnit* Unit, AttackPos* ap)
{
	int score = 2.718;

	if(Unit->Power >= ap->Target->Health)
	{
		score *= 1.5;
	}
	else if (ap->Target->GetHealthRatio() < 0.3f)
	{
		score *= 1.2;
	}
	
	return score;
}

CCArray* XGAIPlayer::GetAttackPos(XGUnit* Unit)
{
	CCArray* PotentialPos = CCArray::create();
	CCArray* MoveableTiles = Unit->GetMoveableTiles();
	for(int i = 0; i < MoveableTiles->count(); i++)
	{
		XGTile* mTile = dynamic_cast<XGTile*>(MoveableTiles->objectAtIndex(i));
		CCArray* AttackableTiles = Unit->GetAttackableTiles(mTile->Position);
		for(int j = 0; j < AttackableTiles->count(); j++)
		{
			XGTile* aTile = dynamic_cast<XGTile*>(AttackableTiles->objectAtIndex(j));
			CCArray* AllTargets = GetAllTargets();
			for(int k = 0; k < AllTargets->count(); k++)
			{
				XGUnit* tUnit = dynamic_cast<XGUnit*>(AllTargets->objectAtIndex(k));
				if(tUnit->Position.equals(aTile->Position))
				{
					PotentialPos->addObject(AttackPos::create(mTile->Position, tUnit));
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
	for(int i = 0; i < AllTargets->count(); i++)
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

CCPoint& XGAIPlayer::FindClosestPointWithTarget(XGUnit* Unit, XGUnit* Target)
{
	int MinDis = 1000;
	CCPoint pos;
	CCArray* MoveableTiles = Unit->GetMoveableTiles();
	for(int i = 0; i < MoveableTiles->count(); i++)
	{
		XGTile* tile = dynamic_cast<XGTile*>(MoveableTiles->objectAtIndex(i));
		int dis = GetDistance(tile->Position, Target->Position);
		if(dis < MinDis)
		{
			MinDis = dis;
			pos = tile->Position;
		}
	}

	return ccp(pos.x, pos.y);
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

