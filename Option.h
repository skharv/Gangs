#ifndef _OPTION_H
#define _OPTION_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "ToolbarUtility.h"

class ToolbarUtility;

class Option
{
private:
	ToolbarUtility* _util;
	bool state = false;
	sf::Texture _texture;
	sf::Sprite _sprite;
	std::string _activefunction;
	std::string _inactivefunction;
	std::vector<std::string> _activeParams;
	std::vector<std::string> _inactiveParams;
	sf::Vector2f _position;
	sf::Keyboard::Key _shortCut;
	void Active();
	void InActive();
public:
	Option();
	Option(ToolbarUtility* u, std::string f, std::vector<std::string> params, sf::Vector2f pos, sf::Vector2i size, sf::Color imageFile, sf::Keyboard::Key shortCut);
	Option(ToolbarUtility* u, std::string active_function, std::vector<std::string> active_params, std::string inactive_function, std::vector<std::string> inactive_params, sf::Vector2f pos, sf::Vector2i size, sf::Color imageFile, sf::Keyboard::Key shortCut);
	Option(ToolbarUtility* u, std::string active_function, std::vector<std::string> active_params, std::string inactive_function, std::vector<std::string> inactive_params, sf::Vector2f pos, sf::Vector2i size, sf::Color imageFile);
	void Draw(sf::RenderWindow &Window);
	void Update(sf::Vector2f camPos);
	sf::Keyboard::Key GetShortCut() { return _shortCut; };
	void SetShortCut(sf::Keyboard::Key k) { _shortCut = k; };
	void Click();
	sf::RectangleShape GetButtonShape();
	~Option();
};

#endif