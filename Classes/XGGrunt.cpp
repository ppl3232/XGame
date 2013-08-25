#include "XGGrunt.h"

USING_NS_CC;

XGGrunt::XGGrunt()
{
	Type = EUT_Grunt;
	HealthMax = 20;
	Health = HealthMax;
	Power = 3;
	Move  = 2;
	Range = 1;
}

XGGrunt::~XGGrunt()
{

}


bool XGGrunt::init(XGGameInfo* info ,XGPlayer* player, cocos2d::CCPoint& pos)
{
	bool ret = false;
	do 
	{
		CC_BREAK_IF(!XGUnit::init(info, player, pos, "Grunt.png"));
		ret = true;;
	} while (0);

	return ret;

}


XGGrunt* XGGrunt::create(XGGameInfo* info ,XGPlayer* player, cocos2d::CCPoint& pos)
{
	XGGrunt* Grunt = new XGGrunt();
	if(Grunt && Grunt->init(info, player, pos))
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
