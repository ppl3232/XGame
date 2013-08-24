#ifndef __XGDEMON_H__
#define __XGDEMON_H__

#include "cocos2d.h"
#include "XGUnit.h"

class XGGrunt : public XGUnit
{
	// constructor & destructor
public:
	XGGrunt();
	virtual ~XGGrunt();

	// create & init
public:
	virtual bool init(XGPlayer* Player, XGDisplay* Canvas ,cocos2d::CCPoint& Pos);
	static XGGrunt* create(XGPlayer* Player, XGDisplay* Canvas ,cocos2d::CCPoint& Pos);

	// method
public:


	// member
public:

};

#endif