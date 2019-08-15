#include "Grid.h"

void Grid::Draw(sf::RenderWindow &Window)
{
	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			_sprite.setPosition(_tiles[i][j]->GetPosition());

			switch (_tiles[i][j]->GetIndex())
			{
			default:
			case 0: //dirt
				_sprite.setTextureRect(sf::IntRect(0, 0, 64, 32));
				break;
			case 1: //road
				_tiles[i][j]->CalculateRoadValue();
				switch (_tiles[i][j]->GetRoadValue())
				{
				case 0:
					_sprite.setTextureRect(sf::IntRect(0, 32, 64, 32));
					break;
				case 1:
					_sprite.setTextureRect(sf::IntRect(64, 32, 64, 32));
					break;
				case 2:
					_sprite.setTextureRect(sf::IntRect(128, 32, 64, 32));
					break;
				case 3:
					_sprite.setTextureRect(sf::IntRect(192, 32, 64, 32));
					break;
				case 4:
					_sprite.setTextureRect(sf::IntRect(0, 64, 64, 32));
					break;
				case 5:
					_sprite.setTextureRect(sf::IntRect(64, 64, 64, 32));
					break;
				case 6:
					_sprite.setTextureRect(sf::IntRect(128, 64, 64, 32));
					break;
				case 7:
					_sprite.setTextureRect(sf::IntRect(192, 64, 64, 32));
					break;
				case 8:
					_sprite.setTextureRect(sf::IntRect(0, 96, 64, 32));
					break;
				case 9:
					_sprite.setTextureRect(sf::IntRect(64, 96, 64, 32));
					break;
				case 10:
					_sprite.setTextureRect(sf::IntRect(128, 96, 64, 32));
					break;
				case 11:
					_sprite.setTextureRect(sf::IntRect(192, 96, 64, 32));
					break;
				case 12:
					_sprite.setTextureRect(sf::IntRect(0, 128, 64, 32));
					break;
				case 13:
					_sprite.setTextureRect(sf::IntRect(64, 128, 64, 32));
					break;
				case 14:
					_sprite.setTextureRect(sf::IntRect(128, 128, 64, 32));
					break;
				case 15:
					_sprite.setTextureRect(sf::IntRect(192, 128, 64, 32));
					break;
				default:
					_sprite.setTextureRect(sf::IntRect(0, 0, 64, 32));
					break;
				}
				break;
			case 2: //red
				_sprite.setTextureRect(sf::IntRect(64, 0, 64, 32));
				break;
			case 3: //blue
				_sprite.setTextureRect(sf::IntRect(128, 0, 64, 32));
				break;
			case 4: //green
				_sprite.setTextureRect(sf::IntRect(192, 0, 64, 32));
				break;
			}

			Window.draw(_sprite);
		}
	}
}

Tile* Grid::GetTile(sf::Vector2f Position)
{ 
	Position = _utility.GridToWorld(_utility.WorldToGrid(Position));
	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			if(_tiles[i][j]->GetPosition() == Position)
				return _tiles[i][j];
		}
	}
	return NULL;
}

std::vector<Tile*> Grid::IsoGetTiles(sf::RectangleShape rect)
{
	std::vector<Tile*> selected;
	rect.setPosition(_utility.WorldToGrid(rect.getPosition()));
	rect.setSize(_utility.WorldToGrid(rect.getSize()));

	int minX = std::min(rect.getPosition().x, rect.getPosition().x - rect.getSize().x);
	int minY = std::min(rect.getPosition().y, rect.getPosition().y - rect.getSize().y);
	int maxX = std::max(rect.getPosition().x, rect.getPosition().x - rect.getSize().x);
	int maxY = std::max(rect.getPosition().y, rect.getPosition().y - rect.getSize().y);

	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int j = 0; j < _tiles[i].size(); j++)
		{
			if (i >= minX && i <= maxX)
				if (j >= minY && j <= maxY)
					selected.push_back(_tiles[i][j]);
		}
	}
	return selected;
}

std::vector<sf::Vector2f> Grid::IsoGetTileCorners(sf::RectangleShape rect)
{
	std::vector<Tile*> tiles = IsoGetTiles(rect);
	std::vector<sf::Vector2f> output;

	sf::Vector2f left = tiles.front()->GetPosition();
	sf::Vector2f top = tiles.front()->GetPosition();
	sf::Vector2f right = tiles.front()->GetPosition();
	sf::Vector2f bottom = tiles.front()->GetPosition();

	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i]->GetPosition().x < left.x)
			left = tiles[i]->GetPosition();

		if (tiles[i]->GetPosition().y < top.y)
			top = tiles[i]->GetPosition();

		if (tiles[i]->GetPosition().x > right.x)
			right = tiles[i]->GetPosition();

		if (tiles[i]->GetPosition().y > bottom.y)
			bottom = tiles[i]->GetPosition();
	}

	output.push_back(sf::Vector2f(left.x - (TILEX * 0.5), left.y));
	output.push_back(sf::Vector2f(top.x, top.y - (TILEY * 0.5)));
	output.push_back(sf::Vector2f(right.x + (TILEX * 0.5), right.y));
	output.push_back(sf::Vector2f(bottom.x, bottom.y + (TILEY * 0.5)));

	return output;
}

Grid::Grid(sf::Vector2f GridSize)
{
	_gridSize = GridSize;
	_utility = Utility();
	_utility.setGridSize(sf::Vector2f(TILEX, TILEY));
	_texture.loadFromFile("images/deserttileset.png");
	_sprite.setTexture(_texture, true);
	_sprite.setOrigin(TILEX / 2, TILEY / 2);

	srand(time(NULL));
	_tiles = std::vector<std::vector<Tile*>>();

	for (int i = 0; i < GridSize.x; i++)
	{
		std::vector<Tile*> column = std::vector<Tile*>();
		for(int j = 0; j < GridSize.y; j++)
		{
			int k = rand() % 2;

			Tile* tile = new Tile(k, _utility.GridToWorld(sf::Vector2f(i, j))); //sf::Vector2f(((i * 0.5) * TILEX) + (TILEX * 0.5 * j), ((j * 0.5) * TILEY) - (TILEY * 0.5 * i)));

			//Set East-West Connections
			if (i <= 0)
				tile->AddConnection(tile, West);
			else if (i > 0)
			{
				tile->AddConnection(_tiles[i-1][j], West);

				_tiles[i - 1][j]->AddConnection(tile, East);
			}
			
			if (i == GridSize.x - 1)
				tile->AddConnection(tile, East);

			//Set North-South Connections
			if (j <= 0)
				tile->AddConnection(tile, North);
			if (j > 0)
			{
				tile->AddConnection(column[j - 1], North);

				column[j - 1]->AddConnection(tile, South);
			}

			if (j == GridSize.y - 1)
				tile->AddConnection(tile, South);
				
			column.push_back(tile);
		}

		_tiles.push_back(column);
	}
}

Grid::Grid()
{
}


Grid::~Grid()
{
}
