#include "XGGameData.h"




bool XGUnitInfo::init(EUnitType type, TilePoint pos)
{
	UnitType		= type;
	SpawnLocation	= pos;

	return true;
}

XGUnitInfo* XGUnitInfo::create(EUnitType type, TilePoint pos)
{
	XGUnitInfo* info = new XGUnitInfo();
	if(info && info->init(type, pos))
	{
		info->autorelease();
		return info;
	}
	else
	{
		CC_SAFE_DELETE(info);
		return NULL;
	}
}

bool XGAICombatInfo::init()
{
	return true;
}

bool XGAICombatInfo::SetAICombatInfo(EAIAction action, TilePoint pos, XGUnit* unit)
{
	AIAction	= action;
	Position	= pos;
	Target		= unit;

	return true;
}



void XGAICombatInfo::SetAIAction(EAIAction action)
{
	AIAction	= action;
}