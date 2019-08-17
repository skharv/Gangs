#include "Tile.h"

void Tile::CalculateRoadValue()
{
	int value = 0;

	if (_links.find(Util::Direction::North) != _links.end() && _links[Util::Direction::North]->GetIndex() == 1)
		value += 1;

	if (_links.find(Util::Direction::West) != _links.end() && _links[Util::Direction::West]->GetIndex() == 1)
		value += 2;

	if (_links.find(Util::Direction::South) != _links.end() && _links[Util::Direction::South]->GetIndex() == 1)
		value += 8;

	if (_links.find(Util::Direction::East) != _links.end() && _links[Util::Direction::East]->GetIndex() == 1)
		value += 4;

	_roadValue = value;
}

void Tile::AddConnection(Tile* tile, Util::Direction D)
{
	_links.insert(std::pair<Util::Direction, Tile*>(D, tile));
}

Tile* Tile::GetConnection(Util::Direction D)
{
	if (_links.find(D) != _links.end() && _links[D] != this)
		return _links[D];
	return NULL;
}

Tile::Tile(int Index, sf::Vector2f Position)
{
	_index = Index;
	_position = Position;
	_links;
	_colour = sf::Color::White;
	_occupied = false;
}

Tile::Tile()
{
}


Tile::~Tile()
{
}
