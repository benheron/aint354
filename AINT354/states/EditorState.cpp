#include "EditorState.h"
#include "../Utility.h"
#include "../Collision.h"




EditorState::EditorState(StateManager* manager, Platform *platform, TileTypeManager *t, CreatureManager *c, MapManager *m, PauseMenuState *p)
	: State(manager, platform)
{
	stateName = "EditorState";
	ttmng = t;
	cmng = c;
	mmng = m;
	pms = p;
}

EditorState::~EditorState()
{

}

bool EditorState::eventHandler()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	mousePos = Vec2(mouseX, mouseY);
	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_MOUSEMOTION:
			//while mouse is moving
			if (mm->mouseCollide(mouseX, mouseY))
			{
				//Utility::log(Utility::I, "Collided at: " + Utility::intToString(mouseX) + ", " + Utility::intToString(mouseY));
			}

			//slider
			if (mouseDownSlider)
			{
				if (Collision::pointBoxCollision(mousePos, numRoomsSlider->getPosition(), numRoomsSlider->getDimensions()))
				{
					numRoomsSlider->changeValue(mousePos);

					Texture *nTex = new Texture(platform->getRenderer(), Utility::intToString(numRoomsSlider->getValue()), font, { 255,255,255 });
					Texture *oldTex = numRoomsText;

					numRoomsText = nTex;

					delete oldTex;
				}
			}


		



			//buttons
			for (int i = 0; i < editorButtons.size(); i++)
			{
				if (Collision::pointBoxCollision(mousePos, editorButtons[i]->getPosition(), editorButtons[i]->getDimensions()))
				{
					if (!editorButtons[i]->getSelected())
					{
						editorButtons[i]->setHover(true);
					}
				}
				else {
					editorButtons[i]->setHover(false);
				}
			}


			break;
		case SDL_QUIT:
			return true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (events.button.button)
			{
			//while mouse is down

			//left click
			case SDL_BUTTON_LEFT:
				//minimap
				if (mm->mouseCollide(mouseX, mouseY))
				{
					Vec2 tmp = mm->changeRoom(mouseX, mouseY);
					if (tmp.x != -1)
					{
						randFloor->setCurRoomPos(tmp);
						currentMap = randFloor->getCurMap();
					}
				}

				//generate map button
				if (Collision::pointBoxCollision(Vec2(mouseX, mouseY), genMapBtn->getPosition(), genMapBtn->getDimensions()))
				{
					genBtnDwn = true;
					createNewMap();
				}

				//slider
				if (Collision::pointBoxCollision(mousePos, numRoomsSlider->getPosition(), numRoomsSlider->getDimensions()))
				{
					numRoomsSlider->changeValue(mousePos);
					mouseDownSlider = true;

					Texture *nTex = new Texture(platform->getRenderer(), Utility::intToString(numRoomsSlider->getValue()), font, { 255,255,255 });
					Texture *oldTex = numRoomsText;

					numRoomsText = nTex;

					delete oldTex;
				}



				//add tiles or creatures to the map itself
				if (Collision::pointBoxCollision(mousePos, randFloor->getPosition(), randFloor->getDimensions()))
				{
					changingTiles = true;
				/*	if (tileSelection->getTypeSelected() == "O")
					{
						randFloor->getCurMap()->changeTileType("O", mousePos / 32, tileTypeSelected, ttmng);
					}
					else if (tileSelection->getTypeSelected() == "B") {
						randFloor->getCurMap()->changeTileType("B", mousePos / 32, tileTypeSelected, ttmng);
					}
					else if (tileSelection->getTypeSelected() == "C") {
						randFloor->getCurMap()->addCreature(mousePos, cmng->getCreatureType("A0"));
					}*/
					
					
				}

				//tile selection
				if (Collision::pointBoxCollision(mousePos, tileSelection->getPosition(), tileSelection->getDimensions()))
				{
					tileSelection->changeSelectedTile(mousePos);
					tileTypeSelected = tileSelection->getSelectedTile();
				}

				//background layer button
				if (Collision::pointBoxCollision(mousePos, bgLayerBtn->getPosition(), bgLayerBtn->getDimensions()))
				{
					bgLayerBtn->setSelected(true);
					crLayerBtn->setSelected(false);
					objLayerBtn->setSelected(false);
					tileSelection->setTypeSelected("B");
					tileTypeSelected = tileSelection->getSelectedTile();
				}

				//object layer button
				if (Collision::pointBoxCollision(mousePos, objLayerBtn->getPosition(), objLayerBtn->getDimensions()))
				{
					bgLayerBtn->setSelected(false);
					crLayerBtn->setSelected(false);
					objLayerBtn->setSelected(true);
					tileSelection->setTypeSelected("O");
					tileTypeSelected = tileSelection->getSelectedTile();
				}

				//add creature
				if (Collision::pointBoxCollision(mousePos, crLayerBtn->getPosition(), crLayerBtn->getDimensions()))
				{
					bgLayerBtn->setSelected(false);
					crLayerBtn->setSelected(true);
					objLayerBtn->setSelected(false);
					tileSelection->setTypeSelected("C");
				}


				//test map button
				if (Collision::pointBoxCollision(mousePos, testMapBtn->getPosition(), testMapBtn->getDimensions()))
				{
					playMap = true;
				}

				//import map button
				if (Collision::pointBoxCollision(mousePos, impMapBtn->getPosition(), impMapBtn->getDimensions()))
				{
					importLevelData();
				}

				//export map button
				if (Collision::pointBoxCollision(mousePos, expMapBtn->getPosition(), expMapBtn->getDimensions()))
				{
					exportData(0);
				}

				//export room as template button
				if (Collision::pointBoxCollision(mousePos, expRoomBtn->getPosition(), expRoomBtn->getDimensions()))
				{
					exportRoomAsTemplate();
				}

				if (Collision::pointBoxCollision(mousePos, paintBtn->getPosition(), paintBtn->getDimensions()))
				{
					paintBtn->setSelected(true);
					eraseBtn->setSelected(false);
				}

				if (Collision::pointBoxCollision(mousePos, eraseBtn->getPosition(), eraseBtn->getDimensions()))
				{
					paintBtn->setSelected(false);
					eraseBtn->setSelected(true);
				}


			break;
				

			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouseDownSlider = false;
				changingTiles = false;
			break;
			}
		break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym)
			{
				//pressing a key
			case SDLK_ESCAPE:
				//pause menu
				stateManager->addState(pms);
				break;
			}
			break;
		case SDL_KEYUP:
			switch (events.key.keysym.sym)
			{
			case SDLK_i:
				//importLevelData();
				break;

			case SDLK_e:
				//exportLevelData();
				break;
				//letting go of a key
			default:
				Utility::log(Utility::I, Utility::intToString(events.key.keysym.sym));
				break;
			}
			break;
		}
	}
	return false;
}

void EditorState::update(float dt)
{
	//Utility::log(Utility::I, "Slider value: " + Utility::intToString(numRoomsSlider->getValue()));
	if (playMap)
	{
		playMap = false;
		active = false;
		stateManager->addState(new GameState(stateManager, platform, ttmng, cmng, mmng, randFloor, 1, pms));
	}


	//add tiles or creatures to the map itself
	if (changingTiles)
	{
		if (Collision::pointBoxCollision(mousePos, randFloor->getPosition()+Vec2(32,32), randFloor->getDimensions() - Vec2(64,64)))
		{
			if (paintBtn->getSelected())
			{
				if (tileSelection->getTypeSelected() == "O")
				{
					randFloor->getCurMap()->changeTileType("O", mousePos / 32, tileTypeSelected, ttmng);
				}
				else if (tileSelection->getTypeSelected() == "B") {
					randFloor->getCurMap()->changeTileType("B", mousePos / 32, tileTypeSelected, ttmng);
				}
				else if (tileSelection->getTypeSelected() == "C") {
					randFloor->getCurMap()->addCreature(mousePos, cmng->getCreatureType("A0"));
				}
			}
			else if (eraseBtn->getSelected()) {
				if (tileSelection->getTypeSelected() == "O")
				{
					randFloor->getCurMap()->changeTileType("O", mousePos / 32, "XX", ttmng);
				}
				else if (tileSelection->getTypeSelected() == "B") {
					randFloor->getCurMap()->changeTileType("B", mousePos / 32, "XX", ttmng);
				}
				else if (tileSelection->getTypeSelected() == "C") {
					randFloor->getCurMap()->changeTileType("C", mousePos / 32, "XX", ttmng);
				}
			}
		}
	}
}

void EditorState::render()
{

	mm->render(platform->getRenderer());
	randFloor->getCurMap()->render(platform->getRenderer());
	//room grid
	for (int i = 1; i < 20; i ++)
	{
		white->pushToScreen(platform->getRenderer(), Vec2(i * 32, 32), Vec2(1, 13*32));
	}
	for (int j = 1; j < 15; j++)
	{
		white->pushToScreen(platform->getRenderer(), Vec2(32, j*32), Vec2(18*32,1));
	}

	//minimap grid
	for (int i = 0; i < 11; i++)
	{
		white->pushToScreen(platform->getRenderer(), Vec2(700+(i * 20), 15), Vec2(1, 10 * 15));
	}
	for (int j = 0; j < 11; j++)
	{
		white->pushToScreen(platform->getRenderer(), Vec2(700, 15+(j * 15)), Vec2(10 * 20, 1));
	}

	

	numRoomsSlider->render(platform->getRenderer());

	

	int nstx = (2 * numRoomsSlider->getPosition().x + numRoomsSlider->getDimensions().x) / 2 -(numRoomsText->getDimensions().x / 2);
	int nsty = numRoomsSlider->getPosition().y + numRoomsSlider->getDimensions().y + 5;

	Vec2 numSliderTextPos = Vec2(nstx, nsty);

	if (numRoomsSlider->getValue() >  9)
	{
		numRoomsText->renderText(platform->getRenderer(), numSliderTextPos, 20);

	}
	else {
		numRoomsText->renderText(platform->getRenderer(), numSliderTextPos, Vec2(10, 20));
	}


	tileSelection->render(platform->getRenderer());




	layerText->renderText(platform->getRenderer(), Vec2(670, 285), Vec2(50, 20));
	bgText->renderText(platform->getRenderer(), Vec2(690, 305), Vec2(100,20));
	objText->renderText(platform->getRenderer(), Vec2(820, 305), Vec2(60, 20));
	
	enemyText->renderText(platform->getRenderer(), Vec2(670, 493), Vec2(50, 20));


	



	bgLayerBtn->render(platform->getRenderer());
	objLayerBtn->render(platform->getRenderer());
	crLayerBtn->render(platform->getRenderer());

	for (int i = 0; i < editorButtons.size(); i++)
	{
		editorButtons[i]->render(platform->getRenderer());
	}
	/*testMapBtn->render(platform->getRenderer());
	expMapBtn->render(platform->getRenderer());
	impMapBtn->render(platform->getRenderer());
	expRoomBtn->render(platform->getRenderer());
	genMapBtn->render(platform->getRenderer());*/

	enemy->render(platform->getRenderer());
}

void EditorState::load()
{
	//generate-map button
	//white texture
	white = new Texture(platform->getRenderer(), 255, 255, 255);

	

	//room slider
	numRoomsSlider = new Slider(white, Vec2(700, 245), Vec2(200, 15), 20);

	//map
	randFloor = new RandMap(mmng, ttmng, cmng, numRoomsSlider->getValue());
	currentMap = randFloor->getCurMap();

	//minimap
	mm = new MiniMap(platform->getRenderer(), 1);
	mm->buildMiniMap(randFloor, Vec2(700, 15));


	//buttons
	genTexture = new Texture("res/img/buttons/generateBtn.png", platform->getRenderer());
	genMapBtn = new Button(genTexture, Vec2(750, 175), Vec2(100, 46), Vec2(0, 0));

	Texture *testMapTexture = new Texture("res/img/buttons/testmapBtn.png", platform->getRenderer());
	testMapBtn = new Button(testMapTexture, Vec2(272, 485), Vec2(100, 46), Vec2(0, 0));

	Texture *impTexture = new Texture("res/img/buttons/importBtn.png", platform->getRenderer());
	impMapBtn = new Button(impTexture, Vec2(0, 485), Vec2(50, 23), Vec2(0, 0));

	Texture *expTexture = new Texture("res/img/buttons/exportBtn.png", platform->getRenderer());
	expMapBtn = new Button(expTexture, Vec2(0, 510), Vec2(50, 23), Vec2(0, 0));


	Texture *expRoomTexture = new Texture("res/img/buttons/exportRoomBtn.png", platform->getRenderer());
	expRoomBtn = new Button(expRoomTexture, Vec2(60, 510), Vec2(50, 23), Vec2(0, 0));


	editorButtons.push_back(genMapBtn);
	editorButtons.push_back(testMapBtn);
	editorButtons.push_back(impMapBtn);
	editorButtons.push_back(expMapBtn);
	editorButtons.push_back(expRoomBtn);


	font = TTF_OpenFont("res/fonts/ariblk.ttf", 20);
	numRoomsText = new Texture(platform->getRenderer(), Utility::intToString(numRoomsSlider->getValue()), font, { 255,255,255 });


	//tile selection
	Texture *grey = new Texture(platform->getRenderer(), 128, 128, 128);
	tileSelection = new TileSelection(Vec2(670, 330), Vec2(8, 5), ttmng, white, grey);
	tileTypeSelected = "XX";
	tileSelection->setTypeSelected("B");



	//layer
	Texture *btn = new Texture("res/img/buttons/selectBtn.png", platform->getRenderer());

	bgLayerBtn = new Button(btn, Vec2(795, 305), Vec2(16, 16), Vec2(0, 0));
	objLayerBtn = new Button(btn, Vec2(885, 305), Vec2(16, 16), Vec2(0, 0));
	crLayerBtn = new Button(btn, Vec2(725, 495), Vec2(16, 16), Vec2(0, 0));
	bgLayerBtn->setSelected(true);

	paintTex = new Texture("res/img/buttons/paint.png", platform->getRenderer());
	eraseTex = new Texture("res/img/buttons/erase.png", platform->getRenderer());

	paintBtn = new Button(paintTex, Vec2(540, 490), Vec2(32, 32), Vec2(0, 0));
	eraseBtn = new Button(eraseTex, Vec2(572, 490), Vec2(32, 32), Vec2(0, 0));

	paintBtn->setSelected(true);

	editorButtons.push_back(paintBtn);
	editorButtons.push_back(eraseBtn);


	layerText = new Texture(platform->getRenderer(), "Layer: ", font, { 255,255,255 });
	bgText = new Texture(platform->getRenderer(), "Background: ", font, { 255,255,255 });
	objText = new Texture(platform->getRenderer(), "Object: ", font, { 255,255,255 });

	enemyText = new Texture(platform->getRenderer(), "Enemy: ", font, { 255,255,255 });


	enemy = new Creature(grey, Vec2(750, 500), Vec2(13, 19), cmng->getCreatureType("A0"));
	
	 
}

void EditorState::unload()
{
	for (int i = editorButtons.size()-1; i > -1; i--)
	{
		delete editorButtons[i];
	}

	delete layerText;
	delete bgText;
	delete objText;
	delete enemyText;
	delete tileSelection;
	//delete font;
	delete numRoomsSlider;
	delete randFloor;
	delete mm;
	delete genTexture;

	
}

void EditorState::createNewMap()
{
	RandMap *newFloor = new RandMap(mmng, ttmng, cmng, numRoomsSlider->getValue());
	RandMap *oldFloor;

	oldFloor = randFloor;
	randFloor = newFloor;

	delete oldFloor;

	MiniMap *newMiniMap = new MiniMap(platform->getRenderer(), 0);
	newMiniMap->buildMiniMap(randFloor, Vec2(700, 15));

	MiniMap *oldMiniMap = mm;
	delete oldMiniMap;

	mm = newMiniMap;

	currentMap = randFloor->getCurMap();
}


void EditorState::createMapFromFile(MapManager *newmng)
{
	RandMap *newFloor = new RandMap(newmng, ttmng, cmng, true);
	RandMap *oldFloor;

	oldFloor = randFloor;
	randFloor = newFloor;

	delete oldFloor;

	MiniMap *newMiniMap = new MiniMap(platform->getRenderer(), 0);
	newMiniMap->buildMiniMap(randFloor, Vec2(700, 15));

	MiniMap *oldMiniMap = mm;
	delete oldMiniMap;

	mm = newMiniMap;

	currentMap = randFloor->getCurMap();
}

void EditorState::importLevelData()
{
	IFileDialog *pfd;
	if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd))))
	{
		if (SUCCEEDED(pfd->Show(NULL)))
		{
			IShellItem *psi;
			if (SUCCEEDED(pfd->GetResult(&psi)))
			{
				PWSTR pszPath;
				if (SUCCEEDED(psi->GetDisplayName(SIGDN_FILESYSPATH, &pszPath)))
				{
					std::string str = CW2A(pszPath);
					Utility::log(Utility::I, str);

					//get level data
					MapManager *newmmng = new MapManager(str, ttmng, cmng, 1);
					createMapFromFile(newmmng);

					delete newmmng;

					CoTaskMemFree(pszPath);
				}
				psi->Release();
			}
		}
		pfd->Release();
	}
}

void  EditorState::exportData(int type)
{
	// CoCreate the File Open Dialog object.
	IFileSaveDialog *pfsd;
	if (SUCCEEDED(CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfsd))))
	{
		pfsd->SetDefaultExtension(L"txt");

		if (SUCCEEDED(pfsd->Show(NULL)))
		{
			IShellItem *psiResult;

			if (SUCCEEDED(pfsd->GetResult(&psiResult)))
			{
				PWSTR pszNewFileName;
				if (SUCCEEDED(psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszNewFileName)))
				{
					std::string str = CW2A(pszNewFileName);
					Utility::log(Utility::I, str);
					if (type == 0)
					{
						exportLevelToFile(str);
					}
					else if (type == 1)
					{
						exportRoomAsTemplate();
					}

					CoTaskMemFree(pszNewFileName);
				}
				psiResult->Release();
			}
		}
		pfsd->Release();
	}
}



void EditorState::exportLevelToFile(std::string fn)
{

	std::ofstream levelFile(fn);

	if (levelFile.is_open())
	{
		Utility::log(Utility::I, "New file, yay");

		int numRoomsToSave = randFloor->getNumRooms();

		levelFile << numRoomsToSave;
		levelFile << "\n";

		for (int i = 0; i < numRoomsToSave; i++)
		{
			

			MapRoom *mr = randFloor->getRoom(i);
			Vec2 p = mr->getPos();

			levelFile << p.x;
			levelFile << " ";
			levelFile << p.y;
			levelFile << "\n";


			std::unordered_map<std::string, std::vector<std::vector<std::string>>> rts = mr->getRoomTilesStrings();
			std::vector<std::string> rcs = mr->getRoomCreaturesStrings();

			std::vector<std::string> lIDs = mr->getLayerIDs();


			for (int i = 0; i < 3; i++)
			{

				levelFile << lIDs[i];
				levelFile << "\n";


				int ySize = rts["B"].size();



				for (int y = 0; y < ySize; y++)
				{
					int xSize = rts["B"][0].size();

					if (lIDs[i] == "O" || lIDs[i] == "B")
					{
						for (int x = 0; x < xSize; x++)
						{
							//Get the tile
							std::string tileID = rts[lIDs[i]][y][x];

							levelFile << tileID;
							levelFile << " ";
						}

						levelFile << "\n";
					}
					else if (lIDs[i] == "C")
					{
						
						for (int x = 0; x < xSize; x++)
						{
							//Get the creature
							std::string creatureID = rcs[y*xSize + x];

							levelFile << creatureID;
							levelFile << " ";

			
						}
						levelFile << "\n";
					}

				}
			}

		}
		levelFile.close();

	}
	else {
		Utility::log(Utility::I, "Failed :(	");
	}
}


void EditorState::exportRoomAsTemplate()
{

	int msgbox = MessageBox(
		NULL,
		(LPCWSTR)L"Are you sure?",
		(LPCWSTR)L"Confirmation create template",
		MB_YESNO
	);

	Utility::log(Utility::I, Utility::intToString(msgbox));

	if (msgbox == 6)
	{
		MapRoom *mr = randFloor->getCurMap();

		std::unordered_map<std::string, std::vector<std::vector<std::string>>> rts = mr->getRoomTilesStrings();
		std::vector<std::string> rcs = mr->getRoomCreaturesStrings();

		std::vector<std::string> lIDs = mr->getLayerIDs();

		int a = mmng->getNumberMaps() + 1;



		std::ostringstream oss;
		oss << a;
		std::string filePath = "res/txt/map" + oss.str() + ".txt";


		std::ofstream roomFile(filePath);



		if (roomFile.is_open())
		{
			Utility::log(Utility::I, "New file, yay");


			if (a < 10)
			{
				roomFile << "M0";
			}
			else {
				roomFile << "M";
			}

			roomFile << a;

			roomFile << "\n";

			roomFile << "20";

			roomFile << "\n";

			roomFile << "15";

			roomFile << "\n";

			roomFile << "3";

			roomFile << "\n";

			roomFile << "32";

			roomFile << "\n";

			roomFile << "32";

			roomFile << "\n";

			for (int i = 0; i < 3; i++)
			{

				roomFile << lIDs[i];
				roomFile << "\n";


				int ySize = rts["B"].size();



				for (int y = 0; y < ySize; y++)
				{
					int xSize = rts["B"][0].size();

					if (lIDs[i] == "O" || lIDs[i] == "B")
					{
						for (int x = 0; x < xSize; x++)
						{


							std::string tileID;
							if (lIDs[i] == "O")
							{
								if ((y == 0 || y == 14) && x > 0 && x < 19)
								{
									tileID = "W0";
								}
								else if ((x == 0 || x == 19) && y > 0 && y < 14)
								{
									tileID = "W1";
								}
								else {
									tileID = rts[lIDs[i]][y][x];
								}

								int g = 0;
							}
							else {
								tileID = rts[lIDs[i]][y][x];
							}


							//Get the tile




							roomFile << tileID;
							roomFile << " ";
						}

						roomFile << "\n";
					}
					else if (lIDs[i] == "C")
					{

						for (int x = 0; x < xSize; x++)
						{
							//Get the creature
							std::string creatureID = rcs[y*xSize + x];

							roomFile << creatureID;
							roomFile << " ";


						}
						roomFile << "\n";
					}

				}
			}
			roomFile.close();
			mmng->loadMapData(filePath, ttmng, cmng);

		}
		else {
			Utility::log(Utility::I, "Failed :(	");
		}
	}

	
}