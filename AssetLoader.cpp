#include "AssetLoader.h"

AssetLoader::AssetLoader()
{
}

AssetLoader::AssetLoader(ToolbarUtility *_toolbarUtility)
{
	util = _toolbarUtility;
}

AssetLoader::~AssetLoader()
{
}


std::map <std::string, Toolbar*> AssetLoader::CreateToolbars()
{
	std::map <std::string, Toolbar*> toolBarMap;


	//basic editor toolbar
	std::vector<Option*> basicEditor_Options;
	//Residential button
	basicEditor_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "Residential"}, "HideToolbar", std::vector<std::string>{"ExtendedEditor"}));
	//GenericBusiness button
	basicEditor_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "GenericBusiness"}, "HideToolbar", std::vector<std::string>{"ExtendedEditor"}));
	//KeyBusiness button
	basicEditor_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "KeyBusiness"}, "HideToolbar", std::vector<std::string>{"ExtendedEditor"}));
	//Market button
	basicEditor_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "Market"}, "HideToolbar", std::vector<std::string>{"ExtendedEditor"}));
	//Misc button
	basicEditor_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "Misc"}, "HideToolbar", std::vector<std::string>{"ExtendedEditor"}));
	
	Toolbar* basicEditor = new Toolbar();
	basicEditor->AddOptionSet("BasicEditor", basicEditor_Options);
	toolBarMap.insert(std::pair<std::string, Toolbar*>("BasicEditor", basicEditor));


	//Residential toolbar
	std::vector<Option*> residential_Options;
	//Residential button
	residential_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "Residential"}));

	//GenericBusiness toolbar
	std::vector<Option*> genericBusiness_Options;
	//GenericBusiness button
	residential_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "Residential"}));

	//KeyBusiness toolbar
	std::vector<Option*> keyBusiness_Options;
	//KeyBusiness button
	residential_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "Residential"}));

	//Market toolbar
	std::vector<Option*> market_Options;
	//Market button
	residential_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "Residential"}));

	//Misc toolbar
	std::vector<Option*> misc_Options;
	//Misc button
	residential_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "Residential"}));

	Toolbar* extendedEditor = new Toolbar();
	extendedEditor->AddOptionSet("Residential", residential_Options);
	extendedEditor->AddOptionSet("GenericBusiness", genericBusiness_Options);
	extendedEditor->AddOptionSet("KeyBusiness", keyBusiness_Options);
	extendedEditor->AddOptionSet("Market", market_Options);
	extendedEditor->AddOptionSet("Misc", misc_Options);
	toolBarMap.insert(std::pair<std::string, Toolbar*>("ExtendedEditor", extendedEditor));

	return toolBarMap;
}