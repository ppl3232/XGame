#include "XGGameInfo.h"

#include "XGInput.h"

USING_NS_CC;

XGGameInfo::XGGameInfo()
	: GameInput(NULL)
{
}

XGGameInfo::~XGGameInfo()
{
}

bool XGGameInfo::init()
{
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		GameInput = XGInput::create();
		addChild(GameInput, InputZOrder);

		return true;
	}
	while (false);

	return false;
}
