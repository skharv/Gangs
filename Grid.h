#ifndef _GRID_H
#define _GRID_H

#include <vector>
#include <SFML/Graphics.hpp>

class Grid
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;

	std::vector<sf::Vector2f> _positions;
public:
	void Update();
	void Draw(sf::RenderWindow &Window);

	sf::Vector2f GetSize() { return sf::Vector2f(_texture.getSize()); };

	Grid(sf::Vector2f GridSize);
	Grid();
	~Grid();
};

#endif