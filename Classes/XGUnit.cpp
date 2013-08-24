#include "XGUnit.h"

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

		Sprite = CCSprite::create(Texture);
		CC_BREAK_IF(!Sprite);
		this->Canvas->AddUnit(this);

		ret = true;
	} while (0);

	return ret;
}

void XGUnit::setPosition(const cocos2d::CCPoint &Pos)
{
	Position = Pos;
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

void XGUnit::OnNormalActionDone()
{
	if(CheckForEndTurn())
	{
		Player->CheckForEndTurn();
	}
}

void XGUnit::OnEndTurnActionDone()
{
	Player->CheckForEndTurn();
}

void XGUnit::ActionMove(XGUnit* target)
{

};

void XGUnit::ActionAttack(XGUnit* target)
{

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