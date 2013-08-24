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