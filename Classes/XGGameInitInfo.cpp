#include "XGGameInitInfo.h"

USING_NS_CC;

XGGameInitInfo::XGGameInitInfo()
{
}

XGGameInitInfo::~XGGameInitInfo()
{
}

XGGameInitInfo* XGGameInitInfo::create()
{
	XGGameInitInfo* pReturnValue = new XGGameInitInfo();
	if (pReturnValue)
	{
		pReturnValue->autorelease();
	}
	return pReturnValue;
}
