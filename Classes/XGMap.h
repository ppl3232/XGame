#ifndef __XG_MAP_H__
#define __XG_MAP_H__

#include "cocos2d.h"

class XGMap: public cocos2d::CCObject
{
// constructor/destructor
public:
    XGMap();
    virtual ~XGMap();

// override
public:
	virtual bool init();

// method
public:
	CREATE_FUNC(XGMap);
};

#endif  // __XG_MAP_H__

