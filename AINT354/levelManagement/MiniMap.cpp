#include "MiniMap.h"

MiniMap::MiniMap(SDL_Renderer* renderer)
{
	tmpTexture = new Texture(renderer, 255, 0, 0);

	roomOnTexture = new Texture(renderer, 255, 255, 255);
}

MiniMap::~MiniMap()
{

}

void MiniMap::buildMiniMap(RandMap *mapFloor)
{
	mf = mapFloor;
	std::vector<std::vector<MapRoom*>> tmpR = mapFloor->getMap();
	curRoomPos = mapFloor->getCurRoomPos();


	for (int i = 0; i < tmpR.size(); i++)
	{
		std::vector<int> tmp;
		map.push_back(tmp);
		for (int j = 0; j < tmpR[0].size(); j++)
		{
			if (tmpR[i][j]->exists)
			{
				map[i].push_back(1);
			}
			else {
				map[i].push_back(0);
			}
		}
	}


	
}

void MiniMap::update(float dt)
{
	curRoomPos = mf->getCurRoomPos();
}

void MiniMap::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j] == 1)
			{
				tmpTexture->pushToScreen(renderer, Vec2(800 + (i * 20), 50 + (j * 20)), 20);
			}
			
		}
	}


	//tmpTexture->pushToScreen(renderer, Vec2(800, 50), 20);
	roomOnTexture->pushToScreen(renderer, (curRoomPos*20) + Vec2(800, 50), 20);
}