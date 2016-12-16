
#pragma once

#include "State.h"
#include "StateManager.h"
#include "../Platform.h"
#include "../Texture.h"
#include "MainMenuState.h"
#include "../entities/creatures/CreatureManager.h"
#include "../levelManagement/MapManager.h"
#include "../entities/Button.h"

/**
@class LoadState
@brief The editor state to customise generation
*/
class LoadState : public State
{
public:

	/**
	@brief Create the LoadState.

	@param [in,out] manager  - Pointer to the current state manager.
	@param [in,out] platform - Platform containing OS dependent data.
	*/

	LoadState(StateManager* manager, Platform *platform);

	virtual ~LoadState();

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


	TileTypeManager *ttmng;
	CreatureManager *cmng;
	MapManager *mmng;


};