#include "XGGameScene.h"

#include "XGGameInfo.h"

USING_NS_CC;

XGGameScene::XGGameScene()
{
}

XGGameScene::~XGGameScene()
{
}

bool XGGameScene::init()
{
	do
	{
		CC_BREAK_IF(!CCScene::init());

		CCLayer* pGameLayer = XGGameInfo::create();
		CC_BREAK_IF(!pGameLayer);
		addChild(pGameLayer);

		return true;
	}
	while (false);

	return false;
}
