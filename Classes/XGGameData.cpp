#include "XGGameData.h"


bool XGUnitInfo::init(EUnitType type, cocos2d::CCPoint& pos)
{
	UnitType		= type;
	SpawnLocation	= pos;

	return true;
}

XGUnitInfo* XGUnitInfo::create(EUnitType type, cocos2d::CCPoint& pos)
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


bool AttackPos::init(cocos2d::CCPoint& Pos, XGUnit* target)
{
	Position		= Pos;
	Target			= target;

	return true;
}

AttackPos* AttackPos::create(cocos2d::CCPoint& Pos, XGUnit* target)
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

