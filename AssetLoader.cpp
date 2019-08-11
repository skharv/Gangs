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


std::map <std::string, Toolbar*>* AssetLoader::CreateToolbars()
{
	std::map <std::string, Toolbar*>* toolBarMap = new std::map <std::string, Toolbar*>();
	//main UI options
	std::vector<Option*> EditorUI_Options;
	sf::Vector2i size = sf::Vector2i(0, 0);
	EditorUI_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"BasicEditor", "BasicEditor"}, "HideToolbar", std::vector<std::string>{"BasicEditor"}, sf::Vector2f(0,0), size, sf::Color::White, sf::Keyboard::E));

	Toolbar* EditorUI = new Toolbar(sf::Vector2f(0, 0), sf::Vector2i(0, 0), sf::Color::White);
	EditorUI->AddOptionSet("EditorUI", EditorUI_Options);
	EditorUI->ShowToolbar("EditorUI");
	toolBarMap->insert(std::pair<std::string, Toolbar*>("EditorUI", EditorUI));


	//basic editor toolbar
	std::vector<Option*> basicEditor_Options;
	size = sf::Vector2i(30, 30);
	int x = 5;
	int y = 5;
	//Residential button
	basicEditor_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "Residential"}, "HideToolbar", std::vector<std::string>{"ExtendedEditor"}, sf::Vector2f(x,y), size, sf::Color::Red, sf::Keyboard::Num1));
	//GenericBusiness button
	basicEditor_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "GenericBusiness"}, "HideToolbar", std::vector<std::string>{"ExtendedEditor"}, sf::Vector2f(x+35, y), size, sf::Color::Blue, sf::Keyboard::Num2));
	//KeyBusiness button
	basicEditor_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "KeyBusiness"}, "HideToolbar", std::vector<std::string>{"ExtendedEditor"}, sf::Vector2f(x, y + 35), size, sf::Color::Cyan, sf::Keyboard::Num3));
	//Market button
	basicEditor_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "Market"}, "HideToolbar", std::vector<std::string>{"ExtendedEditor"}, sf::Vector2f(x + 35, y + 35), size, sf::Color::Green, sf::Keyboard::Num4));
	//Misc button
	basicEditor_Options.push_back(new Option(util, "TriggerToolbar", std::vector<std::string>{"ExtendedEditor", "Misc"}, "HideToolbar", std::vector<std::string>{"ExtendedEditor"}, sf::Vector2f(x, y + 70), size, sf::Color::Yellow, sf::Keyboard::Num5));
	
	Toolbar* basicEditor = new Toolbar(sf::Vector2f(0,0), sf::Vector2i(75,110),sf::Color::White);
	basicEditor->AddOptionSet("BasicEditor", basicEditor_Options);
	toolBarMap->insert(std::pair<std::string, Toolbar*>("BasicEditor", basicEditor));


	//Residential toolbar
	std::vector<Option*> residential_Options;
	size = sf::Vector2i(30, 30);
	sf::Vector2f pos = sf::Vector2f(5, 105);
	//Residential button
	residential_Options.push_back(new Option(util, "SetMouseState", std::vector<std::string>{"ZONE_RESIDENTIAL"}, pos, size, sf::Color::Red, sf::Keyboard::Numpad1));

	//GenericBusiness toolbar
	std::vector<Option*> genericBusiness_Options;
	//GenericBusiness button
	genericBusiness_Options.push_back(new Option(util, "SetMouseState", std::vector<std::string>{"ZONE_GENERICBUSINESS"}, pos, size, sf::Color::Blue, sf::Keyboard::Numpad1));

	//KeyBusiness toolbar
	std::vector<Option*> keyBusiness_Options;
	//KeyBusiness button
	keyBusiness_Options.push_back(new Option(util, "SetMouseState", std::vector<std::string>{"ZONE_KEYBUSINESS"}, pos, size, sf::Color::Cyan, sf::Keyboard::Numpad1));

	//Market toolbar
	std::vector<Option*> market_Options;
	//Market button
	market_Options.push_back(new Option(util, "SetMouseState", std::vector<std::string>{"ZONE_MARKET"}, pos, size, sf::Color::Green, sf::Keyboard::Numpad1));

	//Misc toolbar
	std::vector<Option*> misc_Options;
	//Misc button
	misc_Options.push_back(new Option(util, "SetMouseState", std::vector<std::string>{"ZONE_MISC"}, pos, size, sf::Color::Yellow, sf::Keyboard::Numpad1));

	Toolbar* extendedEditor = new Toolbar(sf::Vector2f(0, 100), sf::Vector2i(300, 100), sf::Color::White);
	extendedEditor->AddOptionSet("Residential", residential_Options);
	extendedEditor->AddOptionSet("GenericBusiness", genericBusiness_Options);
	extendedEditor->AddOptionSet("KeyBusiness", keyBusiness_Options);
	extendedEditor->AddOptionSet("Market", market_Options);
	extendedEditor->AddOptionSet("Misc", misc_Options);
	toolBarMap->insert(std::pair<std::string, Toolbar*>("ExtendedEditor", extendedEditor));

	return toolBarMap;
}