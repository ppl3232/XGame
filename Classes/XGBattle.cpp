#include "XGBattle.h"

#include "XGPlayer.h"
#include "XGInput.h"

USING_NS_CC;

XGBattle::XGBattle()
	: Turn(0)
{
	arrPlayers = new CCArray();
}

XGBattle::~XGBattle()
{
	if(arrPlayers != NULL)
	{
		arrPlayers->release();
	}
}

bool XGBattle::init()
{
	bool ret = false;
	do 
	{
		ret = true;
	} while (0);

	return ret;
}


void XGBattle::AddPlayer(XGPlayer* kPlayer)
{
	arrPlayers->addObject(kPlayer);
}

void XGBattle::BeginNewTurn()
{

	CCAssert(arrPlayers->count() != 0, "Empty Player array!!!");
	if(Turn == 0)
	{
		ActivePlayer = dynamic_cast<XGPlayer*>(arrPlayers->objectAtIndex(0));
	}
	else
	{
		for(unsigned int i = 0; i < arrPlayers->count(); i++)
		{
			if(ActivePlayer == dynamic_cast<XGPlayer*>(arrPlayers->objectAtIndex(i)))
			{
				int NextPlayerIdx = (i + 1) % arrPlayers->count();
				ActivePlayer = dynamic_cast<XGPlayer*>(arrPlayers->objectAtIndex(NextPlayerIdx));
				break;
			}
		}
	}

	if(ActivePlayer == dynamic_cast<XGPlayer*>(arrPlayers->objectAtIndex(0)))
	{
		Turn++;
	}

	ActivePlayer->BeginTurn();

}

void XGBattle::Start()
{
	BeginNewTurn();
}


// for test;
XGPlayer* XGBattle::GetPlayer()
{
	return dynamic_cast<XGPlayer*>(arrPlayers->objectAtIndex(0));
}