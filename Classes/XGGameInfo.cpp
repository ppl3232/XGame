#include "XGGameInfo.h"

#include "XGInput.h"
#include "XGDisplay.h"
#include "XGControlCenter.h"
#include "XGMap.h"

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

		ControlCenter = XGControlCenter::create(this);
		CC_BREAK_IF(!ControlCenter);
		ControlCenter->retain();

		Map = XGMap::create(10, 10);
		CC_BREAK_IF(!Map);
		Map->retain();

		GameInput = XGInput::create();
		CC_BREAK_IF(!GameInput);
		addChild(GameInput, InputZOrder);

		GameDisplay = XGDisplay::create(Map);
		CC_BREAK_IF(!GameDisplay);
		addChild(GameDisplay, DisplayZOrder);
		GameDisplay->setTileBackground("tile.png");

		return true;
	}
	while (false);

	return false;
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
