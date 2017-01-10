#pragma once

#include "State.h"
#include "StateManager.h"
#include "MainMenuState.h"
#include "../Platform.h"
#include "../Texture.h"

#include "../entities/creatures/CreatureManager.h"

#include "../levelManagement/TileTypeManager.h"
#include "../levelManagement/MapManager.h"

#include "../entities/Button.h"


class GameState;
/**
@class GameOverState
@brief The editor state to customise generation
*/
class GameOverState : public State
{
public:

	/**
	@brief Create the GameOverState.

	@param [in,out] manager  - Pointer to the current state manager.
	@param [in,out] platform - Platform containing OS dependent data.
	*/

	GameOverState(StateManager* manager, Platform *platform, TileTypeManager *t, CreatureManager *c, MapManager *m, PauseMenuState *p);

	virtual ~GameOverState();

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

	bool leftDown = false;

	TileTypeManager *ttmng;
	CreatureManager *cmng;
	MapManager *mmng;
	PauseMenuState *pms;



	Button *playagainBtn;
	Button *quitMenuBtn;
	Button *quitDesktopBtn;

	Texture *gameOver;
	Texture *playAgainTexture;
	Texture *quitToMenuTexture;
	Texture *quitToDesktopTexture;

	std::vector<Button*> gameOverButtons;
};