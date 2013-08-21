#ifndef __XG_CONTROL_CENTER_H__
#define __XG_CONTROL_CENTER_H__

#include "cocos2d.h"

class XGControlCenter: public cocos2d::CCObject
{
// constructor/destructor
public:
    XGControlCenter();
    virtual ~XGControlCenter();

// override
public:
	virtual bool init();

// method
public:
	CREATE_FUNC(XGControlCenter);
};

#endif  // __XG_CONTROL_CENTER_H__

