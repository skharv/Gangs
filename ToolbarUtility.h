#ifndef _TOOLBARUTILITY_H
#define _TOOLBARUTILITY_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Toolbar.h"
#include "Mouse.h"
#include "Grid.h"
#include "Building.h"

class Toolbar;
class Option;
class Mouse;

class ToolbarUtility
{
private:
	std::map <std::string, Toolbar*>* _toolbars;
	void TriggerToolbar(Toolbar* t, std::string options);
	void HideToolbar(Toolbar* t);
	void ClearMouse();
	void SetMouseState(std::string state);
	std::vector<Building> _buildings;
	Mouse* _mouse;
	Grid* _grid;
	Utility* _utility;
public:
	ToolbarUtility() {};
	ToolbarUtility(Grid* grid, Utility* utility) { _grid = grid; _utility = utility; };
	void SetMouseReference(Mouse* mouse) { _mouse = mouse; };
	void SetToolbarReferences(std::map <std::string, Toolbar*>* teaSet);
	void ButtonAction(std::string function, std::vector<std::string> params);
	void DrawUI(sf::RenderWindow &Window);
	void DrawMap(sf::RenderWindow &Window);
	void Update(sf::Vector2f camPos);
	void CheckShortCutKeys();
	void AddBuilding(Building b);
	bool CheckButtonClick(sf::Vector2f mousePos, bool mouseIsPoint);
};

#endif