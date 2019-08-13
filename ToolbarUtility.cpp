#include "ToolbarUtility.h"

void ToolbarUtility::SetToolbarReferences(std::map <std::string, Toolbar*>* teaSet)
{
	_toolbars = teaSet;
}

void ToolbarUtility::Draw(sf::RenderWindow &Window)
{
	std::map <std::string, Toolbar*>::iterator it;
	for (it = _toolbars->begin(); it != _toolbars->end(); it++)
		it->second->Draw(Window);
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

void ToolbarUtility::SetMouseState(std::string state)
{
	_mouse->SetMouseState(state);
}

bool ToolbarUtility::CheckButtonClick(sf::Vector2f mousePos)
{
	//check activeOptions for intersect - that button is pressed
	std::map <std::string, Toolbar*>::iterator it;
	for (it = _toolbars->begin(); it != _toolbars->end(); it++)
	{
		bool result = it->second->CheckButtonClick(mousePos);
		if (result)
			return true;
	}
	return false;
}