#include "stdafx.h"
#include "Map.h"

void Map::initTileMap()
{
	int cols = this->mapWidth / this->tileSize; // 19 cols
	int rows = this->mapHeight / this->tileSize; // 10 rows

	for (int i = 0; i < rows; i++)
	{
		std::vector<sf::Sprite> sprites;
		for (int j = 0; j < cols; j++)
		{
			sf::Sprite sp;
			if (i == 0 && j == 0) //top left corner
			{
				sp = sf::Sprite(this->mapTexture, this->topLeftWall);
			}
			else if (i == rows - 1 && j == 0) //bottom left corner
			{
				sp = sf::Sprite(this->mapTexture, this->bottomLeftWall);
			}
			else if (i == 0 && j == cols - 1) //top right corner
			{
				sp = sf::Sprite(this->mapTexture, this->topRightWall);
			}
			else if (i == rows - 1 && j == cols - 1) //bottom right corner
			{
				sp = sf::Sprite(this->mapTexture, this->bottomRightWall);
			}
			else if (i == 0)
			{
				sp = sf::Sprite(this->mapTexture, this->wallTop[j % (this->wallTop.size() - 1)]);
			}
			else if (i == rows - 1)
			{
				sp = sf::Sprite(this->mapTexture, this->wallBottom[j % (this->wallBottom.size() - 1)]);
			}
			else if (j == 0)
			{
				sp = sf::Sprite(this->mapTexture, this->wallLeft);
			}
			else if (j == cols - 1)
			{
				sp = sf::Sprite(this->mapTexture, this->wallRight);
			}
			else
			{
				sp = sf::Sprite(this->mapTexture, this->floorLocations[j % (this->floorLocations.size() - 1)]);
			}
			sp.setPosition(j * this->tileSize, i * this->tileSize);
			sprites.push_back(sp);
		}
		this->tileMap.push_back(sprites);
	}
	for (int i = 1; i < 5; i++)
	{
		sf::Sprite sp = sf::Sprite(this->mapTexture, this->enemySpawnLocation);
		sp.setPosition((i + i) * this->tileSize, (i + 1 * i) * this->tileSize);
		this->bonesSprites.push_back(sp);
	}
}

void Map::initLocations()
{
	this->floorLocations.push_back(sf::IntRect(0, 100, this->tileSize, this->tileSize));
	this->floorLocations.push_back(sf::IntRect(100, 100, this->tileSize, this->tileSize));
	this->floorLocations.push_back(sf::IntRect(200, 100, this->tileSize, this->tileSize));
	this->floorLocations.push_back(sf::IntRect(300, 100, this->tileSize, this->tileSize));

	this->wallTop.push_back(sf::IntRect(0, 600, this->tileSize, this->tileSize));
	this->wallTop.push_back(sf::IntRect(100, 600, this->tileSize, this->tileSize));
	this->wallTop.push_back(sf::IntRect(200, 600, this->tileSize, this->tileSize));

	this->wallBottom.push_back(sf::IntRect(0, 200, this->tileSize, this->tileSize));
	this->wallBottom.push_back(sf::IntRect(100, 200, this->tileSize, this->tileSize));
	this->wallBottom.push_back(sf::IntRect(200, 200, this->tileSize, this->tileSize));
}

Map::Map(int map_width, int map_height, sf::Texture& map_texture) : 
	mapTexture(map_texture), mapHeight(map_height), mapWidth(map_width)
{
	this->initLocations(); //locations must update before tilemapInit
	this->initTileMap();
}

Map::~Map()
{
}

void Map::render(sf::RenderTarget& target)
{
	for (auto &row : this->tileMap)
	{
		for (auto &sp : row)
		{
			target.draw(sp);
		}
	}
	for (auto& sp : bonesSprites)
	{
		target.draw(sp);
	}
}
