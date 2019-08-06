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
	void Active();
	void InActive();
public:
	Option();
	Option(ToolbarUtility* u, std::string f, std::vector<std::string> params);
	Option(ToolbarUtility* u, std::string active_function, std::vector<std::string> active_params, std::string inactive_function, std::vector<std::string> inactive_params);
	void Draw(sf::RenderWindow &Window);
	void Click();
	~Option();
};

#endif