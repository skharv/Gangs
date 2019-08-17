#ifndef _BUILDING_H
#define _BUILDING_H

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Utility.h"

class Building
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	std::vector<Util::Direction> _footprint;
	std::vector<Tile*> _highlightTiles;
	bool _validLocation;
	bool _placed;
public:
	void PlacementUpdate(Tile* t);
	void Draw(sf::RenderWindow &Window);
	void SetFootprint(std::vector<Util::Direction> footprint);
	void SetOrigin(sf::Vector2f origin);
	sf::Vector2f GetPosition() { return _sprite.getPosition(); };
	void PlaceBuilding();
	bool ValidPlacement() { return _validLocation; };
	void CancelPlacement();
	Building(std::string file);
	Building();
	~Building();
};

#endif