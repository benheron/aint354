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
	@param rooms The number of rooms to create including specials
	*/
	RandMap(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, int rooms);


	/**
	@brief Creates a randomised number of maps.
	@param mpmn The Map Manager
	@param ttmng The TileType Manager
	@param cmng The Creature Manager
	@param usingLevelFile check if using a level file to create the entire map
	*/
	RandMap(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, bool usingLevelFile);



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

	void setCurRoomPos(Vec2 xy);

	MapRoom* getCurMap();

	Vec2 getCurRoomPos();


	std::vector<std::vector<MapRoom*>> getMap();


	void setPosition(Vec2 p);

	Vec2 getPosition();

	Vec2 getDimensions();

	int getNumRooms();

	MapRoom* getRoom(int index);

private:
	//max width/height
	int maxSize = 10;
	int numRooms = 26;

	

	void createFloor(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, int rooms);

	std::vector<std::vector<MapRoom*>> thisFloor;


	bool playerLoaded = false;

	Vec2 curRoomPos;



	void createEmptyFloor();

	void addRooms(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, int type);

	bool addToSingleRoom(MapManager *mpmng, TileTypeManager *ttmng, CreatureManager *cmng, Vec2 thisRoomPos, int type);

	int checkRoomConnections(Vec2 roomPos);

	std::vector<Vec2> roomPositions;


	std::vector<MapRoom*> currentRooms;


	Vec2 pos;
	Vec2 dimens;






};