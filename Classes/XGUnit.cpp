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
	, Power(2)
	, Speed(2)
	, Range(1)
	, bDead(false)
{
}

XGUnit::~XGUnit()
{
}


CCObject* XGUnit::copyWithZone(CCZone* pZone)
{
	return NULL;
}

bool XGUnit::init(XGControlCenter* ControlCenter, XGPlayer* Player, XGTilePoint Pos, const char* Texture)
{
	bool ret = false;
	do 
	{
		this->ControlCenter = ControlCenter;
		this->Player = Player;
		this->Position = Pos;
		this->Texture = Texture;

		ret = true;
	} while (0);

	return ret;
}

XGTilePoint& XGUnit::GetPosition()
{
	return Position;
}

void XGUnit::OnPositionChanged(XGTilePoint NewPos)
{
	Position = NewPos;
}


XGUnit* XGUnit::create(XGControlCenter* ControlCenter, XGPlayer* Player, XGTilePoint Pos, const char* Texture)
{
	XGUnit* unit = new XGUnit();
	if(unit && unit->init(ControlCenter, Player, Pos, Texture))
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

void XGUnit::ActionMove(XGTilePoint Pos)
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

	MoveableTiles = map->GetTilesWithinRange(Position, Speed);

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

CCArray* XGUnit::GetAttackableTiles(XGTilePoint Origin)
{
	XGMap* map = XGGameInfo::getGameInfo()->getMap();
	return map->GetTilesWithinRange(Origin, Range);
}

CCArray* XGUnit::GetPotentialAttackableTiles()
{
	CCArray* PotentialTiles = CCArray::create();
	CCArray* MoveableTiles = GetMoveableTiles();
	for (unsigned int i = 0; i < MoveableTiles->count(); i++)
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