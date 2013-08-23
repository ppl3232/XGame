#include "XGPlayer.h"
#include "XGUnit.h"

USING_NS_CC;

XGPlayer::XGPlayer()
{
	Units = new CCArray();
}

XGPlayer::~XGPlayer()
{
	if(Units != NULL)
	{
		Units->release();
	}
}

bool XGPlayer::init()
{
	bool ret = false;
	do 
	{
		
		ret = true;
	} while (0);

	return ret;
}



void XGPlayer::BeginTurn()
{
	CCObject* UnitObj = NULL;
	CCARRAY_FOREACH(Units, UnitObj)
	{
		XGUnit* kUnit = dynamic_cast<XGUnit*>(UnitObj);
		kUnit->BeginTurn();
	}
}

void XGPlayer::EndTurn()
{
	Battle->BeginNewTurn();
}

bool XGPlayer::CheckForEndTurn()
{
	CCObject* UnitObj = NULL;
	CCARRAY_FOREACH(Units, UnitObj)
	{
		XGUnit* kUnit = dynamic_cast<XGUnit*>(UnitObj);
		if(!kUnit->CheckForEndTurn())
		{
			return false;
		}
	}

	EndTurn();

	return true;
}