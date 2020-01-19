#ifndef _ENGINE_H
#define _ENGINE_H

#include <SFML\Graphics.hpp>


#include "Unit.h"
#include "Camera.h"
#include "Grid.h"
#include "Utility.h"
#include "Mouse.h"
#include "AssetLoader.h"
#include "ToolbarUtility.h"

class Engine
{
private:
	sf::RenderWindow *_window;
	
	Camera *_camera;

	Grid *_grid;
	//Grid *_squareGrid;
	
	Mouse *_mouse;

	Utility *_utility;

	AssetLoader *_assetLoader;

	ToolbarUtility *_toolbarUtility;

	bool Init();
	void MainLoop();
	void ProcessInput();
	void RenderFrame();
	void Update();
public:
	Engine() {};
	~Engine() {};

	void Go();
};

#endif