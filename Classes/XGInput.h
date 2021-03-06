#ifndef __XG_INPUT_H__
#define __XG_INPUT_H__

#include "cocos2d.h"
#include "XGUnit.h"
#include "XGBattle.h"
#include "XGGameInfo.h"


class XGInput: public cocos2d::CCLayer
{
// constructor/destructor
public:
    XGInput();
    virtual ~XGInput();

// override
public:
	virtual bool init();

    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);

// method
public:
	CREATE_FUNC(XGInput);

	void setControlUnit(XGUnit* pControlUnit);



// member
protected:
	XGUnit*					CurrentControlUnit;
public:
	XGBattle*				battle; // for test
	XGGameInfo*				GameInfo;
};

#endif  // __XG_INPUT_H__
