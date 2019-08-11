#include "Mouse.h"

/* The mouse pos.
		To set the mouse "cursor" to land directly on a tile space
		you get the position of the mouse relative to the window,
		then you convert the world position of the mouse into the grid coords.
		After that you convert them BACK to world coords. This snaps the cursor
		to the specific tile.
*/
void Mouse::Update(sf::RenderWindow* Window)
{
	sf::Vector2f mousePos = Window->mapPixelToCoords(sf::Mouse::getPosition(*Window));
	//std::cout << mousePos.x << ", " << mousePos.y << std::endl;
	_position = _utility->GridToWorld(_utility->WorldToGrid(mousePos));
	_sprite.setPosition(_position);
}

void Mouse::Draw(sf::RenderWindow &Window)
{
	Window.draw(_sprite);
}

void Mouse::Click(std::string mouseState, std::vector <std::vector<Option*>>* activeOptions, sf::RenderWindow& Window)
{
	sf::Vector2f mousePos = Window.mapPixelToCoords(sf::Mouse::getPosition(Window));
	//std::cout << "CLICK! " << mousePos.x << ", " << mousePos.y << std::endl;
	if (!CheckButtonClick(activeOptions, mousePos))
	{
		if (_mouseState.substr(0, 4) == "ZONE")
			Zone(_mouseState.substr(5, _mouseState.length()));
	}
}

void Mouse::SetMouseState(std::string state)
{
	_mouseState = state;
}

bool Mouse::CheckButtonClick(std::vector <std::vector<Option*>>* activeOptions, sf::Vector2f mousePos)
{
	//check activeOptions for intersect - that button is pressed
	for (int x = 0; x < activeOptions->size(); x++)
	{
		int optionSetSize = activeOptions->at(x).size();
		for (int y = 0; y < optionSetSize; y++)
		{
			if (_utility->RectPoint(activeOptions->at(x).at(y)->GetButtonShape(), mousePos))
			{
				activeOptions->at(x).at(y)->Click();
				return true;
			}
		}
	}
	return false;
}

void Mouse::Zone(std::string s)
{
	if (s == "RESIDENTIAL")
	{
		//set tile stuff
	}
}

void Mouse::UpdateCursorPos()
{

}

Mouse::Mouse(std::string FilePath, Utility* utility)
{
	_utility = utility;
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
