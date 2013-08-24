#include "XGPlayer.h"
#include "XGUnit.h"
#include "XGFootman.h"
#include "XGGrunt.h"

USING_NS_CC;

XGPlayer::XGPlayer()
{
	Units = new CCArray();
}

XGPlayer::~XGPlayer()
{
	if(Units != NULL)
	{
		Units->release();
	}
}

bool XGPlayer::init()
{
	bool ret = false;
	do 
	{
		ret = true;
	} while (0);

	return ret;
}



void XGPlayer::BeginTurn()
{
	CCObject* UnitObj = NULL;
	CCARRAY_FOREACH(Units, UnitObj)
	{
		XGUnit* kUnit = dynamic_cast<XGUnit*>(UnitObj);
		kUnit->BeginTurn();
	}
}

void XGPlayer::EndTurn()
{
	Battle->BeginNewTurn();
}

bool XGPlayer::CheckForEndTurn()
{
	CCObject* UnitObj = NULL;
	CCARRAY_FOREACH(Units, UnitObj)
	{
		XGUnit* kUnit = dynamic_cast<XGUnit*>(UnitObj);
		if(!kUnit->CheckForEndTurn())
		{
			return false;
		}
	}

	EndTurn();

	return true;
}


bool XGPlayer::SpawnTeam(XGDisplay* Canvas, CCArray* TeamInfo)
{
	if(TeamInfo->count() <= 0)
		return false;

	CCObject* UnitInfoObj = NULL;
	CCARRAY_FOREACH(TeamInfo, UnitInfoObj)
	{
		XGUnitInfo* UnitInfo = dynamic_cast<XGUnitInfo*>(UnitInfoObj);
		XGUnit* Unit = SpawnUnit(UnitInfo->UnitType, Canvas, UnitInfo->SpawnLocation);
		Units->addObject(Unit);
	}

	return true;
}


XGUnit* XGPlayer::SpawnUnit(EUnitType type, XGDisplay* Canvas, CCPoint& Pos)
{
	XGUnit* Unit = NULL;

	switch(type)
	{
	case EUT_Footman:
		Unit = XGFootman::create(this, Canvas, Pos);
		break;
	case EUT_Grunt:
		Unit = XGGrunt::create(this, Canvas, Pos);
		break;
	default:
		break;
	}

	return Unit;
}
