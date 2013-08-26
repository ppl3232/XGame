#ifndef __NAVIGATIONHANDLE_H__
#define __NAVIGATIONHANDLE_H__

#include "cocos2d.h"
#include "XGGameInfo.h"
#include "XGGameData.h"

class PathNode : public cocos2d::CCObject
{
public:
	static PathNode* create(TilePoint pos);
	virtual bool init(TilePoint pos);
	

public:
	bool isEqual(PathNode *Other);
	int	 fScore();
	void ClearPathInfo();


public:
	TilePoint	position;
	int					gScore;
	int					hScore;
	PathNode*			parent;
};



class NavigationHandle : public cocos2d::CCObject
{
public:
	virtual ~NavigationHandle();

	static NavigationHandle* create(XGGameInfo* info);
	virtual bool init(XGGameInfo* info);

public:
	
	
	bool FindPath(TilePoint start, TilePoint end);
	bool FindPathWithMove(TilePoint start, TilePoint end, int move);
	cocos2d::CCArray* GetPath();
	bool GetNextMoveLocation(TilePoint pos);
	
	cocos2d::CCArray* GetAdjacentNode(PathNode* origin);

	int CalHScore(TilePoint from, TilePoint to);
	int CalGScore(PathNode* node, int edgeCost);
	cocos2d::CCArray* InsertOpenList(cocos2d::CCArray* openList, PathNode* node);

	bool InitGraph();
	void ClearGraphPathInfo();
	PathNode* GetNode(TilePoint pos);
	

public:
	XGGameInfo*					GameInfo;
	cocos2d::CCArray*			Path;
	cocos2d::CCArray*			Graph;
};



#endif	


