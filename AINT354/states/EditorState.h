#pragma once

#include "State.h"
#include "StateManager.h"
#include "../Platform.h"
#include "../Texture.h"
#include "GameState.h"
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


/**
@class EditorState
@brief The editor state to customise generation
*/
class EditorState : public State
{
public:

	/**
	@brief Create the EditorState.

	@param [in,out] manager  - Pointer to the current state manager.
	@param [in,out] platform - Platform containing OS dependent data.
	*/

	EditorState(StateManager* manager, Platform *platform, TileTypeManager *t, CreatureManager *c, MapManager *m);

	virtual ~EditorState();

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

	/**
	@brief Creates new map and destroys the old one
	*/
	void createNewMap();

	/**
	@brief Imports the level data from a file
	*/
	void importLevelData();

	/**
	@brief Exports the level data to a file
	*/
	void exportLevelData();

	Texture *white;

	RandMap *randFloor;
	MapRoom *currentMap;
	MiniMap* mm;

	Texture *genTexture;
	Button *genMapBtn;

	Button *testMapBtn;

	bool genBtnDwn = false;


	TileTypeManager *ttmng;
	CreatureManager *cmng;
	MapManager *mmng;

	Slider *numRoomsSlider;

	bool mouseDownSlider = false;

	TTF_Font *font = NULL;

	Texture *numRoomsText;

	TileSelection *tileSelection;

	std::string tileTypeSelected;
	

	Button *bgLayerBtn;
	Button *objLayerBtn;

	
	bool playMap = false;


	Texture *layerText;
	Texture *bgText;
	Texture *objText;

	std::string layerOn;

};