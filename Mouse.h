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
	Camera* _camera;
	ToolbarUtility *_toolbarUtility;
	//sf::Sprite _pointerSprite;
	sf::Vector2f _position;
	std::string _mouseState;
	bool _mousePressed;
	sf::Vector2f _mouseStart;
	sf::RectangleShape _mouseSelect;
	sf::ConvexShape _tileSelect;

	bool _mouseMovePressed;
	sf::Vector2f _mouseMoveStart;

	void Zone(std::string s, std::vector<Tile*> t);
	int GetZoneCode(std::string s);
	void EditModeMouse(bool mouseIsPoint, sf::Vector2f mousePos, sf::RectangleShape shape);
public:
	void Update(sf::RenderWindow* Window);
	void DrawOver(sf::RenderWindow &Window);
	void DrawUnder(sf::RenderWindow &Window);

	void MouseMoveDown(sf::RenderWindow& Window);
	void MouseMoveUp();

	void MouseUp();
	void SetPosition(sf::Vector2f Position) { _position = Position; };
	void Click(sf::RenderWindow& Window);
	void MouseDown(sf::RenderWindow& Window);
	void SetMouseState(std::string state);

	Mouse(Utility* utility, ToolbarUtility* toolbarUtil, Grid* grid, Camera* camera);
	Mouse();
	~Mouse();
};

#endif