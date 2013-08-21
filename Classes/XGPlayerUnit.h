#ifndef __XG_PLAYER_UNIT_H__
#define __XG_PLAYER_UNIT_H__

#include "XGUnit.h"

class XGPlayerUnit: public XGUnit
{
// constructor/destructor
public:
    XGPlayerUnit();
    virtual ~XGPlayerUnit();

// override
public:
	virtual bool init();

// method
public:
	CREATE_FUNC(XGPlayerUnit);

// member
};

#endif  // __XG_PLAYER_UNIT_H__
