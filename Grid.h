#ifndef _GRID_H
#define _GRID_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Utility.h"

class Grid
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	Utility* _util;

	std::vector<sf::Vector2f> _positions;
public:
	void Update();
	void Draw(sf::RenderWindow &Window);

	sf::Sprite GetTile(sf::Vector2f pos);
	sf::Vector2f GetSize() { return sf::Vector2f(_texture.getSize()); };

	Grid(sf::Vector2f GridSize);
	Grid();
	~Grid();
};

#endif