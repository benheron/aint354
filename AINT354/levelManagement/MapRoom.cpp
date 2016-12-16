#include "MapRoom.h"
#include "Tile.h"
#include "../Utility.h"
#include "../Collision.h"

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

	for (int i = 0; i < layerIDs.size(); i++)
	{
		//Store the ID of the layer
		std::string layerID = layerIDs[i];


		int ySize = roomTiles["B"].size();



		for (int y = 0; y < ySize; y++)
		{
			int xSize = roomTiles["B"][0].size();

			if (layerID == "O" || layerID == "B")
			{

				for (int x = 0; x < xSize; x++)
				{
					delete  roomTiles[layerID][y][x];
				}
			}
		}
	}

	for (int j = 0; j < roomCreatures.size(); j++)
	{
		delete roomCreatures[j];
	}



}

void MapRoom::createRoom(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, Vec2 pos, int type)
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
					/*roomTiles[layerID][y].push_back(
						new Tile(tileTexture, Vec2((x * 32), (y *32)), Vec2(32, 32), spritePos, spriteDimensions, tileType)
					);*/


					roomTiles[layerID][y].push_back(
						new Tile(Vec2((x * 32), (y * 32)), Vec2(32, 32), tileType)
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


	//randomise creature placements
	for (int i = 0; i < roomCreatures.size(); i++)
	{
		int a = Utility::randomInt(50, 600);
		int b = Utility::randomInt(50, 420);

		roomCreatures[i]->setPosition(Vec2(a, b));

		//Utility::log(Utility::I, Utility::intToString(a) + ", " + Utility::intToString(b));
	}

	if (type == 1)
	{
		changeTileType("O", Vec2(13, 1), "S0", ttmng);
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

void MapRoom::setExists(bool e)
{
	exists = e;
}

bool MapRoom::getExists()
{
	return exists;
}



Tile* MapRoom::getTile(Vec2 xy)
{
	return roomTiles["O"][xy.y][xy.x];
}

int MapRoom::checkCollide(Entity *e)
{
	if (exists)
	{
		Vec2 localPos = e->getPosition();
		Vec2 localDimen = e->getDimensions();

		int mx = floor(localPos.x / 32);
		int my = floor(localPos.y / 32);

		//Utility::log(Utility::I, "Player Tile position: X: " + Utility::intToString(mx) + " Y: " + Utility::intToString(my));



		int c = 0;

		for (int i = my - 1; i < my + 2; i++)
		{
			for (int j = mx - 1; j < mx + 2; j++)
			{
				c++;
				if (!(j < 0 || j > 19 ||
					i < 0 || i > 14))
				{
					if (!roomTiles["O"][i][j]->haveBlankID())
					{
						Vec2 tmp = roomTiles["O"][i][j]->getPosition();
						Vec2 tmp2 = roomTiles["O"][i][j]->getDimensions();
						/*

						Utility::log(Utility::I, "Player X: " + Utility::floatToString(localPos.x) + ", Player Y: " + Utility::floatToString(localPos.y));
						Utility::log(Utility::I, "Player Width " + Utility::floatToString(localDimen.x) + ", Player Height: " + Utility::floatToString(localDimen.y));
						Utility::log(Utility::I, "Tile X: " + Utility::floatToString(tmp.x) + ", Tile Y: " + Utility::floatToString(tmp.y));
						Utility::log(Utility::I, "Tile Width " + Utility::floatToString(tmp2.x) + ", Tile Height: " + Utility::floatToString(tmp2.y));*/


						if (Collision::boxBoxCollision(localPos, localDimen, roomTiles["O"][i][j]->getPosition(), roomTiles["O"][i][j]->getDimensions()))
						{
							if (roomTiles["O"][i][j]->getTileTypeID() == "S0")
							{
								return 2;
							}
							else {
								return 1;
							}
						}
					}
				}
			}
		}

		return false;
	}
	return 0;

}


void MapRoom::changeTileType(std::string layer, Vec2 tilePos, std::string tileID, TileTypeManager *ttmng)
{
	roomTiles[layer][tilePos.y][tilePos.x]->setTileType(tileID, ttmng);
}