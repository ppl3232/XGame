#include "XGDisplay.h"

#include "XGGameInitInfo.h"

USING_NS_CC;

XGDisplay::XGDisplay()
	: TileBkSprites(NULL)
	, TileObjSprites(NULL)
	, TileFogSprites(NULL)
{
	setTileSize(CCSize(32, 32));
}

XGDisplay::~XGDisplay()
{
	TileBkSprites->release();
	TileObjSprites->release();
}

bool XGDisplay::init(XGGameInitInfo* pInitInfo)
{
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		MapSize = pInitInfo->MapSize;
		unsigned int tileNum = MapSize.getTileNum();
		TileBkSprites = CCArray::createWithCapacity(tileNum);
		CC_BREAK_IF(!TileBkSprites);
		for (unsigned int i = 0; i < tileNum; i++)
		{
			CCSprite* tileSprite = CCSprite::create();
			if (!tileSprite)
			{
				break;
			}
			int tileX = i % MapSize.width;
			int tileY = i / MapSize.width;
			tileSprite->setContentSize(TileSize);
			tileSprite->setPosition(CCPoint(
				TileSize.width*(tileX+0.5), TileSize.height*(tileY+0.5)));
			TileBkSprites->addObject(tileSprite);
			addChild(tileSprite, TileZOrder);
		}
		CC_BREAK_IF(TileBkSprites->count() != tileNum);
		TileBkSprites->retain();

		TileObjSprites = CCArray::create();
		CC_BREAK_IF(!TileObjSprites);
		TileObjSprites->retain();

		TileFogSprites = CCArray::create();
		CC_BREAK_IF(!TileFogSprites);
		for (unsigned int i = 0; i < tileNum; i++)
		{
			CCSprite* tileFogSprite = CCSprite::create("FogCoverTile.png");
			if (!tileFogSprite)
			{
				break;
			}
			int tileX = i % MapSize.width;
			int tileY = i / MapSize.width;
			tileFogSprite->setContentSize(TileSize);
			tileFogSprite->setPosition(CCPoint(
				TileSize.width*(tileX+0.5), TileSize.height*(tileY+0.5)));
			tileFogSprite->setVisible(false);
			TileFogSprites->addObject(tileFogSprite);
			addChild(tileFogSprite, TileFogZOrder);
		}
		CC_BREAK_IF(TileFogSprites->count() != tileNum);
		TileFogSprites->retain();

		setTileBkToAll("tile.png");

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

void XGDisplay::setTileBkAt(XGTilePoint pos, const char* filename)
{
	CCSprite* pFogSprite = getTileSpriteInArray(pos, TileBkSprites);
	if (pFogSprite)
	{
		pFogSprite->initWithFile(filename);
	}	
}

void XGDisplay::setTileBkInRange(XGTilePoint pos, int range, const char* filename)
{
	CCObject* pTileBkSpriteObj = NULL;
	int curX = 0, curY = 0;
	CCARRAY_FOREACH(TileBkSprites, pTileBkSpriteObj)
	{
		CCSprite* pTileSBkprite = dynamic_cast<CCSprite*>(pTileBkSpriteObj);
		if (pTileSBkprite && ((curX - pos.x) + (curY - pos.y) <= range))
		{
			pTileSBkprite->initWithFile(filename);
		}

		// calculate next location
		if (curX == int(MapSize.width))
		{
			curY++;
		}
		curX = ++curX % int(MapSize.width);
	}	
}

void XGDisplay::setTileBkToAll(const char* filename)
{
	CCObject* pTileObj = NULL;
	CCARRAY_FOREACH(TileBkSprites, pTileObj)
	{
		CCSprite* tileSprite = dynamic_cast<CCSprite*>(pTileObj);
		if (tileSprite)
		{
			tileSprite->initWithFile(filename);
		}
	}
}

bool XGDisplay::addTileObject(XGTilePoint pos, const char* filename)
{
	// add obj sprite
	CCSprite* pNewTileObj = CCSprite::create(filename);
	if (!pNewTileObj)
	{
		return false;
	}
	pNewTileObj->setContentSize(TileSize);
	pNewTileObj->setPosition(getTileCenterPos(pos));
	TileObjSprites->addObject(pNewTileObj);
	addChild(pNewTileObj, TileObjZOrder);

	return true;
}

bool XGDisplay::moveTileObject(XGTilePoint fromPos, XGTilePoint toPos)
{
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(TileObjSprites, pObj)
	{
		CCSprite* pSprite = dynamic_cast<CCSprite*>(pObj);
		if (pSprite)
		{
			// find target obj
			if (getTileLocation(pSprite->getPosition()).equals(fromPos))
			{
				pSprite->setPosition(getTileCenterPos(toPos));
				return true;
			}
		}
	}

	return false;
}

bool XGDisplay::removeTileObject(XGTilePoint pos)
{
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(TileObjSprites, pObj)
	{
		CCSprite* pSprite = dynamic_cast<CCSprite*>(pObj);
		if (pSprite)
		{
			// find target obj
			if (getTileLocation(pSprite->getPosition()).equals(pos))
			{
				TileObjSprites->removeObject(pObj);
				return true;
			}
		}
	}

	return false;	
}

void XGDisplay::changeFogAt(XGTilePoint pos, bool isShow)
{
	CCSprite* pFogSprite = getTileSpriteInArray(pos, TileFogSprites);
	if (pFogSprite)
	{
		pFogSprite->setVisible(isShow);
	}
}

void XGDisplay::changeFogInRange(XGTilePoint pos, int range, bool isShow)
{
	CCObject* pFogSpriteObj = NULL;
	int curX = 0, curY = 0;
	CCARRAY_FOREACH(TileFogSprites, pFogSpriteObj)
	{
		CCSprite* pFogSprite = dynamic_cast<CCSprite*>(pFogSpriteObj);
		if (pFogSprite && ((curX - pos.x) + (curY - pos.y) <= range))
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

void XGDisplay::changeFogToAll(bool isShow)
{
	CCObject* pFogSpriteObj = NULL;
	CCARRAY_FOREACH(TileFogSprites, pFogSpriteObj)
	{
		CCSprite* pFogSprite = dynamic_cast<CCSprite*>(pFogSpriteObj);
		if (pFogSprite)
		{
			pFogSprite->setVisible(isShow);
		}
	}	
}

void XGDisplay::setTileSize(CCSize tileSize)
{
	TileSize = tileSize;
	TileSize.width = int(TileSize.width);
	TileSize.height = int(TileSize.height);

	CCObject* pSpriteObj = NULL;
	CCARRAY_FOREACH(TileBkSprites, pSpriteObj)
	{
		CCSprite* pSprite = dynamic_cast<CCSprite*>(pSpriteObj);
		if (pSprite)
		{
			pSprite->setContentSize(TileSize);
		}
	}

	CCARRAY_FOREACH(TileObjSprites, pSpriteObj)
	{
		CCSprite* pSprite = dynamic_cast<CCSprite*>(pSpriteObj);
		if (pSprite)
		{
			pSprite->setContentSize(TileSize);
		}
	}

	CCARRAY_FOREACH(TileFogSprites, pSpriteObj)
	{
		CCSprite* pSprite = dynamic_cast<CCSprite*>(pSpriteObj);
		if (pSprite)
		{
			pSprite->setContentSize(TileSize);
		}
	}
}

CCPoint XGDisplay::getTileCenterPos(XGTilePoint pos)
{
	return CCPoint(TileSize.width*(0.5+pos.x), TileSize.height*(0.5+pos.y));
}

XGTilePoint XGDisplay::getTileLocation(CCPoint posInPixel)
{
	return XGTilePoint(posInPixel.x/TileSize.width,
		posInPixel.y/TileSize.height);
}

CCSprite* XGDisplay::getTileSpriteInArray(XGTilePoint pos, CCArray* pArray)
{
	return dynamic_cast<CCSprite*>(
		pArray->objectAtIndex(pos.x+pos.y*MapSize.width));
}
