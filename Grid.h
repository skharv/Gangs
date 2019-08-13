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

	sf::Texture _texture;
	sf::Sprite _sprite;
	Utility* _util;

	std::vector<std::vector<Tile*>> _tiles;
public:
	void Draw(sf::RenderWindow &Window);

	sf::Vector2f GetSize() { return sf::Vector2f(TILEX, TILEY); };

	Tile* GetTile(sf::Vector2f Position) { return _tiles[Position.x][Position.y]; };
	sf::Sprite GetTile(sf::Vector2f pos);
	sf::Vector2f GetSize() { return sf::Vector2f(_texture.getSize()); };

	Grid(sf::Vector2f GridSize);
	Grid();
	~Grid();
};

#endif