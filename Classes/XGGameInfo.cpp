#include "XGGameInfo.h"

#include "XGGameInitInfo.h"
#include "XGControlCenter.h"
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

		setTag(GameInfoTag);

		XGGameInitInfo* pGameInitInfo = getGameInitInfo(NULL);
		CC_BREAK_IF(!pGameInitInfo);
		pGameInitInfo->retain();

		ControlCenter = XGControlCenter::create(this);
		CC_BREAK_IF(!ControlCenter);
		ControlCenter->retain();

		Map = XGMap::create(pGameInitInfo);
		CC_BREAK_IF(!Map);
		Map->retain();

		GameInput = XGInput::create();
		CC_BREAK_IF(!GameInput);
		addChild(GameInput, InputZOrder);

		GameDisplay = XGDisplay::create(pGameInitInfo);
		CC_BREAK_IF(!GameDisplay);
		addChild(GameDisplay, DisplayZOrder);

		CC_BREAK_IF(!InitBattle());

		pGameInitInfo->release();
		return true;
	}
	while (false);

	return false;
}

XGGameInfo* XGGameInfo::getGameInfo()
{
	CCDirector* d = CCDirector::sharedDirector();
	CCScene* s = d->getRunningScene();
	CCNode* n = s->getChildByTag(GameInfoTag);
	XGGameInfo* g = dynamic_cast<XGGameInfo*>(n);
	return g;
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

		XGPlayer* player_1 = XGPlayer::create(ControlCenter,Battle);
		CC_BREAK_IF(!player_1);
		player_1->SpawnTeam(this, getHumanTeam(1));
		Battle->AddPlayer(player_1);

		//XGAIPlayer* NewAI_2 = XGAIPlayer::create(Battle);
		//CC_BREAK_IF(!NewAI_2);
		//NewAI_2->SpawnTeam(this, getOrcTeam(1));
		//Battle->AddPlayer(NewAI_2);

		this->scheduleOnce(schedule_selector(XGGameInfo::BattleStart), 2);

		GameInput->GameInfo = this; // for test

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
		pGameInitInfo->MapSize = TileMapSize(sizeX, sizeY);
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

		//for(int i = 0; i < pGameInitInfo->MapTiles->count(); i++)
		//{
		//	XGTile* tile = dynamic_cast<XGTile*>(pGameInitInfo->MapTiles->objectAtIndex(i));
		//	CCLOG("[Nav] init tile %f %f %d", tile->Position.x, tile->Position.y, tile->bBlock);
		//}


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



XGBattle* XGGameInfo::GetBattle()
{
	return Battle;
}


void XGGameInfo::DestoryBattle()
{
	if(Battle != NULL)
	{
		Battle->arrPlayers->removeAllObjects();
		Battle->release();
	}
}

void XGGameInfo::BattleStart(float dt)
{
	Battle->Start();
}

// config function
CCArray* XGGameInfo::getHumanTeam(int Num)
{
	CCArray* TeamInfo = CCArray::createWithCapacity(1);
	for(int i = 0; i < Num; i++)
	{
		XGUnitInfo* info = XGUnitInfo::create(EUT_Footman, TilePoint(i,0));
		TeamInfo->addObject(info);
	}

	return TeamInfo;
}
CCArray* XGGameInfo::getOrcTeam(int Num)
{
	CCArray* TeamInfo = CCArray::createWithCapacity(1);
	for(int i = 0; i < Num; i++)
	{
		XGUnitInfo* info = XGUnitInfo::create(EUT_Grunt, TilePoint(9-i,9));
		TeamInfo->addObject(info);
	}

	return TeamInfo;
}
// end

