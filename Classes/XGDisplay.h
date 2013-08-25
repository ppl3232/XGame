#ifndef __XG_DISPLAY_H__
#define __XG_DISPLAY_H__

#include "cocos2d.h"

#include "XGTile.h"

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

	void setTileBkAt(XGTilePoint pos, const char* filename);
	void setTileBkInRange(XGTilePoint pos, int range, const char* filename);
	void setTileBkToAll(const char* filename);

	// please ensure object not in a same tile by yourself
	// @return true if add tile object successfully
	bool addTileObject(XGTilePoint pos, const char* filename);
	// please ensure object not in a same tile by yourself
	// @return true if move tile object successfully
	bool moveTileObject(XGTilePoint fromPos, XGTilePoint toPos);
	// please ensure object not in a same tile by yourself
	// @return true if remove tile object successfully
	bool removeTileObject(XGTilePoint pos);

	void changeFogAt(XGTilePoint pos, bool isShow);
	void changeFogInRange(XGTilePoint pos, int range, bool isShow);
	void changeFogToAll(bool isShow);

	void setTileSize(cocos2d::CCSize tileSize);

	// @return a pixel position by passing tile position
	cocos2d::CCPoint getTileCenterPos(XGTilePoint pos);
	// @return a tile position using a giving pixel position
	XGTilePoint getTileLocation(cocos2d::CCPoint posInPixel);

protected:
	cocos2d::CCSprite* getTileSpriteInArray(
		XGTilePoint pos, cocos2d::CCArray* pArray);

// member
private:
	XGMapSize						MapSize;
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
};

#endif  // __XG_DISPLAY_H__
