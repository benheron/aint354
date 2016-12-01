#pragma once

#include "../entities/Entity.h"
#include "Tile.h"
#include "../entities/creatures/Character.h"
#include "../entities/creatures/Creature.h"
#include <Vector>


/**
@brief Contains all the data for the map templates
*/
class RoomTemplate
{
public:
	/**
	@brief Creates the Map for the level.
	@param mapTiles The Tiles in the Map.
	@param layerIDs The list of the layer ID's.
	*/
	RoomTemplate(std::unordered_map<std::string, std::vector<std::vector<Tile*>>> mapTiles, std::vector<Creature*> mapCreatures, std::vector<std::string> layerIDs, Vec2 spawnPoint);



	RoomTemplate(std::unordered_map<std::string, std::vector<std::vector<std::string>>> mapTilesData, std::vector<std::string> roomCreaturesData, std::vector<std::string> layerIDs);


	RoomTemplate::RoomTemplate(std::unordered_map<std::string, std::vector<std::vector<Tile*>>> mapTiles, std::vector<Creature*> mapCreatures, std::vector<std::string> layerIDs, Vec2 spawnPoint, Vec2 mapPos);



	/**
	@brief Map destructor.
	*/
	~RoomTemplate();

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

	void setPos(Vec2 pos);

	Vec2 getPos();

	void setAccess(bool b);

	bool getAccess();


	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> getRoomTiles();

	std::vector<std::string> getLayerIDs();

	std::vector<Creature*> getCreatures();



	std::unordered_map<std::string, std::vector<std::vector<std::string>>> getRoomTileData();

	std::vector<std::string> getCreatureData();

	

private:
	///A vector to hold all of the layer IDs.
	std::vector<std::string> layerIDs;
	///A 3D vector that contains all of the tiles. [Layer ID][Y Index][X Index]
	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> roomTiles;

	//An unordered map that contains all of the creatures. [Layer ID][Y Index][X Index]
	//std::unordered_map<std::string, Creature*> mapCreatures;

	///A vector of all creatures
	std::vector<Creature*> roomCreatures;

	///A 2D vector storing the spawn point of the player
	Vec2 spawnPoint;

	///the map's ID
	std::string ID;



	bool playerLoaded = false;


	Vec2 mapPos;

	bool access = false;




	///A 3D vector that contains all of the tiles. [Layer ID][Y Index][X Index]
	std::unordered_map<std::string, std::vector<std::vector<std::string>>> roomTilesData;

	//An unordered map that contains all of the creatures. [Layer ID][Y Index][X Index]
	//std::unordered_map<std::string, Creature*> mapCreatures;

	///A vector of all creatures
	std::vector<std::string> roomCreaturesData;


};