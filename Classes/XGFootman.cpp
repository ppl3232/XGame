#include "XGFootman.h"

USING_NS_CC;

XGFootman::XGFootman()
{
	Type = EUT_Footman;
	Health = 10;
	HealthMax = 10;
	Power = 2;
	MovePoint  = 20; //for test;
	Range = 1;
}

XGFootman::~XGFootman()
{

}

bool XGFootman::init(XGGameInfo* info ,XGPlayer* player, TilePoint pos)
{
	bool ret = false;
	do 
	{
		CC_BREAK_IF(!XGUnit::init(info, player, pos, "Footman.png"));
		ret = true;;
	} while (0);

	return ret;

}



XGFootman* XGFootman::create(XGGameInfo* info, XGPlayer* player, TilePoint pos)
{
	XGFootman* Footman = new XGFootman();
	if(Footman && Footman->init(info, player, pos))
	{
		Footman->autorelease();
		return Footman;
	}
	else
	{
		CC_SAFE_DELETE(Footman);
		return NULL;
	}
}
