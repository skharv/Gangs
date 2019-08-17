#ifndef _ASSETLOADER_H
#define _ASSETLOADER_H

#include "Option.h"
#include "Toolbar.h"
#include "ToolbarUtility.h"
#include "Building.h"

class AssetLoader
{
private:
public:
	ToolbarUtility* util;
	std::map <std::string, Toolbar*>* CreateToolbars();
	std::map <std::string, Building*>* CreateBuildingPatterns();
	AssetLoader();
	AssetLoader(ToolbarUtility *_toolbarUtility);
	~AssetLoader();
};

#endif