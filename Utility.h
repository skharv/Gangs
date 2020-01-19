#ifndef _UTILITY_H
#define _UTILITY_H

#include <SFML/Graphics.hpp>

// This class should probs be static so it's shit can be called from anywhere.

namespace Util
{
	enum Direction { North = 0, South = 1, East = 2, West = 3, NorthEast = 4, SouthEast = 5, SouthWest = 6, NorthWest = 7 };
	enum GameState { Editor, InGame};
}

class Utility
{
private:
	sf::Vector2f _gridTileSize;
	sf::Vector2f _gridSize;
	float _gridRatio;
	Util::GameState _gameState;
public:
	static sf::Vector2f IsoWorldToGrid(sf::Vector2f WorldPosition, sf::Vector2f GridTileSize);
	static sf::Vector2f IsoGridToWorld(sf::Vector2f GridPosition, sf::Vector2f GridTileSize);

	static sf::Vector2f SquareWorldToGrid(sf::Vector2f WorldPosition, sf::Vector2f GridTileSize);
	static sf::Vector2f SquareGridToWorld(sf::Vector2f GridPosition, sf::Vector2f GridTileSize);

	sf::Vector2f getGridTileSize() { return _gridTileSize; };

	void setGridTileSize(sf::Vector2f GirdTileSize) { _gridTileSize = GirdTileSize; };
	void setGridTileSize(float GridTileX, float GridTileY) { _gridTileSize = sf::Vector2f(GridTileX, GridTileY); };
	void setGridSize(sf::Vector2f GirdSize) { _gridSize = GirdSize; };
	void setGridSize(float GridX, float GridY) { _gridSize = sf::Vector2f(GridX, GridY); };
	bool RectPoint(sf::RectangleShape rect, sf::Vector2f point);
	bool RectRect(sf::RectangleShape rectA, sf::RectangleShape rectB);
	sf::RectangleShape ConvertToRectShape(sf::Sprite s);
	void setGameState(Util::GameState val) { _gameState = val; };
	Util::GameState getGameState() { return _gameState; };

	Utility() { _gridTileSize = sf::Vector2f(0, 0); _gridRatio = 0; };
	~Utility() {};
};

#endif