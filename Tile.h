#ifndef _TILE_H
#define _TILE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Utility.h"

class Tile
{
private:
	enum SocialClass { high, medium, low };
	std::map <Util::Direction, Tile *> _links;
	int _index;
	int _roadValue; //this name will change
	sf::Vector2f _position;
	sf::Color _colour;
	bool _occupied;
	SocialClass _socialClass;
public:
	void SetIndex(int i) { _index = i; };
	int GetIndex() { return _index; };

	void CalculateRoadValue();
	int GetRoadValue() { return _roadValue; };

	void SetPosition(sf::Vector2f Position) { _position = Position; };
	sf::Vector2f GetPosition() { return _position; };

	void AddConnection(Tile * tile, Util::Direction D);
	Tile* GetConnection(Util::Direction D);

	void SetSocialClass(SocialClass sc) { _socialClass = sc; };
	SocialClass GetSocialClass() { return _socialClass; };

	void SetColour(sf::Color c) { _colour = c; };
	sf::Color GetColour() { return _colour; };

	void SetOccupiedStatus(bool b) { _occupied = b; };
	bool GetOccupiedStatus() { return _occupied; };

	Tile(int Index, sf::Vector2f Position);
	Tile();
	~Tile();
};

#endif