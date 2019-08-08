#ifndef _ASSETLOADER_H
#define _ASSETLOADER_H

#include "Option.h"
#include "Toolbar.h"
#include "ToolbarUtility.h"

class AssetLoader
{
private:
public:
	ToolbarUtility* util;
	std::map <std::string, Toolbar*>* CreateToolbars();
	AssetLoader();
	AssetLoader(ToolbarUtility *_toolbarUtility);
	~AssetLoader();
};

#endif