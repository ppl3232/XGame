#include "XGGameInfo.h"

#include "XGGameInfo.h"

USING_NS_CC;

XGGameInfo::XGGameInfo()
{
}

XGGameInfo::~XGGameInfo()
{
}

bool XGGameInfo::init()
{
	do
	{
		CC_BREAK_IF(!CCScene::init());

		XGGameInfo* pGame = XGGameInfo::create();
		CC_BREAK_IF(!pGame);
		addChild(pGame);

		return true;

	} while (false);

	return false;
}
