#ifndef __XGBATTLE_H__
#define __XGBATTLE_H__

#include "cocos2d.h"

class XGPlayer;

class XGBattle : public cocos2d::CCObject
{
	// constructor & destructor
public:
	XGBattle();
	virtual ~XGBattle();

	// create & init
public:
	CREATE_FUNC(XGBattle);
	virtual bool init();

	// method
public:
	void AddPlayer(XGPlayer* kPlayer);

	void BeginNewTurn();

	void Start();

	void End();

	XGPlayer* GetPlayer(); //  for test;

	// member
public:
	cocos2d::CCArray*		arrPlayers;
	XGPlayer*				ActivePlayer;

	int						Turn;


};


#endif