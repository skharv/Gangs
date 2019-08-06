#include "Toolbar.h"

void Toolbar::Update()
{
}

void Toolbar::Draw(sf::RenderWindow &Window)
{
	Window.draw(_bgSprite);
	if (_visible)
	{
		for (int x = 0; x < _optionSets[activeOptionSet].size(); x++)
		{
			_optionSets[activeOptionSet].at(x)->Draw(Window);
		}
	}
}

void Toolbar::AddOptionSet(std::string name, std::vector<Option*> option)
{
	_optionSets.insert(std::pair<std::string, std::vector<Option*>>(name, option));
}

void Toolbar::ShowToolbar(std::string optionSet)
{
	_visible = true;
}

Toolbar::Toolbar()
{
}


Toolbar::~Toolbar()
{
}
