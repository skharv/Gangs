#include "Mouse.h"

void Mouse::Update(sf::Vector2f Position)
{
	_position = Position;
	_sprite.setPosition(_position);
}

void Mouse::Draw(sf::RenderWindow &Window)
{
	Window.draw(_sprite);
}

Mouse::Mouse(std::string FilePath)
{
	_texture.loadFromFile(FilePath);
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
	_sprite.setColor(sf::Color::Green);
	_position = sf::Vector2f(0, 0);
}

Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}
