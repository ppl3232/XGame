#include "NavigationHandle.h"
#include "XGMap.h"

USING_NS_CC;

// PathNode function start

PathNode* PathNode::create(TilePoint pos)
{
	PathNode* node = new PathNode();
	if(node && node->init(pos))
	{
		node->autorelease();
		return node;
	}
	else
	{
		CC_SAFE_DELETE(node);
		return NULL;
	}
}

bool PathNode::init(TilePoint pos)
{
	bool ret = false;
	do 
	{
		position = pos;
		gScore = 0;
		hScore = 0;
		parent = NULL;
		ret = true;
	} while (0);

	return ret;
}




bool PathNode::isEqual(PathNode *Other)
{
	return position.equals(Other->position);
}

int PathNode::fScore()
{
	return gScore + hScore;
}

void PathNode::ClearPathInfo()
{
	gScore = 0;
	hScore = 0;
	parent = NULL;
}


// PathNode function end


// NavigationHandle function start

NavigationHandle::~NavigationHandle()
{
	if(Path != NULL)
	{
		Path->release();
	}

	Graph->release();
}

NavigationHandle* NavigationHandle::create(XGGameInfo* info)
{
	NavigationHandle* handle = new NavigationHandle();
	if(handle && handle->init(info))
	{
		handle->autorelease();
		return handle;
	}
	else
	{
		CC_SAFE_DELETE(handle);
		return NULL;
	}
}

bool NavigationHandle::init(XGGameInfo* info)
{
	bool ret = false;
	do 
	{
		GameInfo = info;
		Path = new CCArray();
		PathIndex = 0;
		InitGraph();
		ret = true;
	} while (0);

	return ret;
}


bool NavigationHandle::InitGraph()
{
	CCArray* TileInfo = GameInfo->getMap()->TileInfo;

	Graph = new CCArray();

	for(unsigned int i = 0; i < TileInfo->count(); i++)
	{
		XGTile* tile = dynamic_cast<XGTile*>(TileInfo->objectAtIndex(i));
		PathNode* node = PathNode::create(tile->Position);
		Graph->addObject(node);
	}

	return true;
}

void NavigationHandle::ClearGraphPathInfo()
{
	for(unsigned int i = 0; i < Graph->count(); i++)
	{
		PathNode* node = dynamic_cast<PathNode*>(Graph->objectAtIndex(i));
		node->ClearPathInfo();
	}

	Path->removeAllObjects();
	PathIndex = 0;
	
}


PathNode* NavigationHandle::GetNode(TilePoint pos)
{
	for(unsigned int i = 0; i < Graph->count(); i++)
	{
		PathNode* node = dynamic_cast<PathNode*>(Graph->objectAtIndex(i));
		if(node->position.equals(pos))
		{
			return node;
		}
	}

	return NULL;
}


bool NavigationHandle::FindPathWithMove(TilePoint start, TilePoint end, int move)
{
	if(FindPath(start,end) && Path->count() <= move)
	{
		return true;
	}

	return false;
}




bool NavigationHandle::FindPath(TilePoint start, TilePoint end)
{
	bool bFindPath = false;
	CCArray* openList =  CCArray::create();
	CCArray* closedList = CCArray::create();

	ClearGraphPathInfo();

	PathNode* startNode = GetNode(start);
	PathNode* endNode = GetNode(end);
	openList->addObject(startNode);

	while(openList->count() != 0)
	{
		PathNode* keyNode = dynamic_cast<PathNode*>(openList->objectAtIndex(0));

		closedList->addObject(keyNode);
		openList->removeObject(keyNode);

		if(closedList->containsObject(endNode))
		{
			bFindPath = true;
			break;
		}

		CCArray* adjacentList = GetAdjacentNode(keyNode);
		for(unsigned int i = 0; i < adjacentList->count(); i++)
		{
			PathNode* node = dynamic_cast<PathNode*>(adjacentList->objectAtIndex(i));
			if(closedList->containsObject(node))
			{
				continue;
			}
			else if( !openList->containsObject(node) )
			{
				node->parent = keyNode;
				node->hScore = CalHScore(node->position, endNode->position);
				node->gScore = CalGScore(keyNode, 1);
				openList = InsertOpenList(openList, node);
			}
			else
			{
				if(node->gScore > CalGScore(keyNode,1))
				{
					node->parent = keyNode;
					node->gScore = CalGScore(keyNode,1); 
					openList->removeObject(node);
					openList = InsertOpenList(openList, node);
				}
			}
		}
	}

	if(bFindPath)
	{
		PathNode* kNode = dynamic_cast<PathNode*>(closedList->objectAtIndex(closedList->count() - 1));
		while(kNode->parent != NULL)
		{
			Path->insertObject(kNode, 0);
			kNode = kNode->parent;
		}
		return true;
	}

	return false;
}

CCArray* NavigationHandle::InsertOpenList(cocos2d::CCArray* openList, PathNode* node)
{
	for(unsigned int i = 0; i < openList->count(); i++)
	{
		PathNode* kNode = dynamic_cast<PathNode*>(openList->objectAtIndex(i));
		if(node->fScore() <= kNode->fScore())
		{
			openList->insertObject(node, i);
			return openList;
		}
	}

	openList->addObject(node);

	return openList;
}

int NavigationHandle::CalHScore(TilePoint from, TilePoint to)
{
	return GetDistance(from, to);
}

int NavigationHandle::CalGScore(PathNode* parent, int edgeCost)
{
	if(parent == NULL)
		return 0;
	
	return parent->gScore + edgeCost;
}


CCArray* NavigationHandle::GetAdjacentNode(PathNode* origin)
{
	CCArray* AdjacentNode = CCArray::create();
	std::vector<TilePoint> AdjacentPos = GameInfo->getMap()->GetAdjacentPos(origin->position);
	for(int i = 0; i < AdjacentPos.size(); i++)
	{
		PathNode* node = GetNode(AdjacentPos[i]);
		AdjacentNode->addObject(node);
	}

	return AdjacentNode;
}

bool NavigationHandle::GetNextMoveLocation(TilePoint& NextPos)
{
	if( PathIndex >= Path->count())
		return false;

	PathNode* node = dynamic_cast<PathNode*>(Path->objectAtIndex(PathIndex));
	NextPos = node->position;
	PathIndex++;
	return true;
}

cocos2d::CCArray* NavigationHandle::GetPath()
{
	return Path;
}


// NavigationHandle function end