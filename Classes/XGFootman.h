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
	virtual bool init(XGPlayer* Player,cocos2d::CCPoint& Pos);
	static XGFootman* create(XGPlayer* Player,cocos2d::CCPoint& Pos);

	// method
public:


	// member
public:

};

#endif