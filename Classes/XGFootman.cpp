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

bool XGFootman::init(XGControlCenter* ControlCenter, XGPlayer* Player, XGTilePoint Pos)
{
	bool ret = false;
	do 
	{
		CC_BREAK_IF(!XGUnit::init(ControlCenter, Player, Pos, "Footman.png"));
		ret = true;;
	} while (0);

	return ret;

}


XGFootman* XGFootman::create(XGControlCenter* ControlCenter, XGPlayer* Player, XGTilePoint Pos)
{
	XGFootman* Footman = new XGFootman();
	if(Footman && Footman->init(ControlCenter, Player, Pos))
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
