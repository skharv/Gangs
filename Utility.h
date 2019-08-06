#ifndef _UTILITY_H
#define _UTILITY_H

#include <SFML/Graphics.hpp>

class Utility
{
private:
	sf::Vector2f _gridSize;
	float _gridRatio;
public:
	sf::Vector2f WorldToGrid(sf::Vector2f WorldPosition);
	sf::Vector2f GridToWorld(sf::Vector2f GridPosition);

	void setGridSize(sf::Vector2f GirdSize) { _gridSize = GirdSize; };
	void setGridSize(float GridX, float GridY) { _gridSize = sf::Vector2f(GridX, GridY); };

	Utility() { _gridSize = sf::Vector2f(0, 0); _gridRatio = 0; };
	~Utility() {};
};

#endif