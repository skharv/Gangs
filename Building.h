#ifndef _BUILDING_H
#define _BUILDING_H

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Utility.h"
#include "Drawable.h"

class Building : public Drawable
{
private:
	std::vector<Util::Direction> _footprint;
	std::vector<Tile*> _highlightTiles;
public:
	void PlacementUpdate(Tile* t);
	void SetFootprint(std::vector<Util::Direction> footprint);
	void SetOrigin(sf::Vector2f origin);
	void PlaceBuilding();
	bool ValidPlacement() { return _validLocation; };
	void CancelPlacement();
	Building(std::string file);
	Building();
	~Building();
};

#endif