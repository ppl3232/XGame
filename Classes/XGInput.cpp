#include "XGInput.h"

USING_NS_CC;

XGInput::XGInput()
{
}

XGInput::~XGInput()
{
}

bool XGInput::init()
{
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		setTouchMode(kCCTouchesOneByOne);
		setTouchEnabled(true);

		return true;
	} while (false);

	return false;
}

void XGInput::setControlUnit(XGPlayerUnit* pControlUnit)
{
	CurrentControlUnit = pControlUnit;
}

bool XGInput::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	return true;
}

void XGInput::ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent)
{
}

void XGInput::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
}

void XGInput::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
}
