#include "EditorState.h"
#include "../Utility.h"
#include "../Collision.h"

EditorState::EditorState(StateManager* manager, Platform *platform, TileTypeManager *t, CreatureManager *c, MapManager *m)
	: State(manager, platform)
{
	stateName = "EditorState";
	ttmng = t;
	cmng = c;
	mmng = m;
}

EditorState::~EditorState()
{

}

bool EditorState::eventHandler()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	Vec2 mousePos = Vec2(mouseX, mouseY);
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

			if (Collision::pointBoxCollision(mousePos, genMapBtn->getPosition(), genMapBtn->getDimensions()))
			{
				genMapBtn->setHover(true);
			}
			else {
				genMapBtn->setHover(false);
			}
			

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


			if (Collision::pointBoxCollision(mousePos, testMapBtn->getPosition(), testMapBtn->getDimensions()))
			{
				testMapBtn->setHover(true);
			}
			else {
				testMapBtn->setHover(false);
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
				if (mm->mouseCollide(mouseX, mouseY))
				{
					Vec2 tmp = mm->changeRoom(mouseX, mouseY);
					if (tmp.x != -1)
					{
						randFloor->setCurRoomPos(tmp);
						currentMap = randFloor->getCurMap();
					}
				}

				if (Collision::pointBoxCollision(Vec2(mouseX, mouseY), genMapBtn->getPosition(), genMapBtn->getDimensions()))
				{
					genBtnDwn = true;
					createNewMap();
				}


				if (Collision::pointBoxCollision(mousePos, numRoomsSlider->getPosition(), numRoomsSlider->getDimensions()))
				{
					numRoomsSlider->changeValue(mousePos);
					mouseDownSlider = true;

					Texture *nTex = new Texture(platform->getRenderer(), Utility::intToString(numRoomsSlider->getValue()), font, { 255,255,255 });
					Texture *oldTex = numRoomsText;

					numRoomsText = nTex;

					delete oldTex;
				}




				if (Collision::pointBoxCollision(mousePos, randFloor->getPosition(), randFloor->getDimensions()))
				{
					if (tileSelection->getTypeSelected() == "A")
					{
						randFloor->getCurMap()->changeTileType("O", mousePos / 32, tileTypeSelected, ttmng);
					}
					else if (tileSelection->getTypeSelected() == "B") {
						randFloor->getCurMap()->changeTileType("B", mousePos / 32, tileTypeSelected, ttmng);
					}
					
					
				}

				if (Collision::pointBoxCollision(mousePos, tileSelection->getPosition(), tileSelection->getDimensions()))
				{
					tileSelection->changeSelectedTile(mousePos);
					tileTypeSelected = tileSelection->getSelectedTile();
				}


				if (Collision::pointBoxCollision(mousePos, bgLayerBtn->getPosition(), bgLayerBtn->getDimensions()))
				{
					bgLayerBtn->setSelected(true);
					objLayerBtn->setSelected(false);
					tileSelection->setTypeSelected("B");
					tileTypeSelected = tileSelection->getSelectedTile();
				}

				if (Collision::pointBoxCollision(mousePos, objLayerBtn->getPosition(), bgLayerBtn->getDimensions()))
				{
					bgLayerBtn->setSelected(false);
					objLayerBtn->setSelected(true);
					tileSelection->setTypeSelected("A");
					tileTypeSelected = tileSelection->getSelectedTile();
				}



				if (Collision::pointBoxCollision(mousePos, testMapBtn->getPosition(), testMapBtn->getDimensions()))
				{
					playMap = true;
				}

			break;
				

			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouseDownSlider = false;
			break;
			}
		break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym)
			{
				//pressing a key
			case SDLK_ESCAPE:
				//do same as quit
				return true;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (events.key.keysym.sym)
			{
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
		stateManager->changeState(new GameState(stateManager, platform, ttmng, cmng, mmng, randFloor));
	}
}

void EditorState::render()
{

	mm->render(platform->getRenderer());
	randFloor->getCurMap()->render(platform->getRenderer());
	//room grid
	for (int i = 0; i < 21; i ++)
	{
		white->pushToScreen(platform->getRenderer(), Vec2(i * 32, 0), Vec2(1, 15*32));
	}
	for (int j = 0; j < 16; j++)
	{
		white->pushToScreen(platform->getRenderer(), Vec2(0, j*32), Vec2(20*32,1));
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

	genMapBtn->render(platform->getRenderer());

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



	bgLayerBtn->render(platform->getRenderer());
	objLayerBtn->render(platform->getRenderer());


	layerText->renderText(platform->getRenderer(), Vec2(670, 400), Vec2(50, 20));
	bgText->renderText(platform->getRenderer(), Vec2(690, 420), Vec2(100,20));
	objText->renderText(platform->getRenderer(), Vec2(820, 420), Vec2(60, 20));
	

	testMapBtn->render(platform->getRenderer());
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
	testMapBtn = new Button(testMapTexture, Vec2(320, 480), Vec2(100, 46), Vec2(0, 0));



	font = TTF_OpenFont("res/fonts/ariblk.ttf", 20);
	numRoomsText = new Texture(platform->getRenderer(), Utility::intToString(numRoomsSlider->getValue()), font, { 255,255,255 });


	//tile selection
	tileSelection = new TileSelection(Vec2(670, 300), Vec2(8, 4), ttmng, white);
	tileTypeSelected = "XX";
	tileSelection->setTypeSelected("B");



	//layer
	Texture *btn = new Texture("res/img/buttons/selectBtn.png", platform->getRenderer());

	bgLayerBtn = new Button(btn, Vec2(795, 420), Vec2(16, 16), Vec2(0, 0));
	objLayerBtn = new Button(btn, Vec2(885, 420), Vec2(16, 16), Vec2(0, 0));
	bgLayerBtn->setSelected(true);


	layerText = new Texture(platform->getRenderer(), "Layer: ", font, { 255,255,255 });
	bgText = new Texture(platform->getRenderer(), "Background: ", font, { 255,255,255 });
	objText = new Texture(platform->getRenderer(), "Object: ", font, { 255,255,255 });





	
}

void EditorState::unload()
{

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

void  EditorState::exportLevelData()
{

}

void EditorState::importLevelData()
{

}

/*
HRESULT BasicFileOpen()
{
	// CoCreate the File Open Dialog object.
	IFileDialog *pfd = NULL;

	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pfd));
	if (SUCCEEDED(hr))
	{
		// Create an event handling object, and hook it up to the dialog.
		IFileDialogEvents *pfde = NULL;
		hr = CDialogEventHandler_CreateInstance(IID_PPV_ARGS(&pfde));
		if (SUCCEEDED(hr))
		{
			// Hook up the event handler.
			DWORD dwCookie;
			hr = pfd->Advise(pfde, &dwCookie);
			if (SUCCEEDED(hr))
			{
				// Set the options on the dialog.
				DWORD dwFlags;

				// Before setting, always get the options first in order 
				// not to override existing options.
				hr = pfd->GetOptions(&dwFlags);
				if (SUCCEEDED(hr))
				{
					// In this case, get shell items only for file system items.
					hr = pfd->SetOptions(dwFlags | FOS_FORCEFILESYSTEM);
					if (SUCCEEDED(hr))
					{
						// Set the file types to display only. 
						// Notice that this is a 1-based array.
						hr = pfd->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
						if (SUCCEEDED(hr))
						{
							// Set the selected file type index to Word Docs for this example.
							hr = pfd->SetFileTypeIndex(INDEX_WORDDOC);
							if (SUCCEEDED(hr))
							{
								// Set the default extension to be ".doc" file.
								hr = pfd->SetDefaultExtension(L"doc;docx");
								if (SUCCEEDED(hr))
								{
									// Show the dialog
									hr = pfd->Show(NULL);
									if (SUCCEEDED(hr))
									{
										// Obtain the result once the user clicks 
										// the 'Open' button.
										// The result is an IShellItem object.
										IShellItem *psiResult;
										hr = pfd->GetResult(&psiResult);
										if (SUCCEEDED(hr))
										{
											// We are just going to print out the 
											// name of the file for sample sake.
											PWSTR pszFilePath = NULL;
											hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH,
												&pszFilePath);
											if (SUCCEEDED(hr))
											{
												TaskDialog(NULL,
													NULL,
													L"CommonFileDialogApp",
													pszFilePath,
													NULL,
													TDCBF_OK_BUTTON,
													TD_INFORMATION_ICON,
													NULL);
												CoTaskMemFree(pszFilePath);
											}
											psiResult->Release();
										}
									}
								}
							}
						}
					}
				}
				// Unhook the event handler.
				pfd->Unadvise(dwCookie);
			}
			pfde->Release();
		}
		pfd->Release();
	}
	return hr;
}*/