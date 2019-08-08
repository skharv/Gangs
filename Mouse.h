#ifndef _MOUSE_H
#define _MOUSE_H

#include <SFML/Graphics.hpp>
#include "Option.h"
#include "Utility.h"
#include "Camera.h"
#include <iostream>

class Option;

class Mouse
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;
	Utility *_utility;
	sf::Vector2f _position;
	std::string _mouseState;

	void Zone(std::string s);
	bool CheckButtonClick(std::vector <std::vector<Option*>>* activeOptions, sf::Vector2f mousePos);
public:
	void Update(sf::RenderWindow* Window);
	void Draw(sf::RenderWindow &Window);

	void SetPosition(sf::Vector2f Position) { _position = Position; };
	void Click(std::string mouseState, std::vector <std::vector<Option*>>* activeOptions, sf::RenderWindow& Window);

	void SetMouseState(std::string state);

	void UpdateCursorPos();
	Mouse(std::string FilePath, Utility* utility);
	Mouse();
	~Mouse();
};

#endif