#include "XGUnit.h"

USING_NS_CC;

XGUnit::XGUnit()
	: Type(eUnit_Unknown)
	, ActionPoint(0)
{
}

XGUnit::~XGUnit()
{
}

CCObject* XGUnit::copyWithZone(CCZone* pZone)
{
	return NULL;
}

bool XGUnit::init()
{
	return true;
}
