#include "XGPlayer.h"

#include "XGControlCenter.h"
#include "XGBattle.h"
#include "XGUnit.h"
#include "XGFootman.h"
#include "XGGrunt.h"
#include "XGMap.h"
#include "XGTile.h"

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

XGPlayer* XGPlayer::create(XGControlCenter* controlCenter, XGBattle* battle)
{
	XGPlayer* player = new XGPlayer();
	if(player && player->init(controlCenter, battle))
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

bool XGPlayer::init(XGControlCenter* controlCenter, XGBattle* battle)
{
	bool ret = false;
	do 
	{
		ControlCenter = controlCenter;
		Battle = battle;
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



bool XGPlayer::SpawnTeam(XGGameInfo* info, CCArray* TeamInfo)
{
	if(TeamInfo->count() <= 0)
		return false;

	CCObject* UnitInfoObj = NULL;
	CCARRAY_FOREACH(TeamInfo, UnitInfoObj)
	{
		XGUnitInfo* UnitInfo = dynamic_cast<XGUnitInfo*>(UnitInfoObj);
		XGUnit* Unit = SpawnUnit(info, UnitInfo->UnitType, UnitInfo->SpawnLocation);
		if(Unit != NULL)
		{
			info->getMap()->SetOccupied(Unit->Position);
			Units->addObject(Unit);
		}
	}

	return true;
}



XGUnit* XGPlayer::SpawnUnit(XGGameInfo* info, EUnitType type,TilePoint Pos)
{
	XGUnit* Unit = NULL;

	XGTile* tile = info->getMap()->getTileAt(Pos.x, Pos.y);
	if(tile->bBlock)
	{
		CCLOG("[Game] Spawn failed due to Block on pos");
		return NULL;
	}

	switch(type)
	{
	case EUT_Footman:
		Unit = XGFootman::create(info, this, Pos);
		break;
	case EUT_Grunt:
		Unit = XGGrunt::create(info, this, Pos);
		break;
	default:
		break;
	}

	return Unit;
}


void XGPlayer::OnUnitMoveEnd(XGUnit* unit)
{

}
void XGPlayer::OnUnitTurnEnd(XGUnit* unit)
{

}