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

void Mouse::Click(std::string mouseState, sf::RenderWindow& Window)
{
	sf::Vector2f mousePos = Window.mapPixelToCoords(sf::Mouse::getPosition(Window));
	//std::cout << "CLICK! " << mousePos.x << ", " << mousePos.y << std::endl;
	if (!_toolbarUtility->CheckButtonClick(mousePos))
	{
		//get the tile
		if (_mouseState.substr(0, 4) == "ZONE")
			Zone(_mouseState.substr(5, _mouseState.length()));
	}
}

void Mouse::SetMouseState(std::string state)
{
	_mouseState = state;
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

Mouse::Mouse(std::string FilePath, Utility* utility, ToolbarUtility* toolbarUtil, Grid* grid)
{
	_toolbarUtility = toolbarUtil;
	_utility = utility;
	_texture.loadFromFile(FilePath);
	_sprite.setTexture(_texture);
	_sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
	_sprite.setColor(sf::Color::Green);
	_position = sf::Vector2f(0, 0);
	_grid = grid;
}


Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}
