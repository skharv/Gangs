#include "Tile.h"



void Tile::CalculateRoadValue()
{
	int value = 0;

	if (_links->_north->GetIndex() == 1)
		value += 1;

	if (_links->_west->GetIndex() == 1)
		value += 2;

	if (_links->_south->GetIndex() == 1)
		value += 8;

	if (_links->_east->GetIndex() == 1)
		value += 4;

	_roadValue = value;
}

void Tile::AddConnection(Tile* Tile, Direction D)
{
	switch (D)
	{
	case North:
		_links->_north = Tile;
		break;
	case South:
		_links->_south = Tile;
		break;
	case East:
		_links->_east = Tile;
		break;
	case West:
		_links->_west = Tile;
		break;
	}
}

Tile::Tile(int Index, sf::Vector2f Position)
{
	_index = Index;
	_position = Position;
	_links = new Links;
}

Tile::Tile()
{
}


Tile::~Tile()
{
}
