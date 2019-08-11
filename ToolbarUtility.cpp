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
	if (std::find(_activeOptions.begin(), _activeOptions.end(), t->GetActiveOptionSet()) == _activeOptions.end())
		_activeOptions.push_back(t->GetActiveOptionSet());
}

void ToolbarUtility::HideToolbar(Toolbar* t)
{
	t->HideToolbar();
	//extend this to hide sub toolbars too
	_activeOptions.erase(std::remove(_activeOptions.begin(), _activeOptions.end(), t->GetActiveOptionSet()), _activeOptions.end());
}

void ToolbarUtility::SetMouseState(std::string state)
{
	_mouse->SetMouseState(state);
}