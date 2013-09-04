#ifndef __XG_DISPLAY_H__
#define __XG_DISPLAY_H__

#include "cocos2d.h"
#include "XGUnit.h"
#include "XGGameData.h"

class XGGameInitInfo;

class XGDisplay: public cocos2d::CCLayer
{
// constructor/destructor
public:
    XGDisplay();
    virtual ~XGDisplay();

// override
public:
	virtual bool init(XGGameInitInfo* pInitInfo);

// method
public:
	static XGDisplay* create(XGGameInitInfo* pInitInfo);

	void setTileBkAt(TilePoint pos, const char* filename);
	void setTileBkInRange(TilePoint pos, int range, const char* filename);
	void setTileBkToAll(const char* NormalTexture, const char* BlockTexture, cocos2d::CCArray* MapTiles);
	void setTileBkToAll(const char* filename);

	// please ensure object not in a same tile by yourself
	// @return true if add tile object successfully
	bool addTileObject(TilePoint pos, const char* filename);
	// please ensure object not in a same tile by yourself
	// @return true if move tile object successfully
	bool moveTileObject(TilePoint fromPos, TilePoint toPos);
	bool moveTileObject(XGUnit* unit, cocos2d::CCArray* Path);
	void MoveTileObjectFinished(cocos2d::CCNode* sender);

	// please ensure object not in a same tile by yourself
	// @return true if remove tile object successfully
	bool removeTileObject(TilePoint pos);

	void changeFogAt(TilePoint pos, bool isShow);
	void changeFogInRange(TilePoint pos, int range, bool isShow);
	void changeFogToAll(bool isShow);

	void setTileSize(cocos2d::CCSize tileSize);

	// @return a pixel position by passing tile position
	cocos2d::CCPoint getTileCenterPos(TilePoint pos);
	// @return a tile position using a giving pixel position
	TilePoint getTileLocation(cocos2d::CCPoint posInPixel);

	TilePoint GetTileCoordForPosition(cocos2d::CCPoint pos);
	cocos2d::CCPoint GetPositionForTileCoord(TilePoint pos);

	void debugDrawPath(cocos2d::CCArray* Path);

	// move sprite
	void LatentMove(cocos2d::CCSprite* target, cocos2d::CCPoint dest, float interval);
	void LatentMoveFinished(cocos2d::CCNode* sender);


	// test code
	void ScheduleTest(float dt);

protected:
	cocos2d::CCSprite* getTileSpriteInArray(TilePoint pos, cocos2d::CCArray* pArray);

// member
private:
	TileMapSize						MapSize;
	cocos2d::CCSize					TileSize;

protected:
	// backgrounds of tiles, store CCSprite
	cocos2d::CCArray*				TileBkSprites;
	static const int				TileZOrder = 100;
	// objects in tiles, store CCSprite
	cocos2d::CCArray*				TileObjSprites;
	static const int				TileObjZOrder = 200;
	// fog in tiles, store CCSprite
	cocos2d::CCArray*				TileFogSprites;
	static const int				TileFogZOrder = 300;

	cocos2d::CCArray*				DebugDraws;


public:

	XGUnit*							CurrentMoveUnit;

};

#endif  // __XG_DISPLAY_H__
