#ifndef _ASSETLOADER_H
#define _ASSETLOADER_H

#include "Option.h"
#include "OptionSet.h"
#include "Toolbar.h"
#include "ToolbarUtility.h"
#include "Building.h"

class AssetLoader
{
private:
	Utility* utility;
	std::map <std::string, Toolbar*>* toolBarMap;
	Toolbar* CreateToolbar(std::string name);
public:
	ToolbarUtility* util;
	std::map <std::string, Toolbar*>* CreateToolbars();
	std::map <std::string, Building*>* CreateBuildingPatterns();
	std::map <std::string, Unit*>* CreateUnitPatterns();
	AssetLoader();
	AssetLoader(ToolbarUtility *_toolbarUtility);
	~AssetLoader();
};

#endif