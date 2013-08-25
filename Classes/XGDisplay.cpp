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

	TileObjects->release();
	DebugDraws->release();

	TileBkSprites->release();
	TileObjSprites->release();

}

bool XGDisplay::init(XGGameInitInfo* pInitInfo, XGMap* map)
{
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		Map = map;
		MapSize = pInitInfo->MapSize;
		unsigned int tileNum = MapSize.getTileNum();
		TileBkSprites = CCArray::createWithCapacity(tileNum);
		CC_BREAK_IF(!TileBkSprites);
		for (unsigned int i = 0; i < tileNum; i++)
		{
			XGTile* tile = dynamic_cast<XGTile*>(Map->TileInfo->objectAtIndex(i));
			CCSprite* tileSprite = CCSprite::create();
			if (!tileSprite)
			{
				break;
			}
			tileSprite->setPosition(GetPositionForTileCoord(tile->Position));
			TileBkSprites->addObject(tileSprite);
			addChild(tileSprite);
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

		DebugDraws = new CCArray();

		return true;
	}
	while(false);

	return false;
}

XGDisplay* XGDisplay::create(XGGameInitInfo* pInitInfo,XGMap* map)
{
	XGDisplay* pReturnValue = new XGDisplay();
	if (pReturnValue)
	{
		if (pReturnValue->init(pInitInfo, map))
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

void XGDisplay::setTileBkAt(cocos2d::CCPoint& pos, const char* filename)
{
	CCSprite* pFogSprite = getTileSpriteInArray(pos, TileBkSprites);
	if (pFogSprite)
	{
		pFogSprite->initWithFile(filename);
	}	
}

void XGDisplay::setTileBkInRange(cocos2d::CCPoint& pos, int range, const char* filename)
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
	for(unsigned int i = 0; i < Map->TileInfo->count(); i++)
	{
		XGTile* tile = dynamic_cast<XGTile*>(Map->TileInfo->objectAtIndex(i));
		CCSprite* tileSprite = dynamic_cast<CCSprite*>(TileBkSprites->objectAtIndex(i));
		
		if(i%7 == 0 || i%79==0)
		{
			tile->bBlock = true;
		}
		if(tile->bBlock)
		{
			tileSprite->initWithFile("TileFog.png");
		}
		else
		{
			tileSprite->initWithFile("Tile.png");
		}

		//CCLOG("[Nav] display tile %d %f %f %d", i, tile->Position.x, tile->Position.y, tile->bBlock);
	}
}





bool XGDisplay::addTileObject(cocos2d::CCPoint& pos, const char* filename)
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

bool XGDisplay::moveTileObject(cocos2d::CCPoint& fromPos, cocos2d::CCPoint& toPos)
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

bool XGDisplay::removeTileObject(cocos2d::CCPoint& pos)
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

void XGDisplay::changeFogAt(cocos2d::CCPoint& pos, bool isShow)
{
	CCSprite* pFogSprite = getTileSpriteInArray(pos, TileFogSprites);
	if (pFogSprite)
	{
		pFogSprite->setVisible(isShow);
	}
}

void XGDisplay::changeFogInRange(cocos2d::CCPoint& pos, int range, bool isShow)
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

CCPoint XGDisplay::getTileCenterPos(cocos2d::CCPoint& pos)
{
	return CCPoint(TileSize.width*(0.5+pos.x), TileSize.height*(0.5+pos.y));
}

cocos2d::CCPoint& XGDisplay::getTileLocation(CCPoint posInPixel)
{
	return ccp(posInPixel.x/TileSize.width,
		posInPixel.y/TileSize.height);
}

CCSprite* XGDisplay::getTileSpriteInArray(cocos2d::CCPoint& pos, CCArray* pArray)
{
	return NULL;
}

void XGDisplay::DrawPath(cocos2d::CCArray* Path)
{
	for(unsigned int i = 0; i < Path->count(); i++)
	{
		PathNode* node = dynamic_cast<PathNode*>(Path->objectAtIndex(i));
		CCSprite* vNode = CCSprite::create("PathNode.png");
		vNode->setPosition(GetPositionForTileCoord(node->position));
		this->addChild(vNode);
		DebugDraws->addObject(vNode);
	}
}

void XGDisplay::ClearPath()
{
	for(unsigned int i = 0; i < DebugDraws->count(); i++)
	{
		CCSprite* vNode = dynamic_cast<CCSprite*>(DebugDraws->objectAtIndex(i));
		this->removeChild(vNode);
	}

	DebugDraws->removeAllObjects();
}


void XGDisplay::AddUnit(XGUnit* unit)
{
	this->addChild(unit->Sprite, TileObjZOrder);
	Map->SetOccupied(unit->Position);
	OnUnitPositionChanged(unit);
}
void XGDisplay::RemoveUnit(XGUnit* unit)
{
	this->removeChild(unit->Sprite);
	Map->ClearOccupied(unit->Position);
}
void XGDisplay::OnUnitPositionChanged(XGUnit* unit)
{
	unit->Sprite->setPosition(GetPositionForTileCoord(unit->Position));
}



CCPoint XGDisplay::GetTileCoordForPosition(CCPoint pos)
{
	int x = pos.x / TileSize.width;
	int y = (MapSize.height * TileSize.height - pos.y) / TileSize.height;
	return ccp(x,y);
}

CCPoint XGDisplay::GetPositionForTileCoord(CCPoint pos)
{
	int x = pos.x * TileSize.width + TileSize.width / 2;
	int y = (MapSize.height - pos.y) * TileSize.height - TileSize.height / 2;
	return ccp(x,y);
}