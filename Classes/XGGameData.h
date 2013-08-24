#ifndef __XGGAMEDATA_H__
#define __XGGAMEDATA_H__

#include "cocos2d.h"

const int MAX_ACTION_POINT = 2;

enum ETeam
{
	ETeam_Human,
	ETeam_AI,
	ETeam_None,
};

enum EUnitType
{
	EUT_Footman,
	EUT_Grunt,
	EUT_Unknow,
};

class XGUnitInfo : public cocos2d::CCObject
{
public:
	virtual bool init(EUnitType type, cocos2d::CCPoint& pos);
	static XGUnitInfo* create(EUnitType type, cocos2d::CCPoint& pos);

public:
	EUnitType			UnitType;
	cocos2d::CCPoint	SpawnLocation;
};


#endif