#ifndef _ENGINE_H
#define _ENGINE_H

#include <SFML\Graphics.hpp>


#include "Camera.h"
#include "Grid.h"
#include "Utility.h"
#include "Mouse.h"

class Engine
{
private:
	sf::RenderWindow *_window;
	
	Camera *_camera;

	Grid *_grid;

	Mouse *_mouse;

	Utility *_utility;

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