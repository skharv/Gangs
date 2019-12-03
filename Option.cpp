#include "Option.h"

void Option::Draw(sf::RenderWindow &Window)
{
	Window.draw(_sprite);
}

Option::Option()
{
	_position = sf::Vector2f(0,0);
	_size = sf::Vector2i(0, 0);
	_texture.loadFromFile("images/blank.png");
}

Option::Option(ToolbarUtility * u)
{
	_util = u;
	_position = sf::Vector2f(0, 0);
	_size = sf::Vector2i(0, 0);
	_texture.loadFromFile("images/blank.png");
}

Option* Option::WithActiveFunction(std::string functionName)
{
	_activefunction = functionName;
	return this;
}

Option* Option::WithActiveParams(std::vector<std::string> active_params) 
{
	_activeParams = active_params;
	return this;
}

Option* Option::WithActiveParams(std::string active_params)
{
	_activeParams = std::vector<std::string>{ active_params };
	return this;
}

Option* Option::WithInactiveParams(std::string inactive_params)
{
	_inactiveParams = std::vector<std::string>{ inactive_params };
	return this;
}

Option* Option::WithInactiveFunction(std::string functionName)
{
	_inactivefunction = functionName;
	return this;
}

Option* Option::WithInactiveParams(std::vector<std::string> inactive_params)
{
	_inactiveParams = inactive_params;
	return this;
}

Option* Option::WithPoition(sf::Vector2f pos)
{
	_position = pos;
	return this;
}

Option* Option::WithSize(sf::Vector2i size) {
	_size = size;
	_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(_texture.getSize().x, _texture.getSize().y)));
	float modX = float(_size.x) / float(_texture.getSize().x);
	float modY = float(_size.y) / float(_texture.getSize().y);
	_sprite.setTexture(_texture);
	_sprite.setScale(sf::Vector2f(modX, modY));
	return this;
}

Option* Option::WithActiveImage(std::string imageFile) {
	_texture.loadFromFile("images/" + imageFile);
	if (_size.x == 0 && _size.y == 0)
		_size = sf::Vector2i(_texture.getSize().x, _texture.getSize().y);
	_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(_texture.getSize().x, _texture.getSize().y)));
	float modX = float(_size.x) / float(_texture.getSize().x);
	float modY = float(_size.y) / float(_texture.getSize().y);
	_sprite.setTexture(_texture);
	_sprite.setScale(sf::Vector2f(modX, modY));
	return this;
}

Option* Option::WithShortcut(sf::Keyboard::Key shortCut)
{
	_shortCut = shortCut;
	return this;
}

void Option::Update(sf::Vector2f camPos)
{
	_sprite.setPosition(_position.x + camPos.x, _position.y + camPos.y);
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