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
	_grid = new Grid(gr::ISOMETRIC, sf::Vector2f(100, 100), sf::Vector2f(64, 32));
	//_squareGrid = new Grid(gr::SQUARE, sf::Vector2f(400, 200), sf::Vector2f(16, 16));

	// Set up the utility class (which should probably be static instead)
	_utility = new Utility();
	_utility->setGridSize(_grid->GetSize());

	// Set the mouse with it's image
	_toolbarUtility = new ToolbarUtility(_grid, _utility);
	_mouse = new Mouse(_utility,_toolbarUtility, _grid, _camera);

	_toolbarUtility->SetMouseReference(_mouse);

	_assetLoader = new AssetLoader(_toolbarUtility);
	_toolbarUtility->SetToolbarReferences(_assetLoader->CreateToolbars());
	_mouse->SetBuildingPatterns(_assetLoader->CreateBuildingPatterns());

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

		if (evt.type == sf::Event::KeyPressed)
		{
			_toolbarUtility->CheckShortCutKeys();
		}
		if (evt.type == sf::Event::MouseWheelMoved)
		{
			if(evt.mouseWheel.delta >= 1)
				_camera->SetZoom(0.9);
			if (evt.mouseWheel.delta <= 0)
				_camera->SetZoom(1.1);
		}
		if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left)
		{
			_mouse->MouseUp();
			_mouse->Click(*_window);
		}
		if (evt.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			_mouse->MouseDown(*_window);
		}

		if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Right)
		{
			_mouse->ClearMouse();
		}

		if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Middle)
			_mouse->MouseMoveUp();
		if (evt.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			_mouse->MouseMoveDown(*_window);
	}
}

void Engine::Update()
{
	_camera->Update(*_window);
	_toolbarUtility->Update(_camera->GetPosition());
	_mouse->Update(_window);
	//update UI positions based on camera
}

void Engine::RenderFrame()
{
	_window->clear(sf::Color(186, 158, 111, 255));

	_camera->setGridView(*_window);
	_grid->Draw(*_window);
	//_squareGrid->Draw(*_window);
	_toolbarUtility->DrawMap(*_window);
	_mouse->DrawUnder(*_window);

	_camera->setUIView(*_window);
	_toolbarUtility->DrawUI(*_window);
	//UI Mouse
	//_mouse->DrawOver(*_window);
	_camera->setGridView(*_window);

	_window->display();
}

void Engine::Go()
{
	if (!Init())
		throw "Could not initialise Engine";

	MainLoop();
}
