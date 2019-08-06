#ifndef _TOOLBARUTILITY_H
#define _TOOLBARUTILITY_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Toolbar.h"

class Toolbar;
class Option;

class ToolbarUtility
{
private:
	std::vector <std::vector<Option*>> _activeOptions;
	std::map <std::string, Toolbar*>* _toolbars;
	void TriggerToolbar(Toolbar* t, std::string options);
	void HideToolbar(Toolbar* t);
public:
	ToolbarUtility() {};
	void SetToolbarReferences(std::map <std::string, Toolbar*>* teaSet);
	void ButtonAction(std::string function, std::vector<std::string> params);
	std::vector <std::vector<Option*>>* GetActiveOptions() { return &_activeOptions; }
};

#endif