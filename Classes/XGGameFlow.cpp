#include "XGGameFlow.h"

USING_NS_CC;

XGGameFlow::XGGameFlow()
	: CurrentTurn(eTurn_Player)
	, PlayerUnits(NULL)
	, EnemyUnits(NULL)
	, NeutralUnits(NULL)
{
}

XGGameFlow::~XGGameFlow()
{
}

bool XGGameFlow::init()
{
	do 
	{

	}
	while (false);

	return false;
}

XGGameFlow* XGGameFlow::create()
{
	XGGameFlow* pReturnValue = new XGGameFlow();
	if (pReturnValue && pReturnValue->init())
	{
		pReturnValue->autorelease();
	}
	else
	{
		if (pReturnValue)
		{
			delete pReturnValue;
		}
		pReturnValue = NULL;
	}
	return pReturnValue;
}

CCArray* XGGameFlow::getCurrentTurnUnits()
{
	switch (CurrentTurn)
	{
	case eTurn_Player:
		return PlayerUnits;

	case eTurn_Enemy:
		return EnemyUnits;

	case eTurn_Neutral:
		return NeutralUnits;
	}

	return NULL;
}

XGUnit* XGGameFlow::getNextActableUnit()
{
	CCArray* pCurrentUnits = getCurrentTurnUnits();
	if (pCurrentUnits)
	{
		CCObject* pUnitObj;
		CCARRAY_FOREACH(pCurrentUnits, pUnitObj)
		{
			XGUnit* pUnit = dynamic_cast<XGUnit*>(pUnitObj);
			if (pUnit && pUnit->getActionPoint() > 0)
			{
				return pUnit;
			}
		}
	}
	return NULL;
}

void XGGameFlow::updateTurn()
{

}

void XGGameFlow::finishTurn()
{
	switch (CurrentTurn)
	{
	case eTurn_Player:
		CurrentTurn = eTurn_Enemy;
		break;

	case eTurn_Enemy:
		CurrentTurn = eTurn_Neutral;
		break;

	case eTurn_Neutral:
		CurrentTurn = eTurn_Player;
		break;
	}
}
