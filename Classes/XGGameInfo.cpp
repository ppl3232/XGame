#include "XGGameInfo.h"

#include "XGGameInitInfo.h"
#include "XGControlCenter.h"
#include "XGGameFlow.h"
#include "XGMap.h"
#include "XGInput.h"
#include "XGDisplay.h"
#include "XGBattle.h"
#include "XGPlayer.h"
#include "XGAIPlayer.h"
#include "XGGameData.h"

USING_NS_CC;

XGGameInfo::XGGameInfo()
	: ControlCenter(NULL)
	, GameFlow(NULL)
	, Map(NULL)
	, GameInput(NULL)
	, GameDisplay(NULL)
{
}

XGGameInfo::~XGGameInfo()
{
	ControlCenter->release();
}

bool XGGameInfo::init()
{
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		XGGameInitInfo* pGameInitInfo = getGameInitInfo(NULL);
		CC_BREAK_IF(!pGameInitInfo);
		pGameInitInfo->retain();

		ControlCenter = XGControlCenter::create(this);
		CC_BREAK_IF(!ControlCenter);
		ControlCenter->retain();

		GameFlow = XGGameFlow::create(pGameInitInfo);
		CC_BREAK_IF(!GameFlow);
		GameFlow->retain();

		Map = XGMap::create(pGameInitInfo);
		CC_BREAK_IF(!Map);
		Map->retain();

		GameInput = XGInput::create();
		CC_BREAK_IF(!GameInput);
		addChild(GameInput, InputZOrder);

		GameDisplay = XGDisplay::create(Map);
		CC_BREAK_IF(!GameDisplay);
		addChild(GameDisplay, DisplayZOrder);
		GameDisplay->setTileBackground("tile.png");


		CC_BREAK_IF(!InitBattle());

		pGameInitInfo->release();
		return true;
	}
	while (false);

	return false;
}

void XGGameInfo::DestoryBattle()
{
	if(Battle != NULL)
	{
		Battle->arrPlayers->removeAllObjects();
		Battle->release();
	}
}

// config function
CCArray* XGGameInfo::getHumanTeam(int Num)
{
	CCArray* TeamInfo = CCArray::createWithCapacity(1);
	for(int i = 0; i < Num; i++)
	{
		XGUnitInfo* info = XGUnitInfo::create(EUT_Footman, ccp(i,0));
		TeamInfo->addObject(info);
	}

	return TeamInfo;
}
CCArray* XGGameInfo::getOrcTeam(int Num)
{
	CCArray* TeamInfo = CCArray::createWithCapacity(1);
	for(int i = 0; i < Num; i++)
	{
		XGUnitInfo* info = XGUnitInfo::create(EUT_Grunt, ccp(9-i,9));
		TeamInfo->addObject(info);
	}

	return TeamInfo;
}
// end

bool XGGameInfo::InitBattle()
{
	bool ret = false;
	do 
	{
		Battle = XGBattle::create();
		CC_BREAK_IF(!Battle);
		Battle->retain();

		XGAIPlayer* NewAI_1 = XGAIPlayer::create();
		CC_BREAK_IF(!NewAI_1);
		NewAI_1->SpawnTeam(GameDisplay, getHumanTeam(4));
		Battle->AddPlayer(NewAI_1);

		XGAIPlayer* NewAI_2 = XGAIPlayer::create();
		CC_BREAK_IF(!NewAI_2);
		NewAI_2->SpawnTeam(GameDisplay, getOrcTeam(3));
		Battle->AddPlayer(NewAI_2);

		Battle->Start();

		ret = true;
	} while (0);

	return ret;
}


XGGameInitInfo* XGGameInfo::getGameInitInfo(const char* filename)
{
	XGGameInitInfo* pGameInitInfo = NULL;
	if (filename == NULL)
	// use debug info
	{
		pGameInitInfo = XGGameInitInfo::create();
		int sizeX = 10, sizeY = 10;
		pGameInitInfo->MapSize = CCSize(sizeX, sizeY);
		pGameInitInfo->MapTiles = CCArray::createWithCapacity(sizeX*sizeY);
		if (!pGameInitInfo)
		{
			return NULL;
		}
		for (int i = 0; i < sizeX*sizeY; i++)
		{
			XGTile* pTile = XGTile::createWithXY(i%sizeX, i/sizeY);
			pGameInitInfo->MapTiles->addObject(pTile);
		}
		pGameInitInfo->Units = CCArray::create();
	}
	else
	{
		// @TODO: load information from file or something else
	}

	return pGameInitInfo;
}

XGInput* XGGameInfo::getInput()
{
	return GameInput;
}

XGDisplay* XGGameInfo::getDisplay()
{
	return GameDisplay;
}

XGControlCenter* XGGameInfo::getControlCenter()
{
	return ControlCenter;
}

XGMap* XGGameInfo::getMap()
{
	return Map;
}
