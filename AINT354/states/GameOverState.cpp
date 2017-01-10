#include "GameOverState.h"
#include "Gamestate.h"
#include "../Utility.h"
#include "../Collision.h"




GameOverState::GameOverState(StateManager* manager, Platform *platform, TileTypeManager *t, CreatureManager *c, MapManager *m, PauseMenuState *p)
	: State(manager, platform)
{
	stateName = "GameOverState";
	ttmng = t;
	cmng = c;
	mmng = m;
	pms = p;
}

GameOverState::~GameOverState()
{

}

bool GameOverState::eventHandler()
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
			for (int i = 0; i < gameOverButtons.size(); i++)
			{
				if (Collision::pointBoxCollision(mousePos, gameOverButtons[i]->getPosition(), gameOverButtons[i]->getDimensions()))
				{
					if (!leftDown)
					{
						gameOverButtons[i]->setHover(true);
					}

				}
				else {
					gameOverButtons[i]->setHover(false);
					gameOverButtons[i]->setSelected(false);
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
				for (int i = 0; i < gameOverButtons.size(); i++)
				{
					if (Collision::pointBoxCollision(mousePos, gameOverButtons[i]->getPosition(), gameOverButtons[i]->getDimensions()))
					{
						gameOverButtons[i]->setHover(false);
						gameOverButtons[i]->setSelected(true);
					}
					else {
						gameOverButtons[i]->setSelected(false);
					}
				}

				//play again button
				if (Collision::pointBoxCollision(mousePos, playagainBtn->getPosition(), playagainBtn->getDimensions()))
				{
					stateManager->changeState(new GameState(stateManager, platform, ttmng, cmng, mmng, new RandMap(mmng, ttmng, cmng, 9), 0, pms));
					return false;
				}

				//quit to main menu
				if (Collision::pointBoxCollision(mousePos, quitMenuBtn->getPosition(), quitMenuBtn->getDimensions()))
				{
					leftDown = false;
					stateManager->changeState(new MainMenuState(stateManager, platform, ttmng, cmng, mmng, pms));
					return false;
				}

				//quit to desktop
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
				for (int i = 0; i <gameOverButtons.size(); i++)
				{
					if (Collision::pointBoxCollision(mousePos, gameOverButtons[i]->getPosition(), gameOverButtons[i]->getDimensions()))
					{
						gameOverButtons[i]->setSelected(false);
						gameOverButtons[i]->setHover(true);
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

void GameOverState::update(float dt)
{

}

void GameOverState::render()
{
	for (int i = 0; i < gameOverButtons.size(); i++)
	{
		gameOverButtons[i]->render(platform->getRenderer());
	}

	int x = (platform->getWindowSize().x / 2) - 200;

	gameOver->pushSpriteToScreen(platform->getRenderer(), Vec2(x, 12), 0, Vec2(400, 150));
}

void GameOverState::load()
{
	gameOver = new Texture("res/img/gameOver.png", platform->getRenderer());
	playAgainTexture = new Texture("res/img/buttons/playagainBtn.png", platform->getRenderer());
	quitToMenuTexture = new Texture("res/img/buttons/quitmenuBtn.png", platform->getRenderer());
	quitToDesktopTexture = new Texture("res/img/buttons/quitdesktopBtn.png", platform->getRenderer());

	Utility::log(Utility::I, Utility::intToString(platform->getWindowSize().x));



	Vec2 btnSize = Vec2(320, 72);

	int xPos = (platform->getWindowSize().x / 2) - (btnSize.x / 2);


	playagainBtn = new Button(playAgainTexture, Vec2(xPos, 120), btnSize, Vec2(0, 0));
	quitMenuBtn = new Button(quitToMenuTexture, Vec2(xPos, 210), btnSize, Vec2(0, 0));
	quitDesktopBtn = new Button(quitToDesktopTexture, Vec2(xPos, 300), btnSize, Vec2(0, 0));



	gameOverButtons.push_back(playagainBtn);
	gameOverButtons.push_back(quitMenuBtn);
	gameOverButtons.push_back(quitDesktopBtn);
}

void GameOverState::unload()
{

}