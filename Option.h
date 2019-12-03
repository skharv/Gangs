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
	sf::Vector2i _size;
	sf::Keyboard::Key _shortCut;
	void Active();
	void InActive();
public:
	Option();
	Option(ToolbarUtility * u);
	void Draw(sf::RenderWindow &Window);
	void Update(sf::Vector2f camPos);
	sf::Keyboard::Key GetShortCut() { return _shortCut; };
	void SetShortCut(sf::Keyboard::Key k) { _shortCut = k; };
	void Click();
	void SwitchingSelection() { InActive(); };
	sf::RectangleShape GetButtonShape();

	Option* WithActiveFunction(std::string functionName);
	Option* WithActiveParams(std::vector<std::string> active_params);
	Option* WithActiveParams(std::string active_params);
	Option* WithInactiveFunction(std::string functionName);
	Option* WithInactiveParams(std::vector<std::string> inactive_params);
	Option* WithInactiveParams(std::string active_params);
	Option* WithPoition(sf::Vector2f pos);
	Option* WithSize(sf::Vector2i size);
	Option* WithInactiveImage(std::string imageFile);
	Option* WithActiveImage(std::string imageFile);
	Option* WithShortcut(sf::Keyboard::Key shortCut);

	~Option();
};

#endif