#include "Toolbar.h"

void Toolbar::Update(sf::Vector2f camPos)
{
	if (_active && _visible)
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
	if(_active)
		return _optionSets[_activeOptionSet];
	return std::vector<Option*>();
}

bool Toolbar::CheckShortCutKeys()
{
	if (sf::Keyboard::isKeyPressed(_shortCut))
	{
		_active = true;
		_activeOptionSet = _primaryOptionSet;
		return true;
	}
	if (_active)
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
					ClickOption(_optionSets[_activeOptionSet].at(x));
					return true;
				}
			}
		}
	}
	return false;
}

void Toolbar::ClickOption(Option* selected)
{
	if(_activeOption != NULL && _activeOption != selected)
		_activeOption->SwitchingSelection();
	selected->Click();
	_activeOption = selected;
}

void Toolbar::Draw(sf::RenderWindow &Window)
{
	if (_active && _visible)
	{
		Window.draw(_bgSprite);
		if (_activeOptionSet != "")
		{
			for (int x = 0; x < _optionSets[_activeOptionSet].size(); x++)
			{
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
	_active = false;
	if (_activeOption != NULL)
	{
		_activeOption->SwitchingSelection();
		_activeOption = NULL;
	}
	_activeOptionSet = "";
}

void Toolbar::ShowToolbar(std::string optionSet)
{
	_active = true;
	_activeOptionSet = optionSet;
}

bool Toolbar::CheckButtonClick(sf::Vector2f mousePos)
{
	if (_active == true)
	{
		if (_activeOptionSet != "")
		{
			for (int x = 0; x < _optionSets[_activeOptionSet].size(); x++)
			{
				if (_utility->RectPoint(_optionSets[_activeOptionSet].at(x)->GetButtonShape(), mousePos))
				{
					ClickOption(_optionSets[_activeOptionSet].at(x));
					return true;
				}
			}
		}
	}
	return false;
}

Toolbar::Toolbar()
{
}

Toolbar::Toolbar(sf::Vector2f pos, sf::Vector2i size, std::string imageFile, Utility* utility)
{
	_utility = utility;
	_bgSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size));
	_position = pos;
	_bgTexture.loadFromFile("images/" + imageFile);
	float modX = float(size.x) / float(_bgTexture.getSize().x);
	float modY = float(size.y) / float(_bgTexture.getSize().y);
	_bgSprite.setTexture(_bgTexture);
	_bgSprite.setScale(sf::Vector2f(modX, modY));
	_shortCut = sf::Keyboard::Escape;
	_activeOption = NULL;
}

//needs to also define a standard option set
Toolbar::Toolbar(sf::Vector2f pos, sf::Vector2i size, std::string imageFile, sf::Keyboard::Key shortCut, std::string primary, Utility* utility)
{
	_utility = utility;
	_primaryOptionSet = primary;
	_bgSprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size));
	_position = pos;
	_bgTexture.loadFromFile("images/" + imageFile);
	float modX = float(size.x) / float(_bgTexture.getSize().x);
	float modY = float(size.y) / float(_bgTexture.getSize().y);
	_bgSprite.setTexture(_bgTexture);
	_bgSprite.setScale(sf::Vector2f(modX, modY));
	_shortCut = shortCut;
	_activeOption = NULL;
}

Toolbar::~Toolbar()
{
}
