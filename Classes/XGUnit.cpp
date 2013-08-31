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
	, Health(10)
	, HealthMax(10)
	, Move(2)
	, Power(2)
	, Range(1)
	, bDead(false)
{
}

XGUnit::~XGUnit()
{
	Navigation->release();
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
		
		this->Player = Player;
		this->Position = Pos;
		this->Texture = Texture;
		ControlCenter = info->getControlCenter();
		Navigation = NavigationHandle::create(info);
		CC_BREAK_IF(!Navigation);
		Navigation->retain();

		Sprite = CCSprite::create(Texture);
		CC_BREAK_IF(!Sprite);
		
		ControlCenter->spawnUnit(this, Pos);

		ret = true;
	} while (0);

	return ret;
}

TilePoint XGUnit::GetPosition()
{
	return Position;
}

void XGUnit::OnPositionChanged(TilePoint NewPos)
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
}

void XGUnit::EndTurn(){}

void XGUnit::ResetActionPoint()
{
	CurActionPoint = MAX_ACTION_POINT;
}

bool XGUnit::CheckForEndTurn()
{
	return CurActionPoint <= 0;
}

void XGUnit::OnNormalActionDone(int ap)
{
	CurActionPoint -= ap;
	if(CheckForEndTurn())
	{
		Player->CheckForEndTurn();
	}
}

void XGUnit::OnEndTurnActionDone()
{
	CurActionPoint = 0;
	Player->CheckForEndTurn();
}

void XGUnit::ActionMove(TilePoint Pos)
{
	ControlCenter->moveUnit(this, Pos);
	OnNormalActionDone(1);
};

void XGUnit::ActionAttack(XGUnit* target)
{
	target->TakeDamage(Power, this);
	OnEndTurnActionDone();
};


void XGUnit::ActionSkill(XGUnit* target)
{

};


void XGUnit::ActionForceEndTurn()
{
	CurActionPoint = 0;
	OnEndTurnActionDone();
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

	bDead = true;
	ControlCenter->dieUnit(this);
	Player->Units->removeObject(this);

	return true;
}


CCArray* XGUnit::GetMoveableTiles()
{
	CCArray* MoveableTiles = NULL;
	XGMap* map = XGGameInfo::getGameInfo()->getMap();

	MoveableTiles = map->GetTilesWithinRange(Position, Move);


	CCArray* TilesNeedRemove = CCArray::create();

	for(unsigned int i = 0; i < MoveableTiles->count(); i++)
	{
		XGTile* it = dynamic_cast<XGTile*>(MoveableTiles->objectAtIndex(i));
		if(it->bBlock)
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
	if(Navigation->FindPathWithMove(Position, dest, Move))
	{
		ControlCenter->potentiallyMoveUnit(this, Navigation->GetPath());
		return true;
	}
	return false;
}

