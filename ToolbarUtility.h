#ifndef _TOOLBARUTILITY_H
#define _TOOLBARUTILITY_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Toolbar.h"
#include "Mouse.h"
#include "Grid.h"
#include "Building.h"
#include "Unit.h"

class Toolbar;
class Option;
class Mouse;

class ToolbarUtility
{
private:
	std::map <std::string, Toolbar*>* _toolbars;
	void TriggerToolbar(Toolbar* t, std::string options);
	void ToggleEditor(Toolbar* t, std::string options);
	void HideToolbar(Toolbar* t);
	void ClearMouse();
	void SetMouseState(std::string state);
	std::vector<Building> _buildings;
	std::vector<Unit> _units;

	std::vector<Drawable*> _drawVec;

	Mouse* _mouse;
	Grid* _grid;
	Utility* _utility;
	void PrepDraw();
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
	void AddUnit(Unit u);

	std::vector<Building>* GetAllBuildings() { return &_buildings; };
	std::vector<Unit>* GetAllUnits() { return &_units; };

	bool CheckButtonClick(sf::Vector2f mousePos, bool mouseIsPoint);
};

#endif