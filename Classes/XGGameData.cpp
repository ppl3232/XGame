#include "XGGameData.h"


bool XGUnitInfo::init(EUnitType type, XGTilePoint pos)
{
	UnitType		= type;
	SpawnLocation	= pos;

	return true;
}

XGUnitInfo* XGUnitInfo::create(EUnitType type, XGTilePoint pos)
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


bool AttackPos::init(XGTilePoint Pos, XGUnit* target)
{
	Position		= Pos;
	Target			= target;

	return true;
}

AttackPos* AttackPos::create(XGTilePoint Pos, XGUnit* target)
{
	AttackPos* ap = new AttackPos();
	if(ap && ap->init(Pos, target))
	{
		ap->autorelease();
		return ap;
	}
	else
	{
		CC_SAFE_DELETE(ap);
		return NULL;
	}
}

