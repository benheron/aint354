#include "MiniMap.h"

MiniMap::MiniMap(SDL_Renderer* renderer)
{
	tmpTexture = new Texture(renderer, 255, 0, 0);

	roomOnTexture = new Texture(renderer, 255, 255, 255);

	mapIcon = new Texture("res/img/mapIcon.png", renderer);

}

MiniMap::~MiniMap()
{

}

void MiniMap::buildMiniMap(RandMap *mapFloor)
{
	mf = mapFloor;
	std::vector<std::vector<MapRoom*>> tmpR = mapFloor->getMap();
	curRoomPos = mapFloor->getCurRoomPos();

	Vec2 miniMapPos = Vec2(700, 50);
	Vec2 miniMapDimensions = Vec2(20, 15);


	for (int i = 0; i < tmpR.size(); i++)
	{
		std::vector<int> tmp;
		map.push_back(tmp);

		std::vector<MiniMapIcon*> tmp2;
		map2.push_back(tmp2);
		for (int j = 0; j < tmpR[0].size(); j++)
		{
			if (tmpR[i][j]->exists)
			{
				map[i].push_back(1);
				map2[i].push_back(new MiniMapIcon(mapIcon, Vec2(miniMapDimensions.x*i, miniMapDimensions.y *j) + miniMapPos, miniMapDimensions, Vec2(0,0), miniMapDimensions, true));
			}
			else {
				map[i].push_back(0);
				map2[i].push_back(new MiniMapIcon(mapIcon, Vec2(miniMapDimensions.x*i, miniMapDimensions.y *j) + miniMapPos, miniMapDimensions, Vec2(0, 0), miniMapDimensions, false));
			}
		}
	}


	map2[4][4]->setOccupied(true);

	
}

void MiniMap::update(float dt)
{
	map2[curRoomPos.x][curRoomPos.y]->setOccupied(false);
	curRoomPos = mf->getCurRoomPos();
	map2[curRoomPos.x][curRoomPos.y]->setOccupied(true);
}

void MiniMap::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j] == 1)
			{
			//	mapIcon->pushToScreen(renderer, Vec2(700 + (i * 20), 50 + (j * 15)), Vec2(20, 15));
			}
			
		}
	}


	//tmpTexture->pushToScreen(renderer, Vec2(800, 50), 20);
	//roomOnTexture->pushToScreen(renderer, Vec2(curRoomPos.x*20, curRoomPos.y*15) + Vec2(700, 50), Vec2(20, 15));



	for (int i = 0; i < map2.size(); i++)
	{
		for (int j = 0; j < map2[0].size(); j++)
		{
			if (map2[i][j]->getExists())
			{
				map2[i][j]->render(renderer);
			}
		}
	}
}