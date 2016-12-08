#include "EditorState.h"
#include "../Utility.h"

EditorState::EditorState(StateManager* manager, Platform *platform)
	: State(manager, platform)
{
	stateName = "EditorState";
}

EditorState::~EditorState()
{

}

bool EditorState::eventHandler()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_MOUSEMOTION:
			//while mouse is moving
			if (mm->mouseCollide(mouseX, mouseY))
			{
				Utility::log(Utility::I, "Collided at: " + Utility::intToString(mouseX) + ", " + Utility::intToString(mouseY));
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
		white->pushToScreen(platform->getRenderer(), Vec2(700+(i * 20), 50), Vec2(1, 10 * 15));
	}
	for (int j = 0; j < 11; j++)
	{
		white->pushToScreen(platform->getRenderer(), Vec2(700, 50+(j * 15)), Vec2(10 * 20, 1));
	}

	
	
}

void EditorState::load()
{
	//generate-map button

	//make new room
	//provide tiles to change the room
	//empty grid with some coloured background
	white = new Texture(platform->getRenderer(), 255, 255, 255);

	////////////////////////
	//testing editor modes//
	////////////////////////

	TileTypeManager* tmp = new TileTypeManager("res/txt/tiles.txt", platform->getRenderer());
	//Creature + character loading test
	CreatureManager* cmtmp = new CreatureManager("res/txt/creatures.txt", "res/txt/characters.txt", platform->getRenderer());
	//load map
	MapManager *mapmng = new MapManager("res/txt/map1.txt", tmp, cmtmp);
	mapmng->loadMapData("res/txt/map2.txt", tmp, cmtmp);
	mapmng->loadMapData("res/txt/map3.txt", tmp, cmtmp);
	mapmng->loadMapData("res/txt/map4.txt", tmp, cmtmp);
	mapmng->loadMapData("res/txt/map5.txt", tmp, cmtmp);
	mapmng->loadMapData("res/txt/map6.txt", tmp, cmtmp);
	mapmng->loadMapData("res/txt/map7.txt", tmp, cmtmp);
	mapmng->loadMapData("res/txt/map8.txt", tmp, cmtmp);


	randFloor = new RandMap(mapmng, tmp, cmtmp);

	currentMap = randFloor->getCurMap();

	mm = new MiniMap(platform->getRenderer(), 1);
	mm->buildMiniMap(randFloor, Vec2(700, 50));
	
}

void EditorState::unload()
{

}