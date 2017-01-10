#pragma once

#include "State.h"
#include "StateManager.h"
#include "../Platform.h"
#include "../Texture.h"
#include "GameState.h"
#include "PauseMenuState.h"
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

#include <windows.h>

#include <atlstr.h>

#include <sstream> 
#include <comdef.h> 
#include <shlobj.h>
#include <objbase.h>      // For COM headers
#include <shobjidl.h>     // for IFileDialogEvents and IFileDialogControlEvents
#include <shlwapi.h>
#include <knownfolders.h> // for KnownFolder APIs/datatypes/function headers
#include <propvarutil.h>  // for PROPVAR-related functions
#include <propkey.h>      // for the Property key APIs/datatypes
#include <propidl.h>      // for the Property System APIs
#include <strsafe.h>      // for StringCchPrintfW
#include <shtypes.h>      // for COMDLG_FILTERSPEC
#include <new>


class MiniMap;

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

	EditorState(StateManager* manager, Platform *platform, TileTypeManager *t, CreatureManager *c, MapManager *m, PauseMenuState *p);

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
	void exportData(int type);


	/**
	@brief Creates a new level from the file loaded
	*/
	void createMapFromFile(MapManager *newmng);

	/**
	@brief Exports the current map to a new file
	*/
	void exportLevelToFile(std::string fn);

	/**
	@brief Exports the currently viewed map as a template to be used in future level generations
	*/
	void exportRoomAsTemplate();

	///Just a white texture
	Texture *white;

	///The level data we're using
	RandMap *randFloor;

	///The current map to display
	MapRoom *currentMap;
	///The minimap of the level
	MiniMap* mm;

	///The generate texture
	Texture *genTexture;
	///A button to generate a level
	Button *genMapBtn;

	///The test map button
	Button *testMapBtn;
	///The export map button
	Button *expMapBtn;

	///The import map button
	Button *impMapBtn;
	///The export room button
	Button *expRoomBtn;

	///if generate button is down
	bool genBtnDwn = false;

	///local reference to the tile type manager
	TileTypeManager *ttmng;

	///local reference to the creature manager
	CreatureManager *cmng;

	///local reference to the map manager
	MapManager *mmng;
	///The slider used to choose the number of rooms to generate
	Slider *numRoomsSlider;

	///if the mouse is down on the slider
	bool mouseDownSlider = false;

	///font used
	TTF_Font *font = NULL;

	///The number of rooms text number
	Texture *numRoomsText;

	///Tile selection object to allow users to choose which tiles to add
	TileSelection *tileSelection;

	std::string tileTypeSelected;
	

	Button *bgLayerBtn;
	Button *objLayerBtn;
	Button *crLayerBtn;

	Texture *paintTex;
	Texture *eraseTex;

	Button *paintBtn;
	Button *eraseBtn;

	
	bool playMap = false;


	Texture *layerText;
	Texture *bgText;
	Texture *objText;

	Texture *enemyText;

	std::string layerOn;



	std::vector<Button*> editorButtons;


	PauseMenuState *pms;



	Creature *enemy;
	Vec2 mousePos;

	bool changingTiles = false;
};