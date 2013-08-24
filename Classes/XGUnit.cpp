#include "XGUnit.h"
#include "XGTile.h"
#include "XGMap.h"

USING_NS_CC;

XGUnit::XGUnit()
	: CurActionPoint(0)
	, Type(EUT_Unknow)
	, Player(NULL)
	, Sprite(NULL)
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

bool XGUnit::init(XGPlayer* Player, XGDisplay* Canvas, CCPoint& Pos, const char* Texture)
{
	bool ret = false;
	do 
	{
		this->Player = Player;
		this->Canvas = Canvas;
		this->Position = Pos;

		Canvas->Map->SetOccupied(Position);

		Sprite = CCSprite::create(Texture);
		CC_BREAK_IF(!Sprite);
		this->Canvas->AddUnit(this);

		ret = true;
	} while (0);

	return ret;
}

void XGUnit::SetPosition(CCPoint &Pos)
{
	CCPoint OldPos = ccp(Position.x, Position.y);
	Position = Pos;
	OnPositionChange(OldPos);
	
}

void XGUnit::OnPositionChange(CCPoint& OldPos)
{
	Canvas->Map->ClearOccupied(OldPos);
	Canvas->Map->SetOccupied(Position);
	Canvas->OnUnitPosChange(this);
}

CCPoint& XGUnit::getPosition()
{
	return Position;
}

CCSprite* XGUnit::getSprite()
{
	return Sprite;
}


XGUnit* XGUnit::create(XGPlayer* Player, XGDisplay* Canvas, CCPoint& Pos, const char* Texture)
{
	XGUnit* unit = new XGUnit();
	if(unit && unit->init(Player, Canvas, Pos, Texture))
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

void XGUnit::ActionMove(CCPoint& Pos)
{
	SetPosition(Pos);
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

	return true;
}


CCArray* XGUnit::GetMoveableTiles()
{
	CCArray* MoveableTiles = NULL;

	MoveableTiles = Canvas->Map->GetTilesWithinRange(Position, Speed);

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

CCArray* XGUnit::GetAttackableTiles(CCPoint& Origin)
{
	return Canvas->Map->GetTilesWithinRange(Origin, Range);
}

CCArray* XGUnit::GetPotentialAttackableTiles()
{
	CCArray* PotentialTiles = CCArray::create();
	CCArray* MoveableTiles = GetMoveableTiles();
	for(int i = 0; i < MoveableTiles->count(); i++)
	{
		XGTile* kTile = dynamic_cast<XGTile*>(MoveableTiles->objectAtIndex(i));
		PotentialTiles->addObjectsFromArray(GetAttackableTiles(kTile->Position));
	}

	return PotentialTiles;
}


float XGUnit::GetHealthRatio()
{
	return float(Health) / HealthMax;
}