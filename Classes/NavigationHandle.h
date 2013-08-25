#ifndef __NAVIGATIONHANDLE_H__
#define __NAVIGATIONHANDLE_H__

#include "cocos2d.h"
#include "XGGameInfo.h"
#include "XGGameData.h"

class PathNode : public cocos2d::CCObject
{
public:
	static PathNode* create(cocos2d::CCPoint& pos);
	virtual bool init(cocos2d::CCPoint& pos);
	

public:
	bool isEqual(PathNode *Other);
	int	 fScore();
	void ClearPathInfo();


public:
	cocos2d::CCPoint	position;
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
	
	
	bool FindPath(cocos2d::CCPoint& start, cocos2d::CCPoint& end);
	bool FindPathWithMove(cocos2d::CCPoint& start, cocos2d::CCPoint& end, int move);
	cocos2d::CCArray* GetPath();
	bool GetNextMoveLocation(cocos2d::CCPoint& pos);
	
	cocos2d::CCArray* GetAdjacentNode(PathNode* origin);

	int CalHScore(cocos2d::CCPoint& from, cocos2d::CCPoint& to);
	int CalGScore(PathNode* node, int edgeCost);
	cocos2d::CCArray* InsertOpenList(cocos2d::CCArray* openList, PathNode* node);

	bool InitGraph();
	void ClearGraphPathInfo();
	PathNode* GetNode(cocos2d::CCPoint& pos);
	

public:
	XGGameInfo*					GameInfo;
	cocos2d::CCArray*			Path;
	cocos2d::CCArray*			Graph;
};



#endif	


