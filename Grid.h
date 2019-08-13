#ifndef _GRID_H
#define _GRID_H

#include "Tile.h"
#include "Utility.h"
#include <vector>

#define TILEX 64
#define TILEY 32

#include <SFML/Graphics.hpp>
#include "Utility.h"

class Grid
{
private:
	Utility _utility;
	sf::Vector2f _gridSize;
	sf::Texture _texture;
	sf::Sprite _sprite;
	Utility* _util;

	std::vector<std::vector<Tile*>> _tiles;
public:
	void Draw(sf::RenderWindow &Window);

	sf::Vector2f GetSize() { return sf::Vector2f(TILEX, TILEY); };

	Tile* GetTile(sf::Vector2f Position);

	Grid(sf::Vector2f GridSize);
	Grid();
	~Grid();
};

#endif