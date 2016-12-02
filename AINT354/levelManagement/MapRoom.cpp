#include "MapRoom.h"
#include "Tile.h"

MapRoom::MapRoom()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 15; j++)
		{

		}
	}
}

MapRoom::MapRoom(MapManager *mpmng, Vec2 pos, int e)
{
	RoomTemplate *rt = mpmng->getRandomMap();
	roomTiles = rt->getRoomTiles();
	roomCreatures = rt->getCreatures();

	layerIDs = rt->getLayerIDs();
	roomPos = pos;

	exists = e;
}

MapRoom::~MapRoom()
{
	
}

void MapRoom::createRoom(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, Vec2 pos)
{
	//generate new room from the template data
	//this allows the same room to be used but hold different data incase some is changed mid-gameplay
	RoomTemplate *rt = mpmng->getRandomMap();





	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> tmpR = rt->getRoomTiles();

	
	//roomTiles = rt->getRoomTiles();
	//roomCreatures = rt->getCreatures();

	layerIDs = rt->getLayerIDs();
	roomPos = pos;

	exists = true;



	int numLayers = layerIDs.size();


	std::unordered_map<std::string, std::vector<std::vector<std::string>>> roomData = rt->getRoomTileData();
	std::vector<std::string> creatureData = rt->getCreatureData();


	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> roomys;
	std::vector<std::string> creatureys;

	int c = 0;

	for (int i = 0; i < numLayers; i++)
	{
		//Store the ID of the layer
		std::string layerID = layerIDs[i];


		int ySize = roomData["B"].size();



		for (int y = 0; y < ySize; y++)
		{
			int xSize = roomData["B"][0].size();

			if (layerID == "O" || layerID == "B")
			{
				std::vector<Tile*> tiles;
				roomTiles[layerID].push_back(tiles);

				for (int x = 0; x < xSize; x++)
				{
					//Get the tile
					std::string tileID = roomData[layerID][y][x];

					//Get the data to load into the new tile
					TileType* tileType = ttmng->getTileType(tileID);
					Vec2 spriteDimensions = tileType->getSpriteDimensions();
					Vec2 spritePos = tileType->getSpritePos();
					Texture* tileTexture = tileType->getTexture();

					//Store tile
					roomTiles[layerID][y].push_back(
						new Tile(tileTexture, Vec2((x * 32), (y *32)), Vec2(32, 32), spritePos, spriteDimensions, tileType)
					);

				}
			}
			else if (layerID == "C")
			{
				//std::vector<Creature*> creatures;
				//mapCreatures[layerID].push_back(creatures);
				for (int x = 0; x < xSize; x++)
				{
					//Get the creature
					std::string creatureID = creatureData[c];

					if (creatureID != "XX")
					{
						Vec2 pos = Vec2((x * 32), (y * 32));

						CreatureType* creatureType = cmng->getCreatureType(creatureID);
						Vec2 spriteDimensions = creatureType->getSpriteDimensions();
						Texture* creatureTexture = creatureType->getTexture();

						roomCreatures.push_back(
							new Creature(creatureTexture, pos, spriteDimensions, creatureType));
						
					}
					c++;
				}
			}

		}
	}











}

void MapRoom::update(float dt)
{
}

void MapRoom::render(SDL_Renderer* renderer)
{


	//Load in all the map data
	//Loop through all of the Layer ID's
	for (unsigned int i = 0; i < layerIDs.size(); i++)
	{
		//Loop through all the map tiles
		for (unsigned int y = 0; y < roomTiles[layerIDs[i]].size(); y++)
		{
			for (unsigned int x = 0; x < roomTiles[layerIDs[i]][y].size(); x++)
			{
				roomTiles[layerIDs[i]][y][x]->render(renderer);
			}
		}
	}

	//load in the creature data

	for (unsigned int i = 0; i < roomCreatures.size(); i++)
	{
		roomCreatures[i]->render(renderer);
	}


	//load in the player data

	if (playerLoaded)
	{
		player->render(renderer);
	}
}

void MapRoom::loadPlayer(CharacterType *pt)
{
	player = new Character(pt->getTexture(), Vec2(25,25), pt);

	playerLoaded = true;
}


void MapRoom::setPos(Vec2 pos)
{

	roomPos = pos;
}

Vec2 MapRoom::getPos()
{
	return roomPos;
}

void MapRoom::setAccess(bool b)
{
	access = true;
}

bool MapRoom::getAccess()
{
	return access;
}