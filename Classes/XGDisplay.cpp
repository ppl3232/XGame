#include "XGDisplay.h"

#include "XGGameInitInfo.h"
#include "NavigationHandle.h"

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
	TileFogSprites->release();
	DebugDraws->release();
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
			CCSprite* pTileSprite = CCSprite::create();
			CC_BREAK_IF(!pTileSprite);
			TilePoint tilePos(i%MapSize.width, i/MapSize.width);
			pTileSprite->setContentSize(TileSize);
			pTileSprite->setPosition(GetPositionForTileCoord(tilePos));
			TileBkSprites->addObject(pTileSprite);
			addChild(pTileSprite);
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
			CCSprite* pTileFogSprite = CCSprite::create("FogCoverTile.png");
			CC_BREAK_IF(!pTileFogSprite);
			TilePoint tilePos(i%MapSize.width, i/MapSize.width);
			pTileFogSprite->setContentSize(TileSize);
			pTileFogSprite->setPosition(GetPositionForTileCoord(tilePos));
			pTileFogSprite->setVisible(false);
			TileFogSprites->addObject(pTileFogSprite);
			addChild(pTileFogSprite, TileFogZOrder);
		}
		CC_BREAK_IF(TileFogSprites->count() != tileNum);
		TileFogSprites->retain();

		setTileBkToAll("Tile.png","TileBlock.png", pInitInfo->MapTiles);

		DebugDraws = CCArray::create();
		CC_BREAK_IF(!DebugDraws);
		DebugDraws->retain();

		//test code
		//this->schedule(schedule_selector(XGDisplay::ScheduleTest), 2.0);

		return true;
	}
	while(false);

	return false;
}

void XGDisplay::ScheduleTest(float dt)
{
	CCLog("[Test] Schedule test!");
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

void XGDisplay::setTileBkAt(TilePoint pos, const char* filename)
{
	CCSprite* pFogSprite = getTileSpriteInArray(pos, TileBkSprites);
	if (pFogSprite)
	{
		pFogSprite->initWithFile(filename);
	}	
}

void XGDisplay::setTileBkInRange(TilePoint pos, int range, const char* filename)
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


// overload function for display info from original Map-Tiles data
void XGDisplay::setTileBkToAll(const char* NormalTexture, const char* BlockTexture, CCArray* MapTiles)
{
	CCObject* pTileObj = NULL;

	for(int i = 0; i < MapTiles->count(); i++)
	{
		XGTile* tile = dynamic_cast<XGTile*>(MapTiles->objectAtIndex(i));
		CCSprite* tileSprite = dynamic_cast<CCSprite*>(TileBkSprites->objectAtIndex(i));
		if(tile && tileSprite)
		{
			if(tile->bBlock)
			{
				tileSprite->initWithFile(BlockTexture);
			}
			else
			{
				tileSprite->initWithFile(NormalTexture);
			}

		}
	}
}

void XGDisplay::setTileBkToAll(const char* filename)
{
	CCObject* pTileObj = NULL;

	CCARRAY_FOREACH(TileBkSprites, pTileObj)
	{
		CCSprite* pTileSprite = dynamic_cast<CCSprite*>(pTileObj);
		if (pTileSprite)
		{
			pTileSprite->initWithFile(filename);
		}
	}
}





bool XGDisplay::addTileObject(TilePoint pos, const char* filename)
{
	// add obj sprite
	CCSprite* pNewTileObj = CCSprite::create(filename);
	if (!pNewTileObj)
	{
		return false;
	}
	pNewTileObj->setContentSize(TileSize);
	pNewTileObj->setPosition(GetPositionForTileCoord(pos));
	TileObjSprites->addObject(pNewTileObj);
	addChild(pNewTileObj, TileObjZOrder);

	return true;
}








bool XGDisplay::removeTileObject(TilePoint pos)
{
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(TileObjSprites, pObj)
	{
		CCSprite* pSprite = dynamic_cast<CCSprite*>(pObj);
		if (pSprite)
		{
			// find target obj
			if (GetTileCoordForPosition(pSprite->getPosition()).equals(pos))
			{
				TileObjSprites->removeObject(pObj);
				return true;
			}
		}
	}

	return false;	
}

void XGDisplay::changeFogAt(TilePoint pos, bool isShow)
{
	CCSprite* pFogSprite = getTileSpriteInArray(pos, TileFogSprites);
	if (pFogSprite)
	{
		pFogSprite->setVisible(isShow);
	}
}

void XGDisplay::changeFogInRange(TilePoint pos, int range, bool isShow)
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


TilePoint XGDisplay::GetTileCoordForPosition(CCPoint pos)
{
	int x = pos.x / TileSize.width;
	int y = (MapSize.height * TileSize.height - pos.y) / TileSize.height;
	return TilePoint(x,y);
}

CCPoint XGDisplay::GetPositionForTileCoord(TilePoint pos)
{
	int x = pos.x * TileSize.width + TileSize.width / 2;
	int y = (MapSize.height - pos.y) * TileSize.height - TileSize.height / 2;
	return ccp(x,y);
}

CCPoint XGDisplay::getTileCenterPos(TilePoint pos)
{
	return CCPoint(TileSize.width*(0.5+pos.x), TileSize.height*(0.5+pos.y));
}

TilePoint XGDisplay::getTileLocation(CCPoint posInPixel)
{
	return TilePoint(posInPixel.x/TileSize.width,
		posInPixel.y/TileSize.height);
}

CCSprite* XGDisplay::getTileSpriteInArray(TilePoint pos, CCArray* pArray)
{
	return dynamic_cast<CCSprite*>(
		pArray->objectAtIndex(pos.x+pos.y*MapSize.width));
}

void XGDisplay::debugDrawPath(cocos2d::CCArray* Path)
{
	for(unsigned int i = 0; i < DebugDraws->count(); i++)
	{
		CCSprite* vNode = dynamic_cast<CCSprite*>(DebugDraws->objectAtIndex(i));
		this->removeChild(vNode);
	}

	DebugDraws->removeAllObjects();

	for(unsigned int i = 0; i < Path->count(); i++)
	{
		PathNode* node = dynamic_cast<PathNode*>(Path->objectAtIndex(i));
		CCSprite* vNode = CCSprite::create("PathNode.png");
		vNode->setPosition(GetPositionForTileCoord(node->position));
		this->addChild(vNode);
		DebugDraws->addObject(vNode);
	}
}

bool XGDisplay::moveTileObject(TilePoint fromPos, TilePoint toPos, float interval)
{
	CCObject* pObj = NULL;
	CCARRAY_FOREACH(TileObjSprites, pObj)
	{
		CCSprite* pSprite = dynamic_cast<CCSprite*>(pObj);
		if (pSprite)
		{
			// find target obj
			CCLOG("[Game] moveTileObject");
			if (GetTileCoordForPosition(pSprite->getPosition()).equals(fromPos))
			{
				CCLOG("[Game] succeed");
				LatentMove(pSprite, GetPositionForTileCoord(toPos), interval);
				//pSprite->setPosition(GetPositionForTileCoord(toPos));
				return true;
			}
		}
	}

	return false;
}

void XGDisplay::LatentMove(CCSprite* target, CCPoint dest, float interval)
{
	CCFiniteTimeAction* actionMove = CCMoveTo::create(interval, dest);
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(XGDisplay::LatentMoveFinished));
	target->runAction( CCSequence::create(actionMove, actionMoveDone, NULL) );
	CCLOG("[Move] LatentMove %p", target);
}

void XGDisplay::LatentMoveFinished(CCNode* sender)
{
	CCSprite* sprite = dynamic_cast<CCSprite*>(sender);
}





