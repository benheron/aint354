#pragma once

#include "State.h"
#include "StateManager.h"
//#include "MainMenuState.h"
#include "../Platform.h"
#include "../Texture.h"
#include "../entities/particles/ParticleSystem.h"
#include "../entities/creatures/CreatureManager.h"
#include "../levelManagement/RandMap.h"
#include "../levelManagement/MapRoom.h"
#include "../levelManagement/TileTypeManager.h"
#include "../levelManagement/MapManager.h"
#include "../levelManagement/Map.h"
#include "../levelManagement/TileSelection.h"

#include "../entities/Button.h"
#include "../UI/Slider.h"


class MainMenuState;
/**
@class PauseMenuState
@brief The editor state to customise generation
*/
class PauseMenuState : public State
{
public:

	/**
	@brief Create the PauseMenuState.

	@param [in,out] manager  - Pointer to the current state manager.
	@param [in,out] platform - Platform containing OS dependent data.
	*/

	PauseMenuState(StateManager* manager, Platform *platform, TileTypeManager *t, CreatureManager *c, MapManager *m);

	virtual ~PauseMenuState();

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



	Button *resumeBtn;
	Button *quitMenuBtn;
	Button *quitDesktopBtn;


	Texture *resumeTexture;
	Texture *quitToMenuTexture;
	Texture *quitToDesktopTexture;
	Texture *mnubg;

	std::vector<Button*> pauseMenuButtons;
};