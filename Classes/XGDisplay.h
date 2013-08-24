#ifndef __XG_DISPLAY_H__
#define __XG_DISPLAY_H__

#include "cocos2d.h"

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

	void setTileSize(cocos2d::CCSize tileSize);
	void setTileSprites(const char* filename);
	void changeFogAt(int x, int y, bool isShow);
	void changeFogInRange(int x, int y, int range, bool isShow);

// member
private:
	cocos2d::CCSize					MapSize;
	cocos2d::CCSize					TileSize;

protected:
	// backgrounds of tiles, store CCSprite
	cocos2d::CCArray*				TileSprites;
	static const int				TileZOrder = 100;
	// objects in tiles, store CCSprite
	cocos2d::CCArray*				TileObjSprites;
	static const int				TileObjZOrder = 200;
	// fog in tiles, store CCSprite
	cocos2d::CCArray*				TileFogSprites;
	static const int				TileFogZOrder = 300;
};

#endif  // __XG_DISPLAY_H__
