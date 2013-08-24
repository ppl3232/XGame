#include "XGGrunt.h"

USING_NS_CC;

XGGrunt::XGGrunt()
{
	Type = EUT_Grunt;
	HealthMax = 20;
	Health = HealthMax;
	Power = 3;
	Speed = 2;
	Range = 1;
}

XGGrunt::~XGGrunt()
{

}

bool XGGrunt::init(XGPlayer* Player, XGDisplay* Canvas ,cocos2d::CCPoint& Pos)
{
	bool ret = false;
	do 
	{
		CC_BREAK_IF(!XGUnit::init(Player, Canvas, Pos, "Grunt.png"));
		ret = true;;
	} while (0);

	return ret;

}


XGGrunt* XGGrunt::create(XGPlayer* Player, XGDisplay* Canvas, CCPoint& Pos)
{
	XGGrunt* Grunt = new XGGrunt();
	if(Grunt && Grunt->init(Player, Canvas, Pos))
	{
		Grunt->autorelease();
		return Grunt;
	}
	else
	{
		CC_SAFE_DELETE(Grunt);
		return NULL;
	}
}
