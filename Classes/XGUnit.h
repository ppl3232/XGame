#ifndef __XG_UNIT_H__
#define __XG_UNIT_H__

#include "cocos2d.h"

// definition
enum UnitType
{
	eUnit_Player,
	eUnit_Enemy,
	eUnit_Neutral,
	eUnit_Unknown
};

class XGUnit: public cocos2d::CCObject
{
// constructor/destructor
public:
    XGUnit();
    virtual ~XGUnit();

// override
public:
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);

// method
public:
	virtual bool init();

	virtual void onBeginTurn() {}
	virtual void onEngTurn() {}

	UnitType getType() {return Type;}
	unsigned int getActionPoint() {return ActionPoint;}

// member
protected:
	UnitType						Type;
	unsigned int					ActionPoint;
};

#endif  // __XG_UNIT_H__
