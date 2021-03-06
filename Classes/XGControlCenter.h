#ifndef __XG_CONTROL_CENTER_H__
#define __XG_CONTROL_CENTER_H__

#include "cocos2d.h"

#include "XGGameInfo.h"
#include "XGTile.h"

class XGUnit;

class XGControlCenter: public cocos2d::CCObject
{
// constructor/destructor
public:
    XGControlCenter();
    virtual ~XGControlCenter();

// override
public:
	virtual bool init(XGGameInfo* pGameInfo);

// method
public:
	static XGControlCenter* create(XGGameInfo* pGameInfo);

	void spawnUnit(XGUnit* pUnit, TilePoint desPos);
	void moveUnit(XGUnit* pUnit, TilePoint desPos);
	void moveUnit(XGUnit* pUnit, cocos2d::CCArray* Path);
	void dieUnit(XGUnit* pUnit);
	void potentiallyMoveUnit(XGUnit* pUnit, cocos2d::CCArray* desPos);

// member
protected:
	XGGameInfo*						GameInfo;
};

#endif  // __XG_CONTROL_CENTER_H__

