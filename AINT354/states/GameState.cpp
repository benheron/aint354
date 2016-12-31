#include "GameState.h"
#include "../Utility.h"

GameState::GameState(StateManager* manager, Platform *platform, TileTypeManager *t, CreatureManager *c, MapManager *m, RandMap *map, int mode, PauseMenuState *p)
	: State(manager, platform)
{
	stateName = "GameState";
	ttmng = t;
	cmng = c;
	mmng = m;
	randFloor = map;
	this->mode = mode;
	pms = p;
}

GameState::~GameState()
{

}

bool GameState::eventHandler()
{
	//temporary input handling
	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{
		case SDL_QUIT:
			return true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (events.button.button)
			{
			case SDL_BUTTON_LEFT:
				Utility::log(Utility::I, "Clicking");
				Vec2 a = randFloor->getCurMap()->getPos();
				Utility::log(Utility::I, "Room X: " + Utility::intToString(a.x) + ", Room Y : " + Utility::intToString(a.y));
				
			}
			break;
		case SDL_KEYDOWN:
			switch (events.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				//do same as quit
				if (mode == 1)
				{
					stateManager->popLastState();
					return false;
				}
				else {
					stateManager->addState(pms);
					
					
					esc = true;
					return false;
				}
				break;
			//temporary movement
			case SDLK_UP:
				kUp = true;
				break;
			case SDLK_DOWN:
				kDown = true;
				break;
			case SDLK_LEFT:
				kLeft = true;
				break;
			case SDLK_RIGHT:
				kRight = true;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (events.key.keysym.sym)
			{
			case SDLK_p:
				particles->generateNewParticles();
				break;

				//temporary movement
			case SDLK_UP:
				kUp = false;
				break;
			case SDLK_DOWN:
				kDown = false;
				break;
			case SDLK_LEFT:
				kLeft = false;
				break;
			case SDLK_RIGHT:
				kRight = false;
				break;
			
			default:
				Utility::log(Utility::I, Utility::intToString(events.key.keysym.sym));
				break;
			}
			break;
		}
	}
	return false;
}

void GameState::update(float dt)
{
	//particles->update(dt);

	mm->update(dt);

	player->update(dt);
	bool changeFloor = false;

	//just some testing data for moving the player
	Vec2 curPos = player->getPosition();
	//Utility::log(Utility::I, "X: " + Utility::floatToString(curPos.x) + "Y: " + Utility::floatToString(curPos.y));
	Vec2 movement = Vec2(0);

	if (kLeft)
	{
		movement.x = -1;
	}
	if (kRight)
	{
		movement.x = 1;
	}

	if (kUp)
	{
		movement.y = -1;
	}

	if (kDown)
	{
		movement.y = 1;
	}

	//get normal of mom
	Vec2 normCurPos = movement.normalize();
	int speed = 7*60 *dt;

	Vec2 dir = normCurPos * speed;

	Vec2 newCurPosX = curPos;
	Vec2 newCurPosY = curPos;

	curPos.x += dir.x;

	//curPos += normCurPos * speed;

	Vec2 diff = normCurPos * speed;

	


	player->setPosition(curPos);

	if (int cm = currentMap->checkCollide(player))
	{
		Vec2 x = curPos;

		curPos -= diff;

		x.x = curPos.x;
		player->setPosition(x);



		//update current position
		curPos = x;

		if (cm == 2)
		{
			changeFloor = true;
		}
	}




	curPos.y += dir.y;

	player->setPosition(curPos);


	if (int cm = currentMap->checkCollide(player))
	{
		Vec2 y = curPos;

		curPos -= diff;
		y.y = curPos.y;

		player->setPosition(y);

		//update current position
		curPos = y;

		if (cm == 2)
		{
			changeFloor = true;
		}

	}















	//Utility::log(Utility::I, Utility::floatToString(speed * dt * 60));
	//Utility::log(Utility::I, "X: " + Utility::floatToString(normCurPos.x) + " Y: " + Utility::floatToString(normCurPos.y));
	//Utility::log(Utility::I, "X: " + Utility::floatToString(curPos.x) + " Y: " + Utility::floatToString(curPos.y));


	if (changeFloor)
	{
		if (mode == 0)
		{
			RandMap *newFloor = new RandMap(mmng, ttmng, cmng, 22);
			RandMap *oldFloor;

			oldFloor = randFloor;
			randFloor = newFloor;

			delete oldFloor;

			player->setPosition(Vec2(320, 240));

			MiniMap *newMiniMap = new MiniMap(platform->getRenderer(), 0);
			newMiniMap->buildMiniMap(randFloor, Vec2(700, 50));

			MiniMap *oldMiniMap = mm;
			delete oldMiniMap;

			mm = newMiniMap;

			currentMap = randFloor->getCurMap();
		}
		else if (mode == 1)
		{
			stateManager->popLastState();
			return;
		}


	}


	Vec2 cm = randFloor->getCurRoomPos();
	Vec2 cp = player->getPosition();

	if (curPos.x < -8)
	{
		randFloor->setCurRoomPos(Vec2((cm.x - 1), cm.y));
		player->setPosition(Vec2(624.0f, cp.y));
		currentMap = randFloor->getCurMap();
	}

	if (curPos.x > 632)
	{
		randFloor->setCurRoomPos(Vec2((cm.x + 1), cm.y));
		player->setPosition(Vec2(0.0f, cp.y));
		currentMap = randFloor->getCurMap();
	}

	if (curPos.y < -8) 
	{
		randFloor->setCurRoomPos(Vec2(cm.x, (cm.y-1)));
		player->setPosition(Vec2(cp.x, 464.0f));
		currentMap = randFloor->getCurMap();
	}

	if (curPos.y > 472)
	{
		randFloor->setCurRoomPos(Vec2(cm.x, (cm.y + 1)));
		player->setPosition(Vec2(cp.x, 0.0f));
		currentMap = randFloor->getCurMap();
	}


	for (int i = 0; i < randFloor->getCurMap()->getNumCreatures(); i++)
	{
		if (Collision::boxBoxCollision(player->getPosition(), player->getDimensions(), randFloor->getCurMap()->getCreatureByIndex(i)->getPosition(), randFloor->getCurMap()->getCreatureByIndex(i)->getDimensions()))
		{
			if (player->canDamage())
			{
				player->setHit(true);
				player->setCanDamage(false);
			}
			
		}
	}

	
		if (player->getHealth() <= 0)
		{
			if (mode == 0)
			{
				stateManager->changeState(new GameOverState(stateManager, platform, ttmng, cmng, mmng, pms));
			}
			else if (mode == 1) {
				stateManager->popLastState();
			}
		}
	
	


}

void GameState::render()
{
	//TMP FOR TESTING
	randFloor->getCurMap()->render(platform->getRenderer());
		
	player->render(platform->getRenderer());


	mm->render(platform->getRenderer());

	health->render(platform->getRenderer());

	
	
}

void GameState::load()
{

	

	currentMap = randFloor->getCurMap();




	//grab the player type
	playerType = cmng->getCharacterType("P0");
	//shove the type into the map to create a new player


	player = new Character(playerType->getTexture(), Vec2(320, 240), playerType);

	
	Utility::log(Utility::I, Utility::floatToString((player->getDimensions()).x));




	//Temp Particle Test
	particles = new ParticleSystem(Vec2(320, 240), new Texture(platform->getRenderer(), 255, 255, 255),
		50, Utility::newColour(0,0,0), Utility::newColour(255,255,255));
	particles->setSpeed(15);

	

	mm = new MiniMap(platform->getRenderer(), 0);
	mm->buildMiniMap(randFloor, Vec2(700, 15));


	Texture *healthTexture = new Texture("res/img/heart.png", platform->getRenderer());

	health = new HealthIcon(healthTexture, Vec2(5, 5), player);

	
}

void GameState::unload()
{
	delete particles;
	delete mm;
	delete player;
	delete health;

	if (mode == 0)
	{
		delete randFloor;
	}
}