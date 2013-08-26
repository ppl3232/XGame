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
	virtual bool init(XGGameInfo* info ,XGPlayer* player, TilePoint pos);
	static XGFootman* create(XGGameInfo* info ,XGPlayer* player, TilePoint pos);

	// method
public:


	// member
public:

};

#endif