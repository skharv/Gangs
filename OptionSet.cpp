#include "OptionSet.h"

OptionSet::OptionSet()
{
	options = std::vector<Option*>();
}

OptionSet::OptionSet(ToolbarUtility* util)
{
	toolbarUtil = util;
	options = std::vector<Option*>();
}

Option* OptionSet::AddOption()
{
	Option* o = new Option(toolbarUtil);
	options.push_back(o);
	return o;
}