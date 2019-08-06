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

void Mouse::Click(std::string mouseState, std::vector <std::vector<Option*>>* activeOptions)
{
	if (!CheckButtonClick(activeOptions))
	{
		//check mouse status and call appropriate function
	}
}

bool Mouse::CheckButtonClick(std::vector <std::vector<Option*>>* activeOptions)
{
	//check activeOptions for intersect - that button is pressed
	for (int x = 0; x < activeOptions->size(); x++)
	{
		int optionSetSize = activeOptions->at(x).size();
		for (int y = 0; y < optionSetSize; y++)
		{
			//if (collission is detected between _position and the option sprite)
				//activeOptions->at(x).at(y)->Click();
			//return true;
		}
	}
	return false;
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
