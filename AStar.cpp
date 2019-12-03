#include "AStar.h"

bool AStar::isValid(int x, int y, Grid grid)
{
	Tile* t = grid.GetTile(Utility::IsoGridToWorld(sf::Vector2f(x, y), grid.GetTileSize()));
    if (t != NULL && !t->GetOccupiedStatus())
	{
        return true;
    } 
	return false;
}

bool AStar::isDestination(int x, int y, int destX, int destY)
{
	if (x == destX && y == destY)
	{
		return true;
	}
	return false;
}

float AStar::calculateH(int x, int y, int destX, int destY)
{
	float H = (sqrt((x - destX)*(x - destX) + (y - destY)*(y - destY)));
	return H;
}

std::vector<sf::Vector2f> AStar::aStar(sf::Vector2f start, sf::Vector2f dest, Grid &grid)
{
	std::vector<sf::Vector2f> empty;
	if (!isValid(dest.x, dest.y, grid))
		return empty;

	if (isDestination(start.x, start.y, dest.x, dest.y))
		return empty;

	std::vector<std::vector<bool>> closedList;

	std::vector<std::vector<Node>> allMap;
	for (int x = 0; x < grid.GetGridSize().x; x++)
	{
		std::vector<bool> closedYSet;
		std::vector<Node> allYSet;
		for (int y = 0; y < grid.GetGridSize().y; y++)
		{
			Node node = Node();
			node.fCost = FLT_MAX;
			node.gCost = FLT_MAX;
			node.hCost = FLT_MAX;
			node.parentX = -1;
			node.parentY = -1;
			node.x = x;
			node.y = y;

			closedYSet.push_back(false);
			allYSet.push_back(node);
		}
		closedList.push_back(closedYSet);
		allMap.push_back(allYSet);
	}

	int x = start.x;
	int y = start.y;
	allMap[x][y].fCost = 0.0;
	allMap[x][y].gCost = 0.0;
	allMap[x][y].hCost = 0.0;
	allMap[x][y].parentX = x;
	allMap[x][y].parentY = y;

	std::vector<Node> openList;
	openList.emplace_back(allMap[x][y]);
	bool destinationFound = false;
	
	while (!openList.empty() && openList.size() < (grid.GetGridSize().x * grid.GetGridSize().y))
	{
		Node node;
		do {
			float temp = FLT_MAX;
			std::vector<Node>::iterator itNode;
			for (std::vector<Node>::iterator it = openList.begin(); it != openList.end(); it = next(it))
			{
				Node n = *it;
				if (n.fCost < temp)
				{
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (!isValid(node.x, node.y, grid));

		x = node.x;
		y = node.y;
		closedList[x][y] = true;

		for (int newX = -1; newX <= 1; newX++)
		{
			for (int newY = -1; newY <= 1; newY++)
			{
				double gNew, hNew, fNew;
				if (isValid(x + newX, y + newY, grid))
				{
					if (isDestination(x + newX, y + newY, dest.x, dest.y))
					{
						//Destination found - make path
						allMap[x + newX][y + newY].parentX = x;
						allMap[x + newX][y + newY].parentY = y;
						destinationFound = true;
						return makePath(grid, allMap, dest.x, dest.y);
					}
					else if (!closedList[x + newX][y + newY])
					{
						gNew = node.gCost + 1.0;
						hNew = calculateH(x + newX, y + newY, dest.x, dest.y);
						fNew = gNew + hNew;
						// Check if this path is better than the one already present
						if (allMap[x + newX][y + newY].fCost == FLT_MAX || allMap[x + newX][y + newY].fCost > fNew)
						{
							// Update the details of this neighbour node
							allMap[x + newX][y + newY].fCost = fNew;
							allMap[x + newX][y + newY].gCost = gNew;
							allMap[x + newX][y + newY].hCost = hNew;
							allMap[x + newX][y + newY].parentX = x;
							allMap[x + newX][y + newY].parentY = y;
							openList.emplace_back(allMap[x + newX][y + newY]);
						}
					}
				}
			}
		}
	}
	if (destinationFound == false)
	{
		return empty;
	}
	return empty;
}

std::vector<sf::Vector2f> AStar::makePath(Grid grid, std::vector<std::vector<Node>> map, int destX, int destY)
{
	try
	{
		int x = destX;
		int y = destY;
		std::vector<Node> path;
		std::vector<sf::Vector2f> usablePath;

		while (!(map[x][y].parentX == x && map[x][y].parentY == y) && map[x][y].x != -1 && map[x][y].y != -1)
		{
			path.push_back(map[x][y]);
			int tempX = map[x][y].parentX;
			int tempY = map[x][y].parentY;
			x = tempX;
			y = tempY;
		}
		path.push_back(map[x][y]);
		for (int i = 0; i < path.size(); i++)
		{
			usablePath.push_back(Utility::IsoGridToWorld(sf::Vector2f(path[i].x, path[i].y), grid.GetTileSize()));
		}
		return usablePath;
	}
	catch (char* e)
	{
		throw "Could not make a path!";
	}

	return std::vector<sf::Vector2f>();
}

AStar::AStar()
{
}


AStar::~AStar()
{
}
