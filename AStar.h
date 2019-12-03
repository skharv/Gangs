#ifndef _ASTAR_H
#define _ASTAR_H

#include "Grid.h"
#include <stack>

struct Node
{
	int y;
	int x;
	int parentX;
	int parentY;
	float gCost;
	float hCost;
	float fCost;
};

inline bool operator < (const Node& lhs, const Node& rhs)
{
	return lhs.fCost < rhs.fCost;
}

class AStar
{
private:
	static bool isValid(int x, int y, Grid grid);
	static bool isDestination(int x, int y, int destX, int destY);
	static float calculateH(int x, int y, int destX, int destY);
	static std::vector<sf::Vector2f> makePath(Grid grid, std::vector<std::vector<Node>> map, int destX, int destY);
public:
	static std::vector<sf::Vector2f> aStar(sf::Vector2f start, sf::Vector2f dest, Grid &grid);

	AStar();
	~AStar();
};

#endif