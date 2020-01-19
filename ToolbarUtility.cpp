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
	for (int x = 0; x < _drawVec.size(); x++)
	{
		_drawVec.at(x)->Draw(Window);
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

void ToolbarUtility::AddUnit(Unit u)
{
	u.PlaceUnit();
	bool placed = false;
	for (int x = 0; x < _units.size(); x++)
	{
		if (u.GetPosition().y > _units.at(x).GetPosition().y)
			continue;
		_units.insert(_units.begin() + x, u);
		placed = true;
		break;
	}
	if (!placed)
		_units.push_back(u);
}

void ToolbarUtility::ButtonAction(std::string function, std::vector<std::string> params)
{
	if (function == "TriggerToolbar")
	{
		TriggerToolbar(_toolbars->at(params[0]), params[1]);
	}
	if (function == "ToggleEditor")
	{
		ToggleEditor(_toolbars->at(params[0]), params[1]);
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

	if (_utility->getGameState() == Util::GameState::InGame)
	{
		for (int x = 0; x < _units.size(); x++)
		{
			_units.at(x).Separation(_units);
			_units.at(x).Alignment(_units);
			_units.at(x).Cohesion(_units);
			_units.at(x).Update();
		}
	}
	PrepDraw();
}

void ToolbarUtility::PrepDraw()
{
	_drawVec.clear();
	for (int x = 0; x < _units.size(); x++)
		_drawVec.push_back(&_units.at(x));

	int insertIndex = 0;
	for (int x = 0; x < _buildings.size(); x++) 
	{
		bool inserted = false;
		for (int y = 0; y < _drawVec.size(); y++)
		{
			if (_buildings.at(x).GetPosition().y > _drawVec.at(y)->GetPosition().y)
				continue;
			_drawVec.insert(_drawVec.begin() + y, &_buildings.at(x));
			insertIndex = y;
			inserted = true;
			break;
		}
		if (!inserted)
			_drawVec.push_back(&_buildings.at(x));
	}
}

void ToolbarUtility::TriggerToolbar(Toolbar* t, std::string options)
{
	t->ShowToolbar(options);
}

void ToolbarUtility::ToggleEditor(Toolbar* t, std::string options)
{
	if (_utility->getGameState() == Util::GameState::InGame) {
		_utility->setGameState(Util::GameState::Editor);
		t->ShowToolbar(options);
	}
	else {
		_utility->setGameState(Util::GameState::InGame);
		t->HideToolbar();
		ClearMouse();
	}
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