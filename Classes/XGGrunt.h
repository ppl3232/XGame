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
	virtual bool init(XGControlCenter* ControlCenter, XGPlayer* Player, XGTilePoint Pos);
	static XGGrunt* create(XGControlCenter* ControlCenter, XGPlayer* Player, XGTilePoint Pos);

	// method
public:


	// member
public:

};

#endif