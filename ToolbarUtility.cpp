#include "ToolbarUtility.h"

void ToolbarUtility::SetToolbarReferences(std::map <std::string, Toolbar*>* teaSet)
{
	_toolbars = teaSet;
}

void ToolbarUtility::DrawUI(sf::RenderWindow &Window)
{
	std::map <std::string, Toolbar*>::iterator it;
	for (it = _toolbars->begin(); it != _toolbars->end(); it++)
		it->second->Draw(Window);
}

void ToolbarUtility::DrawMap(sf::RenderWindow &Window)
{
	for (int x = 0; x < _buildings.size(); x++)
	{
		_buildings.at(x).Draw(Window);
	}
}

void ToolbarUtility::AddBuilding(Building b)
{
	b.PlaceBuilding();
	bool placed = false;
	for (int x = 0; x < _buildings.size(); x++)
	{
		if (b.GetPosition().y > _buildings.at(x).GetPosition().y)
			continue;
		_buildings.insert(_buildings.begin() + x, b);
		placed = true;
		break;
	}
	if(!placed)
		_buildings.push_back(b);
}

void ToolbarUtility::ButtonAction(std::string function, std::vector<std::string> params)
{
	if (function == "TriggerToolbar")
	{
		TriggerToolbar(_toolbars->at(params[0]), params[1]);
	}
	if (function == "HideToolbar")
	{
		HideToolbar(_toolbars->at(params[0]));
	}
	if (function == "ClearMouse")
	{
		ClearMouse();
	}
	if (function == "SetMouseState")
	{
		SetMouseState(params[0]);
	}
}

void ToolbarUtility::CheckShortCutKeys()
{
	//this will do shortcuts for toolbars and active option sets
	std::map <std::string, Toolbar*>::iterator it;
	for (it = _toolbars->begin(); it != _toolbars->end(); it++)
	{
		if (it->second->CheckShortCutKeys())
			break;
	}
}

void ToolbarUtility::Update(sf::Vector2f camPos)
{
	std::map <std::string, Toolbar*>::iterator it;
	for (it = _toolbars->begin(); it != _toolbars->end(); it++)
		it->second->Update(camPos);
}

void ToolbarUtility::TriggerToolbar(Toolbar* t, std::string options)
{
	t->ShowToolbar(options);
}

void ToolbarUtility::HideToolbar(Toolbar* t)
{
	//hides passed through toolbar and makes the active button inactive to hide sub toolbars
	t->HideToolbar();
}

void ToolbarUtility::ClearMouse()
{
	_mouse->ClearMouse();
}

void ToolbarUtility::SetMouseState(std::string state)
{
	_mouse->SetMouseState(state);
}

bool ToolbarUtility::CheckButtonClick(sf::Vector2f mousePos, bool mouseIsPoint)
{
	if (mouseIsPoint)
	{
		//check activeOptions for intersect - that button is pressed
		std::map <std::string, Toolbar*>::iterator it;
		for (it = _toolbars->begin(); it != _toolbars->end(); it++)
		{
			bool result = it->second->CheckButtonClick(mousePos);
			if (result)
				return true;
		}
	}
	return false;
}