#ifndef __XGFOOTMAN_H__
#define __XGFOOTMAN_H__

#include "cocos2d.h"

#include "XGUnit.h"

class XGFootman : public XGUnit
{
	// constructor & destructor
public:
	XGFootman();
	virtual ~XGFootman();

	// create & init
public:
	virtual bool init(XGControlCenter* ControlCenter, XGPlayer* Player, XGTilePoint Pos);
	static XGFootman* create(XGControlCenter* ControlCenter, XGPlayer* Player, XGTilePoint Pos);

	// method
public:


	// member
public:

};

#endif