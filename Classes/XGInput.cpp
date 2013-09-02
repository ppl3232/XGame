
#include "XGInput.h"
#include "XGGameInfo.h"
#include "XGBattle.h"
#include "XGPlayer.h"
USING_NS_CC;

XGInput::XGInput()
	: CurrentControlUnit(NULL)
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

void XGInput::setControlUnit(XGUnit* pControlUnit)
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
	//battle->BeginNewTurn(); // for test
	TilePoint touchPos = GameInfo->getDisplay()->GetTileCoordForPosition(pTouch->getLocation());

	CCArray* PlayerUnits = GameInfo->GetBattle()->GetPlayer()->Units;
	for(unsigned int i = 0; i < PlayerUnits->count(); i++)
	{
		XGUnit* unit = dynamic_cast<XGUnit*>(PlayerUnits->objectAtIndex(i));
		if(unit->Position.equals(touchPos))
		{
			CurrentControlUnit = unit;
			return;
		}
	}

	if(CurrentControlUnit != NULL)
	{
		CurrentControlUnit->ActionMove(touchPos);
	}
	

}

void XGInput::ccTouchCancelled(CCTouch* pTouch, CCEvent* pEvent)
{
}
