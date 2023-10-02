#ifndef MAP_H
#define MAP_H
#pragma once

class Map
{
private:
	const int tileSize = 100;
	std::vector<std::vector<sf::Sprite>> tileMap;
	sf::Texture &mapTexture;

	//intRect left right top bottom location of sprites on the whole texture sprite sheet
	//Hard coded by checking sprite pixels
	std::vector<sf::IntRect> wallTop;
	std::vector<sf::IntRect> wallBottom;

	std::vector<sf::IntRect> floorLocations;

	sf::IntRect enemySpawnLocation = sf::IntRect(0, 0, tileSize, tileSize);
	std::vector<sf::Sprite> bonesSprites;

	sf::IntRect wallLeft = sf::IntRect(0, 400, tileSize, tileSize);
	sf::IntRect wallRight = sf::IntRect(0, 500, tileSize, tileSize);
	sf::IntRect topRightWall = sf::IntRect(100, 300, tileSize, tileSize);
	sf::IntRect topLeftWall = sf::IntRect(0, 300, tileSize, tileSize);
	sf::IntRect bottomRightWall = sf::IntRect(300, 300, tileSize, tileSize);
	sf::IntRect bottomLeftWall = sf::IntRect(200, 300, tileSize, tileSize);



	int mapHeight;
	int mapWidth;

	void initTileMap();
	void initLocations();
public:
	Map(int map_width, int map_height, sf::Texture&);
	~Map();

	void render(sf::RenderTarget&);
};

#endif // !MAP_H