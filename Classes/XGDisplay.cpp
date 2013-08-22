#include "XGDisplay.h"

USING_NS_CC;

XGDisplay::XGDisplay()
	: TileSize(32, 32)
	, TileBackgroundFileName(NULL)
	, TileBackgrounds(NULL)
	, TileObjects(NULL)
{
}

XGDisplay::~XGDisplay()
{
}

bool XGDisplay::init()
{
	do
	{
		CC_BREAK_IF(!CCLayer::init());



		return true;
	}
	while(false);

	return false;
}

XGDisplay* XGDisplay::create()
{
	XGDisplay* pReturnValue = new XGDisplay();
	if (pReturnValue && pReturnValue->init())
	{
		pReturnValue->autorelease();
	}
	else
	{
		if (pReturnValue)
		{
			delete pReturnValue;
		}
		pReturnValue = NULL;
	}
	return pReturnValue;
}

void XGDisplay::setTileSize(CCSize tileSize)
{
	TileSize = tileSize;
}
