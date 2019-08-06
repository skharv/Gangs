#include "Engine.h"

bool Engine::Init()
{
	// Set up the window
	_window = new sf::RenderWindow(sf::VideoMode(1200, 768), "Gangs");
	_window->setVerticalSyncEnabled(true);

	// Set up the camera for viewing with
	_camera = new Camera(sf::Vector2f(1200, 768));
	_camera->SetMoveSpeed(20);

	// Set the grid with a set size
	_grid = new Grid(sf::Vector2f(100, 100));

	// Set the mouse with it's image
	_mouse = new Mouse("images/gridsection.png");

	// Set up the utility class (which should probably be static instead)
	_utility = new Utility();
	_utility->setGridSize(_grid->GetSize());

	_toolbarUtility = new ToolbarUtility();

	_assetLoader = new AssetLoader(_toolbarUtility);
	_assetLoader->CreateToolbars();

	//teaSet?

	if (!_window)
		return false;

	return true;
}

void Engine::MainLoop()
{
	while (_window->isOpen())
	{
		ProcessInput();

		Update();

		RenderFrame();
	}
}

void Engine::ProcessInput()
{
	sf::Event evt;

	while (_window->pollEvent(evt))
	{
		// How to close the game
		if (evt.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_window->close();

		// Camera movement (it's a bit shit atm)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			_camera->AddToMoveDirection(0, 1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			_camera->AddToMoveDirection(0, -1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			_camera->AddToMoveDirection(-1, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			_camera->AddToMoveDirection(1, 0);

		//Edit mode
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			_camera->AddToMoveDirection(1, 0);
		 
		//mouse click
		_mouse->Click("",_toolbarUtility->GetActiveOptions());
	}
}

void Engine::Update()
{
	_camera->Update(*_window);

	/* The mouse pos.
		To set the mouse "cursor" to land directly on a tile space
		you get the position of the mouse relative to the window,
		then you convert the world position of the mouse into the grid coords.
		After that you convert them BACK to world coords. This snaps the cursor
		to the specific tile. 

		This should probs go in the mouse class.
	*/
	sf::Vector2f mousePos = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
	mousePos = _utility->WorldToGrid(mousePos);
	mousePos = _utility->GridToWorld(mousePos);
	_mouse->Update(mousePos);
}

void Engine::RenderFrame()
{
	_window->clear(sf::Color(186, 158, 111, 255));
	_grid->Draw(*_window);
	_mouse->Draw(*_window);
	_window->display();
}

void Engine::Go()
{
	if (!Init())
		throw "Could not initialise Engine";

	MainLoop();
}
