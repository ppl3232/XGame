#ifndef __XG_DISPLAY_H__
#define __XG_DISPLAY_H__

#include "cocos2d.h"

class XGMap;
class XGDisplay: public cocos2d::CCLayer
{
// constructor/destructor
public:
    XGDisplay();
    virtual ~XGDisplay();

// override
public:
	virtual bool init(XGMap* map);

// method
public:
	static XGDisplay* create(XGMap* map);

	void setTileSize(cocos2d::CCSize tileSize);
	void setTileBackground(const char* filename);

// member
protected:
	XGMap*							Map;

	cocos2d::CCSize					TileSize;

	// backgrounds of tiles, store CCSprite
	cocos2d::CCArray*				TileBackgrounds;
	// objects in tiles, store CCSprite
	cocos2d::CCArray*				TileObjects;
};

#endif  // __XG_DISPLAY_H__
