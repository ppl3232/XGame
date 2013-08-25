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
	virtual bool init(XGGameInfo* info ,XGPlayer* player, cocos2d::CCPoint& pos);
	static XGGrunt* create(XGGameInfo* info ,XGPlayer* player, cocos2d::CCPoint& pos);


	// method
public:


	// member
public:

};

#endif