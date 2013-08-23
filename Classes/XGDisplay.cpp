#include "XGDisplay.h"

#include "XGMap.h"
#include "XGGameFlow.h"

USING_NS_CC;

XGDisplay::XGDisplay()
	: TileSize(32, 32)
	, TileBackgrounds(NULL)
	, TileObjects(NULL)
{
}

XGDisplay::~XGDisplay()
{
	TileBackgrounds->release();
	TileObjects->release();
}

bool XGDisplay::init(XGMap* map)
{
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		Map = map;

		unsigned int tileNum = Map->getTileNum();
		TileBackgrounds = CCArray::createWithCapacity(tileNum);
		CC_BREAK_IF(!TileBackgrounds);
		bool initBackgroundFailed = false;
		for (unsigned int i = 0; i < tileNum; i++)
		{
			CCSprite* tileSprite = CCSprite::create();
			if (!tileSprite)
			{
				initBackgroundFailed = true;
				break;
			}
			int tileX = i % Map->getSizeX();
			int tileY = i / Map->getSizeY();
			tileSprite->setPosition(CCPoint(
				TileSize.width*(tileX+0.5), TileSize.height*(tileY+0.5)));
			TileBackgrounds->addObject(tileSprite);
			addChild(tileSprite);
		}
		CC_BREAK_IF(initBackgroundFailed);
		TileBackgrounds->retain();

		TileObjects = CCArray::create();
		CC_BREAK_IF(!TileObjects);
		TileObjects->retain();

		return true;
	}
	while(false);

	return false;
}

XGDisplay* XGDisplay::create(XGMap* map)
{
	XGDisplay* pReturnValue = new XGDisplay();
	if (pReturnValue)
	{
		if (pReturnValue->init(map))
		{
			pReturnValue->autorelease();
		}
		else
		{
			delete pReturnValue;
			pReturnValue = NULL;
		}
	}
	return pReturnValue;
}

void XGDisplay::setTileSize(CCSize tileSize)
{
	TileSize = tileSize;
	TileSize.width = floor(TileSize.width);
	TileSize.height = floor(TileSize.height);
}

void XGDisplay::setTileBackground(const char* filename)
{
	CCObject* pTileObj = NULL;
	CCARRAY_FOREACH(TileBackgrounds, pTileObj)
	{
		CCSprite* tileSprite = dynamic_cast<CCSprite*>(pTileObj);
		if (tileSprite)
		{
			tileSprite->initWithFile(filename);
		}
	}
}
