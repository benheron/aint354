#include "PauseMenuState.h"
#include "MainMenuState.h"
#include "../Utility.h"
#include "../Collision.h"




PauseMenuState::PauseMenuState(StateManager* manager, Platform *platform, TileTypeManager *t, CreatureManager *c, MapManager *m)
	: State(manager, platform)
{
	stateName = "PauseMenuState";
	ttmng = t;
	cmng = c;
	mmng = m;
}

PauseMenuState::~PauseMenuState()
{

}

bool PauseMenuState::eventHandler()
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
			for (int i = 0; i < pauseMenuButtons.size(); i++)
			{
				if (Collision::pointBoxCollision(mousePos, pauseMenuButtons[i]->getPosition(), pauseMenuButtons[i]->getDimensions()))
				{
					if (!leftDown)
					{
						pauseMenuButtons[i]->setHover(true);
					}
					
				}
				else {
					pauseMenuButtons[i]->setHover(false);
					pauseMenuButtons[i]->setSelected(false);
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
				leftDown = true;
				for (int i = 0; i < pauseMenuButtons.size(); i++)
				{
					if (Collision::pointBoxCollision(mousePos, pauseMenuButtons[i]->getPosition(), pauseMenuButtons[i]->getDimensions()))
					{
						pauseMenuButtons[i]->setHover(false);
						pauseMenuButtons[i]->setSelected(true);
					}
					else {
						pauseMenuButtons[i]->setSelected(false);
					}
				}
				
				if (Collision::pointBoxCollision(mousePos, resumeBtn->getPosition(), resumeBtn->getDimensions()))
				{
					stateManager->popLastStateWithoutDelete();
					return false;
				}
/*

				if (Collision::pointBoxCollision(mousePos, quitMenuBtn->getPosition(), quitMenuBtn->getDimensions()))
				{
					leftDown = false;
					stateManager->popLastStateWithoutDelete();
					stateManager->changeState(new MainMenuState(stateManager, platform, ttmng, cmng, mmng, this));
					return false;
				}*/

				if (Collision::pointBoxCollision(mousePos, quitDesktopBtn->getPosition(), quitDesktopBtn->getDimensions()))
				{
					return true;
				}

				break;


			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT:
				leftDown = false;
				for (int i = 0; i < pauseMenuButtons.size(); i++)
				{
					if (Collision::pointBoxCollision(mousePos, pauseMenuButtons[i]->getPosition(), pauseMenuButtons[i]->getDimensions()))
					{
						pauseMenuButtons[i]->setSelected(false);
						pauseMenuButtons[i]->setHover(true);
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
				
				stateManager->popLastStateWithoutDelete();
				return false;
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

void PauseMenuState::update(float dt)
{
	
}

void PauseMenuState::render()
{

	mnubg->pushSpriteToScreen(platform->getRenderer(), 0, 0, Vec2(1920, 1080));
	for (int i = 0; i < pauseMenuButtons.size(); i++)
	{
		pauseMenuButtons[i]->render(platform->getRenderer());
	}
}

void PauseMenuState::load()
{
	resumeTexture = new Texture("res/img/buttons/resumeBtn.png", platform->getRenderer());
	quitToMenuTexture = new Texture("res/img/buttons/quitmenuBtn.png", platform->getRenderer());
	quitToDesktopTexture = new Texture("res/img/buttons/quitdesktopBtn.png", platform->getRenderer());
	mnubg = new Texture("res/img/menubg.png", platform->getRenderer());

	Utility::log(Utility::I, Utility::intToString(platform->getWindowSize().x));

	

	Vec2 btnSize = Vec2(320, 72);

	int xPos = (platform->getWindowSize().x/2) - (btnSize.x / 2);
	

	resumeBtn = new Button(resumeTexture, Vec2(xPos, 30), btnSize, Vec2(0,0));
	//quitMenuBtn = new Button(quitToMenuTexture, Vec2(xPos, 210), btnSize, Vec2(0, 0));
	quitDesktopBtn = new Button(quitToDesktopTexture, Vec2(xPos, 120), btnSize, Vec2(0, 0));
	


	pauseMenuButtons.push_back(resumeBtn);
	//pauseMenuButtons.push_back(quitMenuBtn);
	pauseMenuButtons.push_back(quitDesktopBtn);
}

void PauseMenuState::unload()
{

}