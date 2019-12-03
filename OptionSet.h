#ifndef _OPTIONSET_H
#define _OPTIONSET_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Option.h"

class Option;
class ToolbarUtility;

class OptionSet
{
private:
	ToolbarUtility* toolbarUtil;
public:
	std::vector<Option*> options;

	Option* AddOption();
	OptionSet();
	OptionSet(ToolbarUtility* util);
	~OptionSet();
};

#endif