#ifndef __XG_CONTROL_CENTER_H__
#define __XG_CONTROL_CENTER_H__

#include "cocos2d.h"

#include "XGGameInfo.h"

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

// member
protected:
	XGGameInfo*						GameInfo;
};

#endif  // __XG_CONTROL_CENTER_H__

