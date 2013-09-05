#include "XGUnit.h"

#include "XGGameInfo.h"
#include "XGControlCenter.h"
#include "XGPlayer.h"
#include "XGMap.h"

USING_NS_CC;

XGUnit::XGUnit()
	: ControlCenter(NULL)
	, CurActionPoint(0)
	, Type(EUT_Unknow)
	, Player(NULL)
	, Texture(NULL)
	, AICombatInfo(NULL)
	, Health(10)
	, HealthMax(10)
	, MovePoint(2)
	, Power(2)
	, Range(1)
	, Speed(2.0)
	, bDead(false)
{
}

XGUnit::~XGUnit()
{
	//GameInfo->removeChild(this);
	Navigation->release();
	AICombatInfo->release();
}


CCObject* XGUnit::copyWithZone(CCZone* pZone)
{
	return NULL;
}


bool XGUnit::init(XGGameInfo* info, XGPlayer* Player, TilePoint Pos, const char* Texture)
{
	bool ret = false;
	do 
	{
		this->GameInfo = info;
		this->Player = Player;
		this->Position = Pos;
		this->Texture = Texture;
		ControlCenter = info->getControlCenter();
		Navigation = NavigationHandle::create(info);
		CC_BREAK_IF(!Navigation);
		Navigation->retain();

		AICombatInfo = XGAICombatInfo::create();
		AICombatInfo->retain();

		Sprite = CCSprite::create(Texture);
		CC_BREAK_IF(!Sprite);
		
		ControlCenter->spawnUnit(this, Pos);

		// test code

		//info->addChild(this);

		ret = true;
	} while (0);

	return ret;
}




TilePoint XGUnit::GetPosition()
{
	return Position;
}

void XGUnit::SetPosition(TilePoint NewPos)
{
	Position = NewPos;
}

XGUnit* XGUnit::create(XGGameInfo* info, XGPlayer* Player, TilePoint Pos, const char* Texture)
{
	XGUnit* unit = new XGUnit();
	if(unit && unit->init(info, Player, Pos, Texture))
	{
		unit->autorelease();
		return unit;
	}
	else
	{
		CC_SAFE_DELETE(unit);
		return NULL;
	}
}


/**
 * Turn logic
 */
void XGUnit::BeginTurn()
{
	ResetActionPoint();
	AICombatInfo->SetAICombatInfo(EAction_None, TilePoint(0,0), NULL);
}

void XGUnit::EndTurn(){}

void XGUnit::ResetActionPoint()
{
	CurActionPoint = MAX_ACTION_POINT;
}

bool XGUnit::IsAvailable()
{
	return !bDead && CurActionPoint > 0;
}

bool XGUnit::CheckForEndTurn()
{
	return CurActionPoint <= 0;
}

void XGUnit::OnNormalActionDone(int ap)
{

	CurActionPoint -= ap;
	//if(CheckForEndTurn())
	//{
	//	Player->CheckForEndTurn();
	//}
}

void XGUnit::OnEndTurnActionDone()
{
	CurActionPoint = 0;
	//Player->CheckForEndTurn();
}




void XGUnit::ActionSkill(XGUnit* target)
{

};


void XGUnit::ActionForceEndTurn()
{
	CurActionPoint = 0;
};



void XGUnit::TakeDamage(int DamageAmount, XGUnit* DamageCauser)
{
	Health = max(0, Health - DamageAmount);

	if(Health <= 0)
	{
		Died(DamageCauser);
	}
}


bool XGUnit::Died(XGUnit* Killer)
{
	if(bDead)
	{
		return false;
	}

	CCLog("[Unit] died!! %p",this);

	bDead = true;
	ControlCenter->dieUnit(this);
	GameInfo->getMap()->ClearOccupied(Position);
	Player->CheckLose();
	//Player->Units->removeObject(this);
	return true;
}


CCArray* XGUnit::GetMoveableTiles()
{
	CCArray* MoveableTiles = NULL;
	XGMap* map = XGGameInfo::getGameInfo()->getMap();

	MoveableTiles = map->GetTilesWithinRange(Position, MovePoint);


	CCArray* TilesNeedRemove = CCArray::create();

	for(unsigned int i = 0; i < MoveableTiles->count(); i++)
	{
		XGTile* it = dynamic_cast<XGTile*>(MoveableTiles->objectAtIndex(i));
		if(it->Position.equals(Position))
			continue;
		if(it->bBlock || !Navigation->FindPathWithMove(Position, it->Position, MovePoint))
		{
			TilesNeedRemove->addObject(it);
		}
	}

	MoveableTiles->removeObjectsInArray(TilesNeedRemove);

	return MoveableTiles;
}

CCArray* XGUnit::GetAttackableTiles(TilePoint Origin)
{
	XGMap* map = XGGameInfo::getGameInfo()->getMap();
	return map->GetTilesWithinRange(Origin, Range);
}

CCArray* XGUnit::GetPotentialAttackableTiles()
{
	CCArray* PotentialTiles = CCArray::create();
	CCArray* MoveableTiles = GetMoveableTiles();
	for(unsigned int i = 0; i < MoveableTiles->count(); i++)
	{
		XGTile* pTile = dynamic_cast<XGTile*>(MoveableTiles->objectAtIndex(i));
		PotentialTiles->addObjectsFromArray(GetAttackableTiles(pTile->Position));
	}

	return PotentialTiles;
}


float XGUnit::GetHealthRatio()
{
	return float(Health) / HealthMax;
}


/************************************************************************/
/* Path-finding                                                         */
/************************************************************************/


bool XGUnit::PathFindingMove(TilePoint dest)
{
	if(Navigation->FindPathWithMove(Position, dest, MovePoint))
	{
		ControlCenter->potentiallyMoveUnit(this, Navigation->GetPath());
		return true;
	}
	return false;
}


void XGUnit::ActionMove(TilePoint Destination)
{
	if(Navigation->FindPathWithMove(Position, Destination, MovePoint))
	{
		CCLOG("[Game] Path find from %d-%d to %d-%d",Position.x, Position.y, Destination.x,
			Destination.y);
		GameInfo->getMap()->CheckPath(Navigation->GetPath());
		ControlCenter->moveUnit(this, Navigation->GetPath());
		GameInfo->getMap()->ClearOccupied(Position);
		SetPosition(Destination);
		GameInfo->getMap()->SetOccupied(Position);
	}
};

void XGUnit::SetAICombatInfo(XGAICombatInfo* kAICombatInfo)
{
	CCLOG("[Unit] SetCombatInfo %d %p %d %d", kAICombatInfo->AIAction, 
		kAICombatInfo->Target, kAICombatInfo->Position.x, kAICombatInfo->Position.y);

	AICombatInfo->SetAICombatInfo(kAICombatInfo->AIAction, kAICombatInfo->Position, kAICombatInfo->Target);
	
}


void XGUnit::OnActionMoveFinished()
{
	CCLOG("[Game] OnActionMoveFinished %p",this);
	OnNormalActionDone(1);
	Player->OnUnitMoveEnd(this);
}

void XGUnit::ActionAttack(XGUnit* target)
{
	target->TakeDamage(Power, this);
	OnEndTurnActionDone();
	Player->OnUnitTurnEnd(this);
};



