#ifndef __XGGAMEDATA_H__
#define __XGGAMEDATA_H__

#include "cocos2d.h"

#include "XGTile.h"

class XGUnit;

const int MAX_ACTION_POINT = 2;

enum EAIAction
{
	EAction_Approach,
	EAction_MoveAttack,
	EAction_None,
};


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



class XGAICombatInfo : public cocos2d::CCObject
{
public:
	CREATE_FUNC(XGAICombatInfo);
	virtual bool init();
	virtual bool SetAICombatInfo(EAIAction action, TilePoint pos, XGUnit* unit);
	virtual void SetAIAction(EAIAction action);
public:
	TilePoint			Position;
	XGUnit*				Target;
	EAIAction			AIAction;
};




class XGUnitInfo : public cocos2d::CCObject
{
public:
	virtual bool init(EUnitType type, TilePoint pos);
	static XGUnitInfo* create(EUnitType type, TilePoint pos);

public:
	EUnitType			UnitType;
	TilePoint			SpawnLocation;
};

inline int GetDistance(TilePoint from, TilePoint to)
{
	return static_cast<int>(abs(from.x - to.x) + abs(from.y - to.y));
}


#endif