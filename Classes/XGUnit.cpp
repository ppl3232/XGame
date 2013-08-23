#include "XGUnit.h"

USING_NS_CC;

XGUnit::XGUnit()
	: Type(eUnit_Unknown)
	, CurActionPoint(0)
{
}

XGUnit::~XGUnit()
{
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






CCObject* XGUnit::copyWithZone(CCZone* pZone)
{
	return NULL;
}

bool XGUnit::init()
{
	return true;
}
