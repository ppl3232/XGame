#ifndef __XG_DISPLAY_H__
#define __XG_DISPLAY_H__

#include "cocos2d.h"

class XGMap;
class XGDisplay: protected cocos2d::CCLayer
{
// constructor/destructor
public:
    XGDisplay();
    virtual ~XGDisplay();

// override
public:
	virtual bool init();

// method
public:
	static XGDisplay* create();

	void setTileSize(cocos2d::CCSize tileSize);

// member
protected:
	cocos2d::CCSize					TileSize;
	const char*						TileBackgroundFileName;

	// backgrounds of tiles
	cocos2d::CCArray*				TileBackgrounds;
	// objects in tiles
	cocos2d::CCArray*				TileObjects;
};

#endif  // __XG_DISPLAY_H__
