#ifndef __XGAIPLAYER_H__
#define __XGAIPLAYER_H__

#include "XGPlayer.h"

class XGAIPlayer : public XGPlayer
{
	// constructor & destructor
public:
	XGAIPlayer();
	virtual ~XGAIPlayer();

	// create & init
public:
	CREATE_FUNC(XGAIPlayer);
	virtual bool init();

	// method
public:

	// member
public:

};

#endif