#ifndef _MOUSE_H
#define _MOUSE_H

#include <SFML/Graphics.hpp>
#include "Option.h"
#include "Utility.h"
#include "ToolbarUtility.h"
#include "Camera.h"
#include <iostream>
#include "Grid.h"

class Option;
class ToolbarUtility;

class Mouse
{
private:
	Utility *_utility;
	Grid* _grid;
	ToolbarUtility *_toolbarUtility;
	sf::Texture _texture;
	sf::Sprite _sprite;
	sf::Vector2f _position;
	std::string _mouseState;

	void Zone(std::string s);
public:
	void Update(sf::RenderWindow* Window);
	void Draw(sf::RenderWindow &Window);

	void SetPosition(sf::Vector2f Position) { _position = Position; };
	void Click(std::string mouseState, sf::RenderWindow& Window);

	void SetMouseState(std::string state);

	void UpdateCursorPos();
	Mouse(std::string FilePath, Utility* utility, ToolbarUtility* toolbarUtil, Grid* grid);
	Mouse();
	~Mouse();
};

#endif