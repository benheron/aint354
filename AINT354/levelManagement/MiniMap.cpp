#include "MiniMap.h"

MiniMap::MiniMap(SDL_Renderer* renderer)
{
	mapIcon = new Texture("res/img/mapIcon.png", renderer);

}

MiniMap::~MiniMap()
{

}

void MiniMap::buildMiniMap(RandMap *mapFloor, Vec2 p)
{
	pos = p;
	mf = mapFloor;
	std::vector<std::vector<MapRoom*>> tmpR = mapFloor->getMap();
	curRoomPos = mapFloor->getCurRoomPos();

	Vec2 miniMapPos = Vec2(700, 50);
	Vec2 miniMapDimensions = Vec2(20, 15);

	dimensions = miniMapDimensions;


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
				map2[i].push_back(new MiniMapIcon(mapIcon, Vec2(miniMapDimensions.x*i, miniMapDimensions.y *j) + pos, miniMapDimensions, Vec2(0,0), miniMapDimensions, true));
			}
			else {
				map[i].push_back(0);
				map2[i].push_back(new MiniMapIcon(mapIcon, Vec2(miniMapDimensions.x*i, miniMapDimensions.y *j) + pos, miniMapDimensions, Vec2(0, 0), miniMapDimensions, false));
			}
		}
	}


	map2[curRoomPos.x][curRoomPos.y]->setOccupied(true);

	
}

void MiniMap::update(float dt)
{
	/*map2[curRoomPos.x][curRoomPos.y]->setOccupied(false);
	curRoomPos = mf->getCurRoomPos();
	map2[curRoomPos.x][curRoomPos.y]->setOccupied(true);*/

	Vec2 crp = mf->getCurRoomPos();
	if (crp != curRoomPos)
	{
		map2[curRoomPos.x][curRoomPos.y]->setOccupied(false);
		curRoomPos = crp;
		map2[curRoomPos.x][curRoomPos.y]->setOccupied(true);
	}
}

void MiniMap::render(SDL_Renderer* renderer)
{
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



bool MiniMap::mouseCollide(int mouseX, int mouseY)
{
	if (mouseX > pos.x &&
		mouseX < (pos.x + dimensions.x) &&
		mouseY > pos.y &&
		mouseY < (pos.y + dimensions.y))
	{
		return true;
	}
	return false;
}

