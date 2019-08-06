#include "ToolbarUtility.h"

void ToolbarUtility::SetToolbarReferences(std::map <std::string, Toolbar*>* teaSet)
{
	_toolbars = teaSet;
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
}

void ToolbarUtility::TriggerToolbar(Toolbar* t, std::string options)
{
	t->ShowToolbar(options);
	_activeOptions.push_back(t->GetActiveOptionSet());
}

void ToolbarUtility::HideToolbar(Toolbar* t)
{
	t->HideToolbar();
	_activeOptions.erase(std::remove(_activeOptions.begin(), _activeOptions.end(), t->GetActiveOptionSet()), _activeOptions.end());
}