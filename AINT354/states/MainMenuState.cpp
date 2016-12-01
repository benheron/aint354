#include "MainMenuState.h"
#include "../Utility.h"

MainMenuState::MainMenuState(StateManager* manager, Platform *platform)
	: State(manager, platform)
{
	stateName = "MainMenuState";
}

MainMenuState::~MainMenuState()
{
	delete buttonBgrRed;
	delete buttonBgrGreen;
	delete redPlay;
	delete greenEdit;
}

bool MainMenuState::eventHandler()
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{

		case SDL_MOUSEMOTION:
			
			break;

		case SDL_QUIT:
			return true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT:
				Utility::log(Utility::I, Utility::intToString(mouseX));
				if (redPlay->mouseCollide(mouseX, mouseY))
				{
					redDown = true;
					
				}

				if (greenEdit->mouseCollide(mouseX, mouseY))
				{
					greenDown = true;
				}
			break;

			}
			break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				//do same as quit
				return true;
				break;
				//temporary movement
			}
			break;
		case SDL_KEYUP:
			switch (events.key.keysym.sym)
			{
			default:
				Utility::log(Utility::I, Utility::intToString(events.key.keysym.sym));
				break;
			}
			break;
		}
	}
	return false;
}

void MainMenuState::update(float dt)
{
	if (redDown)
	{

		stateManager->changeState(new GameState(stateManager, platform));
	}

	if (greenDown)
	{
		//change to editor state
		//stateManager->changeState(new EditorState(stateManager, platform));
	}
}

void MainMenuState::render()
{
	redPlay->render(platform->getRenderer());
	greenEdit->render(platform->getRenderer());
}

void MainMenuState::load()
{

	buttonBgrRed  = new Texture(platform->getRenderer(), 255, 0, 0);

	buttonBgrGreen = new Texture(platform->getRenderer(), 0, 255, 0);


	//background
	redPlay = new Button(buttonBgrRed, Vec2(60, 40), Vec2(250, 115));

	greenEdit = new Button(buttonBgrGreen, Vec2(60, 260), Vec2(250, 115));

	//buttons
}

void MainMenuState::unload()
{
	
}