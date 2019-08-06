#include "Utility.h"

sf::Vector2f Utility::WorldToGrid(sf::Vector2f WorldPosition)
{
	sf::Vector2f GridPosition;

	GridPosition.x = roundf((0.5 * ((WorldPosition.x / (_gridSize.x * 0.5) - (WorldPosition.y / (_gridSize.y * 0.5))))));
	GridPosition.y = roundf((0.5 * ((WorldPosition.x / (_gridSize.x * 0.5) + (WorldPosition.y / (_gridSize.y * 0.5))))));

	return GridPosition;
}

sf::Vector2f Utility::GridToWorld(sf::Vector2f GridPosition)
{
	sf::Vector2f WorldPosition;

	WorldPosition.x = (GridPosition.x + GridPosition.y) * _gridSize.x * 0.5;
	WorldPosition.y = (-GridPosition.x + GridPosition.y) * _gridSize.y * 0.5;

	return WorldPosition;
}
