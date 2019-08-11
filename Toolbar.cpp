#include "Toolbar.h"

void Toolbar::Update(sf::Vector2f camPos)
{
	if (_visible)
	{
		_bgSprite.setPosition(_position.x + camPos.x, _position.y + camPos.y);
		if (_activeOptionSet != "")
		{
			for (int x = 0; x < _optionSets[_activeOptionSet].size(); x++)
			{
				_optionSets[_activeOptionSet].at(x)->Update(camPos);
			}
		}
	}
}

std::vector<Option*> Toolbar::GetActiveOptionSet()
{ 
	if(_visible)
		return _optionSets[_activeOptionSet];
	return std::vector<Option*>();
}

bool Toolbar::CheckShortCutKeys()
{
	if (sf::Keyboard::isKeyPressed(_shortCut))
	{
		_visible = true;
		_activeOptionSet = _primaryOptionSet;
		return true;
	}
	if (_visible)
	{
		if (_activeOptionSet != "")
		{
			for (int x = 0; x < _optionSets[_activeOptionSet].size(); x++)
			{
				sf::Keyboard::Key key = _optionSets[_activeOptionSet].at(x)->GetShortCut();
				std::cout << key << std::endl;
				std::cout << sf::Keyboard::isKeyPressed(key) << std::endl;
				if (sf::Keyboard::isKeyPressed(key))
				{
					_optionSets[_activeOptionSet].at(x)->Click();
					return true;
				}
			}
		}
	}
	return false;
}

void Toolbar::Draw(sf::RenderWindow &Window)
{
	if (_visible)
	{
		Window.draw(_bgSprite);
		if (_activeOptionSet != "")
		{
			for (int x = 0; x < _optionSets[_activeOptionSet].size(); x++)
			{
				if (_activeOptionSet != "")
					_optionSets[_activeOptionSet].at(x)->Draw(Window);
			}
		}
	}
}

void Toolbar::AddOptionSet(std::string name, std::vector<Option*> option)
{
	_optionSets.insert(std::pair<std::string, std::vector<Option*>>(name, option));
}

void Toolbar::HideToolbar()
{
	_visible = false;
	_activeOptionSet = "";
}

void Toolbar::ShowToolbar(std::string optionSet)
{
	_visible = true;
	_activeOptionSet = optionSet;
}

Toolbar::Toolbar()
{
}

Toolbar::Toolbar(sf::Vector2f pos, sf::Vector2i size, sf::Color imageFile)
{
	_bgSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size));
	_position = pos;
	_bgSprite.setTexture(_bgTexture);
	_bgSprite.setColor(imageFile);
	_shortCut = sf::Keyboard::Escape;
}

//needs to also define a standard option set
Toolbar::Toolbar(sf::Vector2f pos, sf::Vector2i size, sf::Color imageFile, sf::Keyboard::Key shortCut, std::string primary)
{
	_primaryOptionSet = primary;
	_bgSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size));
	_position = pos;
	_bgSprite.setTexture(_bgTexture);
	_bgSprite.setColor(imageFile);
	_shortCut = shortCut;
}

Toolbar::~Toolbar()
{
}
