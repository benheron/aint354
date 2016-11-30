#pragma once

#include "State.h"

/**
@class MainMenuState
@brief The main menu state to the different parts of the project
*/
class MainMenuState : public State
{
public:

	/**
	@brief Create the MainMenuState.

	@param [in,out] manager  - Pointer to the current state manager.
	@param [in,out] platform - Platform containing OS dependent data.
	*/

	MainMenuState(StateManager* manager, Platform *platform);

	virtual ~MainMenuState();

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
};