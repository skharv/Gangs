#include "Building.h"

void Building::PlacementUpdate(Tile* t)
{
	for (int x = 0; x < _highlightTiles.size(); x++)
	{
		_highlightTiles.at(x)->SetColour(sf::Color::White);
	}
	_highlightTiles.clear();

	if (t != NULL)
	{
		_sprite.setPosition(t->GetPosition());
		t->SetColour(sf::Color::Green);
		_highlightTiles.push_back(t);
		_validLocation = true;
		for (int x = 0; x < _footprint.size(); x++)
		{
			t = t->GetConnection(_footprint.at(x));
			if (t == NULL || t->GetOccupiedStatus())
			{
				_validLocation = false;
				break;
			}
			t->SetColour(sf::Color::Green);
			_highlightTiles.push_back(t);

		}
		if (!_validLocation)
		{
			for (int x = 0; x < _highlightTiles.size(); x++)
			{
				_highlightTiles.at(x)->SetColour(sf::Color::White);
			}
			_highlightTiles.clear();
		}
	}
	else
		_validLocation = false;
}

void Building::CancelPlacement()
{
	for (int x = 0; x < _highlightTiles.size(); x++)
	{
		_highlightTiles.at(x)->SetColour(sf::Color::White);
	}
	_highlightTiles.clear();
}

void Building::PlaceBuilding()
{
	if (_validLocation)
	{
		_placed = true;
		_sprite.setColor(sf::Color::White);
		for (int x = 0; x < _highlightTiles.size(); x++)
		{
			_highlightTiles.at(x)->SetOccupiedStatus(true);
			_highlightTiles.at(x)->SetColour(sf::Color::White);
		}
		_highlightTiles.clear();
	}
}

void Building::SetOrigin(sf::Vector2f origin)
{
	origin.y = _sprite.getPosition().y + _sprite.getTextureRect().height - origin.y;
	_sprite.setOrigin(origin);
}

void Building::SetFootprint(std::vector<Util::Direction> footprint)
{
	_footprint = footprint;
}

void Building::Draw(sf::RenderWindow &Window)
{
	if (!_placed)
	{
		if (_validLocation)
			_sprite.setColor(sf::Color(255, 255, 255, 200));
		else
			_sprite.setColor(sf::Color(174, 25, 7, 200));
	}
	Window.draw(_sprite);
}

Building::Building(std::string file)
{
	_texture.loadFromFile("images/" + file);
	_sprite.setColor(sf::Color(255, 255, 255, 200));
	_sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
	_sprite.setTexture(_texture);
	_placed = false;
}

Building::Building()
{
}

Building::~Building()
{
}
