#ifndef __XGPLAYER_H__
#define __XGPLAYER_H__

#include "cocos2d.h"
#include "XGBattle.h"

class XGBattle;

class XGPlayer : public cocos2d::CCObject
{
	// constructor & destructor
public:
	XGPlayer();
	virtual ~XGPlayer();

	// create & init
public:
	CREATE_FUNC(XGPlayer);
	virtual bool init();

	// method
public:
	virtual bool CheckForEndTurn();


	virtual void BeginTurn();
	virtual void EndTurn();
	

	// member
public:
	XGBattle*			Battle;
	cocos2d::CCArray*	Units;


};

#endif