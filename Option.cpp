#include "Option.h"

void Option::Draw(sf::RenderWindow &Window)
{
	Window.draw(_sprite);
}

Option::Option()
{
}

Option::Option(ToolbarUtility* u, std::string active_function, std::vector<std::string> active_params, sf::Vector2f pos, sf::Vector2i size, sf::Color imageFile)
{
	_util = u;
	_activefunction = active_function;
	_activeParams = active_params;
	_inactivefunction = "";
	_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size));
	_sprite.setPosition(pos);
	_sprite.setTexture(_texture);
	_sprite.setColor(imageFile);
}

Option::Option(ToolbarUtility* u, std::string active_function, std::vector<std::string> active_params, std::string inactive_function, std::vector<std::string> inactive_params, sf::Vector2f pos, sf::Vector2i size, sf::Color imageFile)
{
	_util = u;
	_activefunction = active_function;
	_activeParams = active_params;
	_inactivefunction = inactive_function;
	_inactiveParams = inactive_params;
	_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0), size));
	_sprite.setPosition(pos);
	_sprite.setTexture(_texture);
	_sprite.setColor(imageFile);
}

void Option::Active()
{
	state = true;
	_util->ButtonAction(_activefunction, _activeParams);
}

void Option::InActive()
{
	state = false;

	if(_inactivefunction != "")
		_util->ButtonAction(_inactivefunction, _inactiveParams);
}

void Option::Click()
{
	state ? InActive() : Active();
}

Option::~Option()
{
}


sf::RectangleShape Option::GetButtonShape()
{
	sf::RectangleShape result(sf::Vector2f(_sprite.getLocalBounds().width, _sprite.getLocalBounds().height));
	result.setPosition(_sprite.getPosition());
	return result;
}