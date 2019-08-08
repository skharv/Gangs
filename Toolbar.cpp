#include "Toolbar.h"

void Toolbar::Update()
{
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
	_bgSprite.setPosition(pos);
	_bgSprite.setTexture(_bgTexture);
	_bgSprite.setColor(imageFile);
}

Toolbar::~Toolbar()
{
}
