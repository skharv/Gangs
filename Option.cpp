#include "Option.h"

void Option::Draw(sf::RenderWindow &Window)
{
	Window.draw(_sprite);
}

Option::Option()
{
}

void Option::Update(sf::Vector2f camPos)
{
	_sprite.setPosition(_position.x + camPos.x, _position.y + camPos.y);
}

Option::Option(ToolbarUtility* u, std::string active_function, std::vector<std::string> active_params, sf::Vector2f pos, sf::Vector2i size, std::string imageFile, sf::Keyboard::Key shortCut)
{
	_util = u;
	_activefunction = active_function;
	_activeParams = active_params;
	_inactivefunction = "";
	_position = pos;
	_texture.loadFromFile("images/" + imageFile);
	float modX = float(size.x) / float(_texture.getSize().x);
	float modY = float(size.y) / float(_texture.getSize().y);
	_sprite.setTexture(_texture);
	_sprite.setScale(sf::Vector2f(modX, modY));
	_shortCut = shortCut;
}

Option::Option(ToolbarUtility* u, std::string active_function, std::vector<std::string> active_params, std::string inactive_function, std::vector<std::string> inactive_params, sf::Vector2f pos, sf::Vector2i size, std::string imageFile, sf::Keyboard::Key shortCut)
{
	_util = u;
	_activefunction = active_function;
	_activeParams = active_params;
	_inactivefunction = inactive_function;
	_inactiveParams = inactive_params;
	_position = pos;
	_texture.loadFromFile("images/" + imageFile);
	float modX = float(size.x) / float(_texture.getSize().x);
	float modY = float(size.y) / float(_texture.getSize().y);
	_sprite.setTexture(_texture);
	_sprite.setScale(sf::Vector2f(modX, modY));
	_shortCut = shortCut;
}

Option::Option(ToolbarUtility* u, std::string active_function, std::vector<std::string> active_params, std::string inactive_function, std::vector<std::string> inactive_params, sf::Vector2f pos, sf::Vector2i size, std::string imageFile)
{
	_util = u;
	_activefunction = active_function;
	_activeParams = active_params;
	_inactivefunction = inactive_function;
	_inactiveParams = inactive_params;
	_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size));
	_position = pos;
	_texture.loadFromFile("images/" + imageFile);
	float modX = float(size.x) / float(_texture.getSize().x);
	float modY = float(size.y) / float(_texture.getSize().y);
	_sprite.setTexture(_texture);
	_sprite.setScale(sf::Vector2f(modX, modY));
	_shortCut = sf::Keyboard::Escape;
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