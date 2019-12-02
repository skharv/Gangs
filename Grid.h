#ifndef _GRID_H
#define _GRID_H

#include "Tile.h"
#include "Utility.h"
#include <vector>

#include <SFML/Graphics.hpp>
#include "Utility.h"

namespace gr
{
	enum GridType
	{
		ISOMETRIC = 0,
		SQUARE = 1
	};
}

class Grid
{
private:
	gr::GridType _gridType;
	Utility _utility;
	sf::Vector2f _gridSize, _tileSize;
	sf::Texture _texture;
	sf::Sprite _sprite;
	Utility* _util;

	std::vector<std::vector<Tile*>> _tiles;
public:
	void Draw(sf::RenderWindow &Window);

	sf::Vector2f GetTileSize() { return _tileSize; };
	sf::Vector2f GetGridSize() { return _gridSize; };
	Tile* GetTile(sf::Vector2f Position);
	std::vector<Tile*> IsoGetTiles(sf::RectangleShape rect);
	std::vector<sf::Vector2f> IsoGetTileCorners(sf::RectangleShape rect);

	Grid(gr::GridType Type, sf::Vector2f GridSize, sf::Vector2f TileSize);
	Grid();
	~Grid();
};

#endif