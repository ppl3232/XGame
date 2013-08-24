#include "XGDisplay.h"

#include "XGGameInitInfo.h"

USING_NS_CC;

XGDisplay::XGDisplay()
	: TileSize(32, 32)
	, TileSprites(NULL)
	, TileObjSprites(NULL)
	, TileFogSprites(NULL)
{
}

XGDisplay::~XGDisplay()
{
	TileSprites->release();
	TileObjSprites->release();
}

bool XGDisplay::init(XGGameInitInfo* pInitInfo)
{
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		MapSize = pInitInfo->MapSize;
		MapSize.width = int(MapSize.width);
		MapSize.height = int(MapSize.height);
		unsigned int tileNum = MapSize.width*MapSize.height;
		TileSprites = CCArray::createWithCapacity(tileNum);
		CC_BREAK_IF(!TileSprites);
		for (unsigned int i = 0; i < tileNum; i++)
		{
			CCSprite* tileSprite = CCSprite::create();
			if (!tileSprite)
			{
				break;
			}
			int tileX = i % int(MapSize.width);
			int tileY = i / int(MapSize.width);
			tileSprite->setPosition(CCPoint(
				TileSize.width*(tileX+0.5), TileSize.height*(tileY+0.5)));
			TileSprites->addObject(tileSprite);
			addChild(tileSprite, TileZOrder);
		}
		CC_BREAK_IF(TileSprites->count() != tileNum);
		TileSprites->retain();

		TileObjSprites = CCArray::create();
		CC_BREAK_IF(!TileObjSprites);
		for (unsigned int i = 0; i < tileNum; i++)
		{
			CCSprite* tileObjSprite = CCSprite::create();
			if (!tileObjSprite)
			{
				break;
			}
			int tileX = i % int(MapSize.width);
			int tileY = i / int(MapSize.width);
			tileObjSprite->setPosition(CCPoint(
				TileSize.width*(tileX+0.5), TileSize.height*(tileY+0.5)));
			TileObjSprites->addObject(tileObjSprite);
			addChild(tileObjSprite, TileObjZOrder);
		}
		CC_BREAK_IF(TileFogSprites->count() != tileNum);
		TileObjSprites->retain();

		TileFogSprites = CCArray::create();
		CC_BREAK_IF(TileFogSprites);
		for (unsigned int i = 0; i < tileNum; i++)
		{
			CCSprite* tileFogSprite = CCSprite::create("FogCoverTile.png");
			if (!tileFogSprite)
			{
				break;
			}
			int tileX = i % int(MapSize.width);
			int tileY = i / int(MapSize.width);
			tileFogSprite->setPosition(CCPoint(
				TileSize.width*(tileX+0.5), TileSize.height*(tileY+0.5)));
			TileObjSprites->addObject(tileFogSprite);
			addChild(tileFogSprite, TileFogZOrder);
		}
		CC_BREAK_IF(TileFogSprites->count() != tileNum);
		TileFogSprites->retain();

		return true;
	}
	while(false);

	return false;
}

XGDisplay* XGDisplay::create(XGGameInitInfo* pInitInfo)
{
	XGDisplay* pReturnValue = new XGDisplay();
	if (pReturnValue)
	{
		if (pReturnValue->init(pInitInfo))
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

void XGDisplay::setTileSprites(const char* filename)
{
	CCObject* pTileObj = NULL;
	CCARRAY_FOREACH(TileSprites, pTileObj)
	{
		CCSprite* tileSprite = dynamic_cast<CCSprite*>(pTileObj);
		if (tileSprite)
		{
			tileSprite->initWithFile(filename);
		}
	}
}

void XGDisplay::changeFogAt(int x, int y, bool isShow)
{
	CCSprite* pFogSprite = dynamic_cast<CCSprite*>(
		TileFogSprites->objectAtIndex(x+y*MapSize.width));
	if (pFogSprite)
	{
		pFogSprite->setVisible(isShow);
	}
}

void XGDisplay::changeFogInRange(int x, int y, int range, bool isShow)
{
	CCObject* pFogSpriteObj = NULL;
	int curX = 0, curY = 0;
	CCARRAY_FOREACH(TileFogSprites, pFogSpriteObj)
	{
		CCSprite* pFogSprite = dynamic_cast<CCSprite*>(pFogSpriteObj);
		if (pFogSprite && ((curX - x) + (curY - y) <= range))
		{
			pFogSprite->setVisible(isShow);
		}

		// calculate next location
		if (curX == int(MapSize.width))
		{
			curY++;
		}
		curX = ++curX % int(MapSize.width);
	}
}
