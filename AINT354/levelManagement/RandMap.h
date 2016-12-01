#pragma once
#pragma once

#include "../entities/Entity.h"
#include "Tile.h"
#include "../entities/creatures/Character.h"
#include "../entities/creatures/Creature.h"
#include "Map.h"
#include "MapManager.h"
#include <Vector>
#include "MapRoom.h"

/**
@brief Contains all the data and functions dealing with the Map objects.
*/
class RandMap
{
public:
	/**
	@brief Creates a randomised number of maps.
	*/
	RandMap();

	/**
	@brief Creates a randomised number of maps.
	@param mpmn The Map Manager
	*/
	RandMap(MapManager *mpmn);

	/**
	@brief Creates a randomised number of maps.
	@param mpmn The Map Manager
	@param ttmng The TileType Manager
	@param cmng The Creature Manager
	*/
	RandMap(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng);

	/**
	@brief Map destructor.
	*/
	~RandMap();

	/**
	@brief Update the Map.
	@param dt The delta time.
	*/
	void update(float dt);

	/**
	@brief Render the Tile objects in the map.
	@param renderer A pointer to the renderer.
	*/
	void render(SDL_Renderer* renderer);


	void loadPlayer(CharacterType *pt);

	Character *player;

	void setCurRoomPos(Vec2 xy);

	MapRoom* getCurMap();

	Vec2 getCurRoomPos();


	std::vector<std::vector<MapRoom*>> getMap();

private:
	///A vector to hold all of the layer IDs.
	std::vector<std::string> layerIDs;
	///A 3D vector that contains all of the tiles. [Layer ID][Y Index][X Index]
	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> randMapTiles;

	//An unordered map that contains all of the creatures. [Layer ID][Y Index][X Index]
	//std::unordered_map<std::string, Creature*> mapCreatures;

	///A vector of all creatures
	std::vector<Creature*> randMapCreatures;

	///A 2D vector storing the spawn point of the player
	Vec2 spawnPoint;



	void createFloor(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng);

	std::vector<std::vector<MapRoom*>> thisFloor;


	bool playerLoaded = false;

	Vec2 curRoomPos;


};