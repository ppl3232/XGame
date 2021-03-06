#include "XGGrunt.h"

USING_NS_CC;

XGGrunt::XGGrunt()
{
	Type = EUT_Grunt;
	HealthMax = 20;
	Health = HealthMax;
	Power = 3;
	MovePoint  = 2;
	Range = 1;
}

XGGrunt::~XGGrunt()
{

}


bool XGGrunt::init(XGGameInfo* info ,XGPlayer* player, TilePoint pos)
{
	bool ret = false;
	do 
	{
		CC_BREAK_IF(!XGUnit::init(info, player, pos, "Grunt.png"));
		ret = true;;
	} while (0);

	return ret;

}


XGGrunt* XGGrunt::create(XGGameInfo* info ,XGPlayer* player, TilePoint pos)
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

void XGGrunt::TakeDamage(int DamageAmount, XGUnit* DamageCauser)
{
	CCLOG("[Unit] Grunt %d %d %d",DamageAmount, Health, HealthMax);
	XGUnit::TakeDamage(DamageAmount, DamageCauser);
}
