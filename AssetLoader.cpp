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

std::map <std::string, Unit*>* AssetLoader::CreateUnitPatterns()
{
	std::map <std::string, Unit*>* unitPatterns = new std::map <std::string, Unit*>();

	Unit* u = new Unit("images/basicUnit.png", sf::Vector2f(16, 32));
	unitPatterns->insert(std::pair<std::string, Unit*>("BASIC", u));

	u = new Unit("images/agileUnit.png", sf::Vector2f(16, 32));
	u->SetMoveSpeed(4);
	u->SetSteerSpeed(7);
	unitPatterns->insert(std::pair<std::string, Unit*>("AGILE", u));

	return unitPatterns;
}

std::map <std::string, Building*>* AssetLoader::CreateBuildingPatterns()
{
	std::map <std::string, Building*>* buildingPatterns = new std::map <std::string, Building*>();

	Building* b = new Building("basicBuilding.png");
	b->SetFootprint(std::vector<Util::Direction>{Util::North, Util::West, Util::South, Util::South, Util::East, Util::East, Util::North, Util::North});
	b->SetOrigin(sf::Vector2f(96, 48));
	buildingPatterns->insert(std::pair<std::string, Building*>("HOUSE",b));

	b = new Building("basicBuilding1.png");
	b->SetFootprint(std::vector<Util::Direction>{Util::North, Util::West, Util::South, Util::South, Util::East, Util::East, Util::North, Util::North});
	b->SetOrigin(sf::Vector2f(96, 48));
	buildingPatterns->insert(std::pair<std::string, Building*>("HOUSE1", b));

	b = new Building("basicBuilding2.png");
	b->SetFootprint(std::vector<Util::Direction>{Util::North, Util::West, Util::South, Util::South, Util::East, Util::East, Util::North, Util::North});
	b->SetOrigin(sf::Vector2f(96, 48));
	buildingPatterns->insert(std::pair<std::string, Building*>("HOUSE2", b));

	b = new Building("basicBuilding3.png");
	b->SetFootprint(std::vector<Util::Direction>{Util::East, Util::East, Util::East, Util::North, Util::West, Util::West, Util::West, Util::West, Util::South, Util::South, Util::East, Util::East});
	b->SetOrigin(sf::Vector2f(96, 48));
	buildingPatterns->insert(std::pair<std::string, Building*>("HOUSE3", b));


	return buildingPatterns;
}

Toolbar* AssetLoader::CreateToolbar(std::string name) {
	Toolbar *t = new Toolbar(utility);
	toolBarMap->insert(std::pair<std::string, Toolbar*>(name, t));
	return t;
}

std::map <std::string, Toolbar*>* AssetLoader::CreateToolbars()
{
	utility = new Utility();
	toolBarMap = new std::map <std::string, Toolbar*>();


	Toolbar* EditorUI = CreateToolbar("EditorUI");
	OptionSet* optionSet = EditorUI->AddOptionSet("EditorUI", util);

	optionSet->AddOption()
		->WithActiveFunction("ToggleEditor")
		->WithActiveParams(std::vector<std::string>{"BasicEditor", "BasicEditor"})
		->WithShortcut(sf::Keyboard::E)
		->WithInactiveFunction("ToggleEditor")
		->WithInactiveParams(std::vector<std::string>{"BasicEditor", "BasicEditor"});

	EditorUI->ShowToolbar("EditorUI");
	EditorUI->SetInvisible();

	Toolbar* basicEditor = CreateToolbar("BasicEditor")
		->WithPosition(sf::Vector2f(-585, 200))
		->WithSize(sf::Vector2i(75, 110))
		->WithImage("BasicEditor.png");
	
	sf::Vector2f pos = sf::Vector2f(-578, 209);
	optionSet = basicEditor->AddOptionSet("BasicEditor", util);
	optionSet->AddOption()
		->WithActiveFunction("TriggerToolbar")
		->WithActiveParams(std::vector<std::string>{"ExtendedEditor", "SocialClass"})
		->WithPoition(pos)
		->WithSize(sf::Vector2i(30, 30))
		->WithInactiveFunction("HideToolbar")
		->WithInactiveParams(std::vector<std::string>{"ExtendedEditor"})
		->WithActiveImage("redButton.png")
		->WithShortcut(sf::Keyboard::Num1);

	optionSet->AddOption()
		->WithActiveFunction("TriggerToolbar")
		->WithActiveParams(std::vector<std::string>{"ExtendedEditor", "Units"})
		->WithPoition(sf::Vector2f(pos.x + 32, pos.y))
		->WithSize(sf::Vector2i(30, 30))
		->WithInactiveFunction("HideToolbar")
		->WithInactiveParams(std::vector<std::string>{"ExtendedEditor"})
		->WithActiveImage("blueButton.png")
		->WithShortcut(sf::Keyboard::Num2);
	optionSet->AddOption()
		->WithActiveFunction("TriggerToolbar")
		->WithActiveParams(std::vector<std::string>{"ExtendedEditor", "KeyBusiness"})
		->WithPoition(sf::Vector2f(pos.x, pos.y + 32))
		->WithSize(sf::Vector2i(30, 30))
		->WithInactiveFunction("HideToolbar")
		->WithInactiveParams(std::vector<std::string>{"ExtendedEditor"})
		->WithActiveImage("cyanButton.png")
		->WithShortcut(sf::Keyboard::Num3);

	optionSet->AddOption()
		->WithActiveFunction("TriggerToolbar")
		->WithActiveParams(std::vector<std::string>{"ExtendedEditor", "Market"})
		->WithPoition(sf::Vector2f(pos.x + 32, pos.y + 32))
		->WithSize(sf::Vector2i(30, 30))
		->WithInactiveFunction("HideToolbar")
		->WithInactiveParams(std::vector<std::string>{"ExtendedEditor"})
		->WithActiveImage("greenButton.png")
		->WithShortcut(sf::Keyboard::Num4);
	optionSet->AddOption()
		->WithActiveFunction("TriggerToolbar")
		->WithActiveParams(std::vector<std::string>{"ExtendedEditor", "Terrain"})
		->WithPoition(sf::Vector2f(pos.x, pos.y + 64))
		->WithSize(sf::Vector2i(30, 30))
		->WithInactiveFunction("HideToolbar")
		->WithInactiveParams(std::vector<std::string>{"ExtendedEditor"})
		->WithActiveImage("yellowButton.png")
		->WithShortcut(sf::Keyboard::Num5);


	Toolbar* extendedEditor = CreateToolbar("ExtendedEditor")
		->WithPosition(sf::Vector2f(-585, 315))
		->WithSize(sf::Vector2i(300, 60))
		->WithImage("ExtendedEditor.png");

	pos = sf::Vector2f(-578, 321);
	optionSet = extendedEditor->AddOptionSet("SocialClass", util);
	optionSet->AddOption()
		->WithActiveFunction("SetMouseState")
		->WithActiveParams("ZONE_LOWINCOME")
		->WithPoition(pos)
		->WithSize(sf::Vector2i(48, 48))
		->WithActiveImage("redButton.png")
		->WithShortcut(sf::Keyboard::Numpad1);
	optionSet->AddOption()
		->WithActiveFunction("SetMouseState")
		->WithActiveParams("ZONE_MEDIUMINCOME")
		->WithPoition(sf::Vector2f(pos.x + 51, pos.y))
		->WithSize(sf::Vector2i(48, 48))
		->WithActiveImage("redButton.png")
		->WithShortcut(sf::Keyboard::Numpad2);
	optionSet->AddOption()
		->WithActiveFunction("SetMouseState")
		->WithActiveParams("ZONE_HIGHINCOME")
		->WithPoition(sf::Vector2f(pos.x + 102, pos.y))
		->WithSize(sf::Vector2i(48, 48))
		->WithActiveImage("redButton.png")
		->WithShortcut(sf::Keyboard::Numpad3);

	optionSet = extendedEditor->AddOptionSet("Units", util);
	optionSet->AddOption()
		->WithActiveFunction("SetMouseState")
		->WithActiveParams("CREATE_BASIC")
		->WithPoition(pos)
		->WithSize(sf::Vector2i(48, 48))
		->WithActiveImage("blueButton.png")
		->WithShortcut(sf::Keyboard::Numpad1);
	optionSet->AddOption()
		->WithActiveFunction("SetMouseState")
		->WithActiveParams("CREATE_AGILE")
		->WithPoition(sf::Vector2f(pos.x + 51, pos.y))
		->WithSize(sf::Vector2i(48, 48))
		->WithActiveImage("blueButton.png")
		->WithShortcut(sf::Keyboard::Numpad2);


	optionSet = extendedEditor->AddOptionSet("KeyBusiness", util);
	optionSet->AddOption()
		->WithActiveFunction("SetMouseState")
		->WithActiveParams("ZONE_KEYBUSINESS")
		->WithPoition(pos)
		->WithSize(sf::Vector2i(48, 48))
		->WithActiveImage("cyanButton.png")
		->WithShortcut(sf::Keyboard::Numpad1);

	optionSet = extendedEditor->AddOptionSet("Market", util);
	optionSet->AddOption()
		->WithActiveFunction("SetMouseState")
		->WithActiveParams("BUILD_HOUSE")
		->WithPoition(pos)
		->WithSize(sf::Vector2i(48, 48))
		->WithActiveImage("greenButton.png")
		->WithShortcut(sf::Keyboard::Numpad1)
		->WithInactiveFunction("ClearMouse")
		->WithInactiveParams("");
	optionSet->AddOption()
		->WithActiveFunction("SetMouseState")
		->WithActiveParams("BUILD_HOUSE1")
		->WithPoition(sf::Vector2f(pos.x + 51, pos.y))
		->WithSize(sf::Vector2i(48, 48))
		->WithActiveImage("greenButton.png")
		->WithShortcut(sf::Keyboard::Numpad2)
		->WithInactiveFunction("ClearMouse")
		->WithInactiveParams("");
	optionSet->AddOption()
		->WithActiveFunction("SetMouseState")
		->WithActiveParams("BUILD_HOUSE2")
		->WithPoition(sf::Vector2f(pos.x + 102, pos.y))
		->WithSize(sf::Vector2i(48, 48))
		->WithActiveImage("greenButton.png")
		->WithShortcut(sf::Keyboard::Numpad3)
		->WithInactiveFunction("ClearMouse")
		->WithInactiveParams("");
	optionSet->AddOption()
		->WithActiveFunction("SetMouseState")
		->WithActiveParams("BUILD_HOUSE3")
		->WithPoition(sf::Vector2f(pos.x + 153, pos.y))
		->WithSize(sf::Vector2i(48, 48))
		->WithActiveImage("greenButton.png")
		->WithShortcut(sf::Keyboard::Numpad4)
		->WithInactiveFunction("ClearMouse")
		->WithInactiveParams("");

	optionSet = extendedEditor->AddOptionSet("Terrain", util);
	optionSet->AddOption()
		->WithActiveFunction("SetMouseState")
		->WithActiveParams("ZONE_DIRT")
		->WithPoition(pos)
		->WithSize(sf::Vector2i(48, 48))
		->WithActiveImage("yellowButton.png")
		->WithShortcut(sf::Keyboard::Numpad1);
	optionSet->AddOption()
		->WithActiveFunction("SetMouseState")
		->WithActiveParams("ZONE_ROAD")
		->WithPoition(sf::Vector2f(pos.x + 51, pos.y))
		->WithSize(sf::Vector2i(48, 48))
		->WithActiveImage("yellowButton.png")
		->WithShortcut(sf::Keyboard::Numpad2);

	return toolBarMap;
}