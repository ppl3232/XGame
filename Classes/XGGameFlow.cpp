#include "XGGameFlow.h"

USING_NS_CC;

XGGameFlow::XGGameFlow()
	: CurrentTurn(eTurn_Player)
	, PlayerUnits(NULL)
	, EnemyUnits(NULL)
	, NeutralUnits(NULL)
	, CurrentActableUnits(NULL)
{
}

XGGameFlow::~XGGameFlow()
{
}

bool XGGameFlow::init(XGGameInitInfo* pInitInfo)
{
	do 
	{
		CC_BREAK_IF(!pInitInfo);

		PlayerUnits = CCArray::create();
		CC_BREAK_IF(!PlayerUnits);
		PlayerUnits->retain();

		EnemyUnits = CCArray::create();
		CC_BREAK_IF(!EnemyUnits);
		EnemyUnits->retain();

		NeutralUnits = CCArray::create();
		CC_BREAK_IF(!NeutralUnits);
		NeutralUnits->retain();

		CCObject* pUnitObj = NULL;
		CCARRAY_FOREACH(pInitInfo->Units, pUnitObj)
		{
			XGUnit* pUnit = dynamic_cast<XGUnit*>(pUnitObj);
			if (pUnit)
			{
				switch (pUnit->getType())
				{
				case eUnit_Player:
					PlayerUnits->addObject(pUnit);
					break;
				case eUnit_Enemy:
					EnemyUnits->addObject(pUnit);
					break;
				case eUnit_Neutral:
				case eUnit_Unknown:
					NeutralUnits->addObject(pUnit);
					break;
				}
			}
		}

		CurrentActableUnits = CCArray::create();
		CC_BREAK_IF(!CurrentActableUnits);
		CurrentActableUnits->retain();

		startTurn();
		updateTurn();

		return true;
	}
	while (false);

	return false;
}

XGGameFlow* XGGameFlow::create(XGGameInitInfo* pInitInfo)
{
	XGGameFlow* pReturnValue = new XGGameFlow();
	if (pReturnValue)
	{
		if (pReturnValue->init(pInitInfo))
		{
			pReturnValue->autorelease();
		}
		else
		{
			delete pReturnValue;
			pReturnValue = NULL;
		}
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

void XGGameFlow::startTurn()
{
	CurrentActableUnits->removeAllObjects();
	CCArray* pTargetUnits = getCurrentTurnUnits();

	CCObject* pUnitObj = NULL;
	CCARRAY_FOREACH(pTargetUnits, pUnitObj)
	{
		XGUnit* pUnit = dynamic_cast<XGUnit*>(pUnitObj);
		if (pUnit)
		{
			pUnit->onBeginTurn();
			CurrentActableUnits->addObject(pUnitObj);
		}
	}
}

void XGGameFlow::updateTurn()
{
	CCArray* pFinishedUnits = CCArray::create();
	CCObject* pUnitObj = NULL;
	CCARRAY_FOREACH(CurrentActableUnits, pUnitObj)
	{
		XGUnit* pUnit = dynamic_cast<XGUnit*>(pUnitObj);
		if (pUnit && pUnit->getActionPoint() == 0)
		{
			pFinishedUnits->addObject(pUnit);
		}
	}
	CurrentActableUnits->removeObjectsInArray(pFinishedUnits);

	if (CurrentActableUnits->count() == 0)
	{
		finishTurn();
		// add some code between two turn?
		startTurn();
	}
}

void XGGameFlow::finishTurn()
{
	CCArray* pTargetUnits = getCurrentTurnUnits();
	CCObject* pUnitObj = NULL;
	CCARRAY_FOREACH(pTargetUnits, pUnitObj)
	{
		XGUnit* pUnit = dynamic_cast<XGUnit*>(pUnitObj);
		if (pUnit)
		{
			pUnit->onEngTurn();
		}
	}

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
