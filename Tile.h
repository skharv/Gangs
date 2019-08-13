#ifndef _TILE_H
#define _TILE_H

#include <vector>
#include <SFML/Graphics.hpp>

class Tile;

struct Links
{
	Tile *_north;
	Tile *_south;
	Tile *_east;
	Tile *_west;
};

enum Direction {North = 0, South = 1, East = 2, West = 3};

class Tile
{
private:
	Links* _links;

	int _index;
	int _roadValue; //this name will change
	sf::Vector2f _position;
public:
	void SetIndex(int i) { _index = i; };
	int GetIndex() { return _index; };

	void CalculateRoadValue();
	int GetRoadValue() { return _roadValue; };

	void SetPosition(sf::Vector2f Position) { _position = Position; };
	sf::Vector2f GetPosition() { return _position; };

	void AddConnection(Tile * Tile, Direction D);

	Tile(int Index, sf::Vector2f Position);
	Tile();
	~Tile();
};

#endif