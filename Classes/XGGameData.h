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
	static AttackPos* create(XGTilePoint Pos, XGUnit* target);
	virtual bool init(XGTilePoint Pos, XGUnit* target);

public:
	XGTilePoint			Position;
	XGUnit*				Target;
};

class XGUnitInfo : public cocos2d::CCObject
{
public:
	virtual bool init(EUnitType type, XGTilePoint pos);
	static XGUnitInfo* create(EUnitType type, XGTilePoint pos);

public:
	EUnitType			UnitType;
	XGTilePoint			SpawnLocation;
};

inline int GetDistance(XGTilePoint from, XGTilePoint to)
{
	return static_cast<int>(abs(from.x - to.x) + abs(from.y - to.y));
}


#endif