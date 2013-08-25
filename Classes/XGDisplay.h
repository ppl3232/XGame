#ifndef __XG_DISPLAY_H__
#define __XG_DISPLAY_H__

#include "cocos2d.h"
#include "XGUnit.h"
#include "XGTile.h"
#include "XGMap.h"

class XGGameInitInfo;

class XGDisplay: public cocos2d::CCLayer
{
// constructor/destructor
public:
    XGDisplay();
    virtual ~XGDisplay();

// override
public:
	virtual bool init(XGGameInitInfo* pInitInfo, XGMap* map);

// method
public:
	static XGDisplay* create(XGGameInitInfo* pInitInfo, XGMap* map);
	cocos2d::CCSprite* getTileSpriteInArray(cocos2d::CCPoint& pos, cocos2d::CCArray* pArray);
	void setTileBkAt(cocos2d::CCPoint& pos, const char* filename);
	void setTileBkInRange(cocos2d::CCPoint& pos, int range, const char* filename);
	void setTileBkToAll(const char* filename);

	// please ensure object not in a same tile by yourself
	// @return true if add tile object successfully
	bool addTileObject(cocos2d::CCPoint& pos, const char* filename);
	// please ensure object not in a same tile by yourself
	// @return true if move tile object successfully
	bool moveTileObject(cocos2d::CCPoint& fromPos, cocos2d::CCPoint& toPos);
	// please ensure object not in a same tile by yourself
	// @return true if remove tile object successfully
	bool removeTileObject(cocos2d::CCPoint& pos);

	void changeFogAt(cocos2d::CCPoint& pos, bool isShow);
	void changeFogInRange(cocos2d::CCPoint& pos, int range, bool isShow);
	void changeFogToAll(bool isShow);

	void setTileSize(cocos2d::CCSize tileSize);

	// @return a pixel position by passing tile position
	cocos2d::CCPoint getTileCenterPos(cocos2d::CCPoint& pos);
	// @return a tile position using a giving pixel position
	cocos2d::CCPoint& getTileLocation(cocos2d::CCPoint posInPixel);


	void DrawPath(cocos2d::CCArray* Path);
	void ClearPath();

	void AddUnit(XGUnit* unit);
	void RemoveUnit(XGUnit* unit);
	void OnUnitPositionChanged(XGUnit* unit);


	cocos2d::CCPoint GetTileCoordForPosition(cocos2d::CCPoint pos);
	cocos2d::CCPoint GetPositionForTileCoord(cocos2d::CCPoint pos);

// member
public:
	XGMap*							Map;

// member
private:
	XGMapSize						MapSize;
	cocos2d::CCSize					TileSize;

protected:
	// backgrounds of tiles, store CCSprite
	cocos2d::CCArray*				TileBkSprites;
	static const int				TileZOrder = 100;
	// objects in tiles, store CCSprite

	cocos2d::CCArray*				TileObjects;

	cocos2d::CCArray*				DebugDraws;

	cocos2d::CCArray*				TileObjSprites;
	static const int				TileObjZOrder = 200;
	// fog in tiles, store CCSprite
	cocos2d::CCArray*				TileFogSprites;
	static const int				TileFogZOrder = 300;
};

#endif  // __XG_DISPLAY_H__
