#ifndef _UTILITY_H
#define _UTILITY_H

#include <SFML/Graphics.hpp>

// This class should probs be static so it's shit can be called from anywhere.

class Utility
{
private:
	sf::Vector2f _gridSize;
	float _gridRatio;
public:
	sf::Vector2f IsoWorldToGrid(sf::Vector2f WorldPosition);
	sf::Vector2f IsoGridToWorld(sf::Vector2f GridPosition);

	sf::Vector2f SquareWorldToGrid(sf::Vector2f WorldPosition);
	sf::Vector2f SquareGridToWorld(sf::Vector2f GridPosition);

	void setGridSize(sf::Vector2f GirdSize) { _gridSize = GirdSize; };
	void setGridSize(float GridX, float GridY) { _gridSize = sf::Vector2f(GridX, GridY); };
	bool RectPoint(sf::RectangleShape rect, sf::Vector2f point);
	bool RectRect(sf::RectangleShape rectA, sf::RectangleShape rectB);

	Utility() { _gridSize = sf::Vector2f(0, 0); _gridRatio = 0; };
	~Utility() {};
};

#endif