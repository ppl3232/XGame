#include "XGGameInfo.h"

#include "XGInput.h"
#include "XGControlCenter.h"

USING_NS_CC;

XGGameInfo::XGGameInfo()
	: GameInput(NULL)
	, ControlCenter(NULL)
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

		GameInput = XGInput::create();
		CC_BREAK_IF(!GameInput);
		addChild(GameInput, InputZOrder);

		ControlCenter = XGControlCenter::create(this);
		CC_BREAK_IF(!ControlCenter);
		ControlCenter->retain();

		return true;
	}
	while (false);

	return false;
}
