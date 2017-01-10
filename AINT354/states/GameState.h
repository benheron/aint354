#pragma once

#include "State.h"
#include "StateManager.h"
#include "PauseMenuState.h"
#include "GameOverState.h"
#include "../Platform.h"
#include "../levelManagement/TileTypeManager.h"
#include "../levelManagement/MapManager.h"
#include "../levelManagement/Map.h"
#include "../entities/particles/ParticleSystem.h"
#include "../entities/creatures/CreatureManager.h"
#include "../levelManagement/RandMap.h"
#include "../levelManagement/MapRoom.h"

#include "../levelManagement/MiniMap.h"

#include "../entities/GameHUD/HealthIcon.h"

//#include "..entities/creatures/Character.h"

/**
@class GameState
@brief A game state that contains the game itself
*/
class GameState : public State
{
public:

	/**
	@brief Create the GameState.

	@param [in,out] manager  - Pointer to the current state manager.
	@param [in,out] platform - Platform containing OS dependent data.
	*/

	GameState(StateManager* manager, Platform *platform, TileTypeManager *t, CreatureManager *c, MapManager *m, RandMap *map, int mode, PauseMenuState *p);
	
	virtual ~GameState();

	/**
	@brief Handles any events such as keyboard/mouse input.

	@return true to exit, false to continue.
	*/
	bool eventHandler();

	/**
	@brief Update any internal values.

	@param dt - delta time.
	*/
	void update(float dt);

	/**
	@brief Render any sprites relevant to the state
	*/
	void render();

protected:


	

	/**
	@brief Loads this State.
	*/
	virtual void load();

	/**
	@brief Unloads this State.
	*/
	virtual void unload();

	//TMP FOR TESTING
	RandMap *randFloor;
	MapRoom *currentMap;

	CharacterType *playerType;

	ParticleSystem* particles;

	Character *player;


	MiniMap* mm;


	TileTypeManager *ttmng;
	CreatureManager *cmng;
 	MapManager *mmng;

	PauseMenuState *pms;


	int mode;

	int changeThisState = 0;

	bool esc = false;

	bool kUp = false, kDown = false, kLeft = false, kRight = false;




	HealthIcon *health;
};