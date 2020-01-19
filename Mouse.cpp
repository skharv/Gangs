#include "Mouse.h"

/* The mouse pos.
		To set the mouse "cursor" to land directly on a tile space
		you get the position of the mouse relative to the window,
		then you convert the world position of the mouse into the grid coords.
		After that you convert them BACK to world coords. This snaps the cursor
		to the specific tile.
*/
void Mouse::Update(sf::RenderWindow* Window)
{
	sf::Vector2f mousePos = Window->mapPixelToCoords(sf::Mouse::getPosition(*Window));

	_position = mousePos;
	_position = _utility->IsoGridToWorld(_utility->IsoWorldToGrid(mousePos, _utility->getGridTileSize()), _utility->getGridTileSize());

	if (_mousePressed && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)))
		Click(*Window);
	else if (_mousePressed)
	{
		_mouseSelect.setSize(sf::Vector2f(_mouseSelect.getPosition().x - mousePos.x, _mouseSelect.getPosition().y - mousePos.y));

		std::vector<sf::Vector2f> points = _grid->IsoGetTileCorners(_mouseSelect); //Using _mouseSelect is not super accurate for this purpose so it'll need to be updated, but whatever. It could be the iso tile bullshit not being accurate too. 
		_tileSelect.setPointCount(points.size()); // Probably not needed
		for (int i = 0; i < _tileSelect.getPointCount(); i++)
			_tileSelect.setPoint(i, points[i]);
	}
	else
	{
		_tileSelect.setPoint(0, sf::Vector2f(_position.x - (_grid->GetTileSize().x * 0.5), _position.y));
		_tileSelect.setPoint(1, sf::Vector2f(_position.x, _position.y - (_grid->GetTileSize().y * 0.5)));
		_tileSelect.setPoint(2, sf::Vector2f(_position.x + (_grid->GetTileSize().x * 0.5), _position.y));
		_tileSelect.setPoint(3, sf::Vector2f(_position.x, _position.y + (_grid->GetTileSize().y * 0.5)));
	}

	if (_mouseMovePressed)
	{
		std::cout << "CAMERA POS: " << _camera->GetPosition().x << " " << _camera->GetPosition().y << std::endl;
		std::cout << "MOUSE POS: " << mousePos.x << " " << mousePos.y << std::endl;
		_camera->SetPosition(sf::Vector2f(_camera->GetPosition() + (_mouseMoveStart - mousePos)));
	}
	if (_mouseState.substr(0, 5) == "BUILD")
		_activeBuilding->PlacementUpdate(_grid->GetTile(mousePos));
	if (_mouseState.substr(0, 6) == "CREATE")
		_activeUnit->PlacementUpdate(_grid->GetTile(mousePos));
	//_pointerSprite.setPosition(_position);
}

void Mouse::DrawUnder(sf::RenderWindow &Window)
{	
	//if (_mousePressed)
	//	Window.draw(_mouseSelect);
	//else
	if (_utility->getGameState() == Util::GameState::Editor)
		Window.draw(_tileSelect);
	else
		Window.draw(_mouseSelect);
	if (_mouseState.substr(0, 5) == "BUILD")
		_activeBuilding->Draw(Window);
	if (_mouseState.substr(0, 6) == "CREATE")
		_activeUnit->Draw(Window);

}

void Mouse::MouseMoveDown(sf::RenderWindow & Window)
{
	_mouseMoveStart = Window.mapPixelToCoords(sf::Mouse::getPosition(Window));
	_mouseMovePressed = true;
}

void Mouse::MouseMoveUp()
{
	_mouseMovePressed = false;
}

void Mouse::DrawOver(sf::RenderWindow &Window)
{
	//Window.draw(_pointerSprite);
}

void Mouse::MouseDown(sf::RenderWindow& Window)
{
	_mouseStart = Window.mapPixelToCoords(sf::Mouse::getPosition(Window));
	_mouseSelect.setPosition(_mouseStart);
	_mousePressed = true;
}

void Mouse::MouseUp()
{
	_mousePressed = false;
}

void Mouse::RightClick(sf::RenderWindow& Window)
{
	if(_utility->getGameState() == Util::GameState::Editor)
		ClearMouse();
	else
		MoveUnits(Window.mapPixelToCoords(sf::Mouse::getPosition(Window)));
}

void Mouse::Click(sf::RenderWindow& Window)
{
	sf::Vector2f mousePos = Window.mapPixelToCoords(sf::Mouse::getPosition(Window));
	_camera->setUIView(Window);
	sf::Vector2f uiMousePos = Window.mapPixelToCoords(sf::Mouse::getPosition(Window));
	_camera->setGridView(Window);

	bool mouseIsPoint = false;

	if ((_mouseSelect.getSize().x < 5 && _mouseSelect.getSize().x > -5) && (_mouseSelect.getSize().y < 5 && _mouseSelect.getSize().y > -5))
		mouseIsPoint = true;


	if (!_toolbarUtility->CheckButtonClick(uiMousePos, mouseIsPoint))
	{
		if (_utility->getGameState() == Util::GameState::Editor)
			EditModeMouse(mouseIsPoint, mousePos, _mouseSelect);
		else
			GameModeMouse(mouseIsPoint, mousePos, _mouseSelect);
	}

	_mouseSelect.setSize(sf::Vector2f(0, 0));
}

void Mouse::SetBuildingPatterns(std::map<std::string, Building*>* b)
{
	_buildingPatterns = b;
}

void Mouse::SetUnitPatterns(std::map<std::string, Unit*>* u)
{
	_unitPatterns = u;
}

void Mouse::EditModeMouse(bool mouseIsPoint, sf::Vector2f mousePos, sf::RectangleShape shape)
{
	std::vector<Tile*> t;
	if (mouseIsPoint)
		t.push_back(_grid->GetTile(mousePos));
	else
		t = _grid->IsoGetTiles(shape);
	if (!t.empty())
	{
		if (_mouseState.substr(0, 4) == "ZONE")
			Zone(_mouseState.substr(5, _mouseState.length()), t);
		if (_mouseState.substr(0, 5) == "BUILD")
		{
			if (_activeBuilding->ValidPlacement())
			{
				_toolbarUtility->AddBuilding(*_activeBuilding);
			}
		}
		if (_mouseState.substr(0, 6) == "CREATE")
		{
			if (_activeUnit->ValidPlacement())
			{
				_toolbarUtility->AddUnit(*_activeUnit);
			}
		}
	}
}

void Mouse::GameModeMouse(bool mouseIsPoint, sf::Vector2f mousePos, sf::RectangleShape shape)
{
	_selectedUnits.clear();
	for (int x = 0; x < _toolbarUtility->GetAllUnits()->size(); x++)
	{
		if (mouseIsPoint)
		{
			if (_utility->RectPoint(_utility->ConvertToRectShape(_toolbarUtility->GetAllUnits()->at(x).GetSprite()), mousePos))
				_selectedUnits.push_back(&_toolbarUtility->GetAllUnits()->at(x));
		}
		else
		{
			if (_utility->RectRect(shape, _utility->ConvertToRectShape(_toolbarUtility->GetAllUnits()->at(x).GetSprite())))
			{
				_selectedUnits.push_back(&_toolbarUtility->GetAllUnits()->at(x));
				if (mouseIsPoint)
					break;
			}
		}
	}
	//then check buildings and 
}

void Mouse::MoveUnits(sf::Vector2f pos)
{
	for (int x = 0; x < _selectedUnits.size(); x++)
	{
		_selectedUnits.at(x)->Move(*_grid, pos, true);
	}
}

std::string Mouse::GetKeyString(std::string s){
	return _mouseState.substr(0, _mouseState.find_first_of('_'));
}

void Mouse::ClearMouse()
{
	if(_activeBuilding != NULL)
		_activeBuilding->CancelPlacement();
	if (_activeUnit != NULL)
		_activeUnit->CancelPlacement();
	_mouseState = "";
	_activeBuilding = NULL;
	_activeUnit - NULL;
}

void Mouse::SetMouseState(std::string state)
{
	_mouseState = state;
	if (_mouseState.substr(0, 5) == "BUILD")
		Build(_mouseState.substr(6, _mouseState.length()));
	if (_mouseState.substr(0, 6) == "CREATE")
		Create(_mouseState.substr(7, _mouseState.length()));
}

void Mouse::Zone(std::string s, std::vector<Tile*> t)
{

	int index = GetSocialClassCode(s);
	for (int x = 0; x < t.size(); x++)
	{
		if(t.at(x) != NULL)
			t.at(x)->SetIndex(index);
	}
}

int Mouse::GetSocialClassCode(std::string s)
{
	if (s == "LOWINCOME")
		return 2;
	if (s == "MEDIUMINCOME")
		return 3;
	if (s == "HIGHINCOME")
		return 4;
}

void Mouse::SetTileIndex(std::string s, std::vector<Tile*> t)
{
	int index = GetTileCode(s);
	for (int x = 0; x < t.size(); x++)
	{
		if (t.at(x) != NULL)
			t.at(x)->SetIndex(index);
	}
}

void Mouse::Create(std::string s)
{
	_activeUnit = _unitPatterns->at(s);
}

void Mouse::Build(std::string s)
{
	_activeBuilding = _buildingPatterns->at(s);
}

int Mouse::GetTileCode(std::string s)
{
	if (s == "DIRT")
		return 0;
	if (s == "ROAD")
		return 1;
}

Mouse::Mouse(Utility* utility, ToolbarUtility* toolbarUtil, Grid* grid, Camera* camera)
{
	_toolbarUtility = toolbarUtil;
	_utility = utility;
	_activeBuilding = NULL;
	_activeUnit = NULL;
	//_texture.loadFromFile(FilePath);
	//_pointerSprite.setTexture(_texture);
	//_pointerSprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y / 2);
	//_pointerSprite.setColor(sf::Color::Green);
	
	_tileSelect.setOutlineThickness(1);
	_tileSelect.setOutlineColor(sf::Color().Green);
	_tileSelect.setFillColor(sf::Color().Transparent);
	_tileSelect.setPointCount(4);
	_tileSelect.setPoint(0, sf::Vector2f(0, 0));
	_tileSelect.setPoint(1, sf::Vector2f(0, 0));
	_tileSelect.setPoint(2, sf::Vector2f(0, 0));
	_tileSelect.setPoint(3, sf::Vector2f(0, 0));

	_position = sf::Vector2f(0, 0);
	_grid = grid;
	_camera = camera;
	_mousePressed = false;
	_mouseSelect.setOutlineThickness(1);
	_mouseSelect.setOutlineColor(sf::Color().Green);
	_mouseSelect.setFillColor(sf::Color().Transparent);
	_mouseSelect.setRotation(180);
}


Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}
