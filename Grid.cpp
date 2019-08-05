#include "Grid.h"

void Grid::Update()
{
}

void Grid::Draw(sf::RenderWindow &Window)
{
	for (int i = 0; i < _positions.size(); i++)
	{
		_sprite.setPosition(_positions[i]);

		Window.draw(_sprite);
	}
}

Grid::Grid(sf::Vector2f GridSize)
{
	_texture.loadFromFile("images/dirttile.png");
	_sprite.setTexture(_texture, true);
	_sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);

	for (int i = 0; i < GridSize.x; i++)
	{
		for(int j = 0; j < GridSize.y; j++)
		{
			_positions.push_back(sf::Vector2f(((i * 0.5) * _texture.getSize().x) + (_texture.getSize().x * 0.5 * j), ((j * 0.5) * _texture.getSize().y) - (_texture.getSize().y * 0.5 * i)));
		}
	}
}

Grid::Grid()
{
}


Grid::~Grid()
{
}
