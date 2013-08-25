#ifndef __XGGAMEDATA_H__
#define __XGGAMEDATA_H__

#include "cocos2d.h"

#include "XGTile.h"

class XGUnit;

const int MAX_ACTION_POINT = 2;

enum ETeamType
{
	ETeam_Human,
	ETeam_ORC,
	ETeam_None,
};

enum EUnitType
{
	EUT_Footman,
	EUT_Grunt,
	EUT_Unknow,
};



class AttackPos : public cocos2d::CCObject
{
public:
	static AttackPos* create(cocos2d::CCPoint& Pos, XGUnit* target);
	virtual bool init(cocos2d::CCPoint& Pos, XGUnit* target);

public:
	cocos2d::CCPoint	Position;
	XGUnit*				Target;
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

inline int GetDistance(cocos2d::CCPoint& from, cocos2d::CCPoint& to)
{
	return static_cast<int>(abs(from.x - to.x) + abs(from.y - to.y));
}


#endif