#ifndef _TOOLBARUTILITY_H
#define _TOOLBARUTILITY_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Toolbar.h"
#include "Mouse.h"
#include "Grid.h"
class Toolbar;
class Option;
class Mouse;

class ToolbarUtility
{
private:
	std::map <std::string, Toolbar*>* _toolbars;
	void TriggerToolbar(Toolbar* t, std::string options);
	void HideToolbar(Toolbar* t);
	void SetMouseState(std::string state);
	Mouse* _mouse;
	Grid* _grid;
public:
	ToolbarUtility() {};
	ToolbarUtility(Grid* grid) { _grid = grid; };
	void SetMouseReference(Mouse* mouse) { _mouse = mouse; };
	void SetToolbarReferences(std::map <std::string, Toolbar*>* teaSet);
	void ButtonAction(std::string function, std::vector<std::string> params);
	void Draw(sf::RenderWindow &Window);
	void Update(sf::Vector2f camPos);
	void CheckShortCutKeys();
	bool CheckButtonClick(sf::Vector2f mousePos);
};

#endif