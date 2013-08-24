#include "XGFootman.h"

USING_NS_CC;

XGFootman::XGFootman()
{
	Type = EUT_Footman;
	Health = 10;
	HealthMax = 10;
	Power = 2;
	Speed = 3;
	Range = 1;
}

XGFootman::~XGFootman()
{

}

bool XGFootman::init(XGPlayer* Player, XGDisplay* Canvas ,cocos2d::CCPoint& Pos)
{
	bool ret = false;
	do 
	{
		CC_BREAK_IF(!XGUnit::init(Player, Canvas, Pos, "Footman.png"));
		ret = true;;
	} while (0);

	return ret;

}


XGFootman* XGFootman::create(XGPlayer* Player, XGDisplay* Canvas, CCPoint& Pos)
{
	XGFootman* Footman = new XGFootman();
	if(Footman && Footman->init(Player, Canvas, Pos))
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
