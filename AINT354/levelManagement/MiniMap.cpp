#include "MiniMap.h"
#include "../Utility.h"
#include "../Collision.h"

MiniMap::MiniMap(SDL_Renderer* renderer, int m)
{
	mapIcon = new Texture("res/img/mapIcon.png", renderer);
	mode = m;
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

	dimensions.x = miniMapDimensions.x*tmpR.size();
	dimensions.y = miniMapDimensions.y*tmpR[0].size();


	for (int i = 0; i < tmpR.size(); i++)
	{
		std::vector<MiniMapIcon*> tmp2;
		map.push_back(tmp2);
		for (int j = 0; j < tmpR[0].size(); j++)
		{
			if (tmpR[i][j]->getExists())
			{
				map[i].push_back(new MiniMapIcon(mapIcon, Vec2(miniMapDimensions.x*i, miniMapDimensions.y *j) + pos, miniMapDimensions, Vec2(0,0), miniMapDimensions, true));
			}
			else {
				map[i].push_back(new MiniMapIcon(mapIcon, Vec2(miniMapDimensions.x*i, miniMapDimensions.y *j) + pos, miniMapDimensions, Vec2(0, 0), miniMapDimensions, false));
			}
		}
	}


	map[curRoomPos.x][curRoomPos.y]->setOccupied(true);

	Utility::log(Utility::I, "PosX: " + Utility::floatToString(pos.x) + " PosY: " + Utility::floatToString(pos.y));
	Utility::log(Utility::I, "DimensionsX: " + Utility::floatToString(dimensions.x) + " DimensionsY: " + Utility::floatToString(dimensions.y));
}

void MiniMap::update(float dt)
{
	/*map2[curRoomPos.x][curRoomPos.y]->setOccupied(false);
	curRoomPos = mf->getCurRoomPos();
	map2[curRoomPos.x][curRoomPos.y]->setOccupied(true);*/

	Vec2 crp = mf->getCurRoomPos();
	if (crp != curRoomPos)
	{
		map[curRoomPos.x][curRoomPos.y]->setOccupied(false);
		curRoomPos = crp;
		map[curRoomPos.x][curRoomPos.y]->setOccupied(true);
	}
}

void MiniMap::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j]->getExists())
			{
				map[i][j]->render(renderer);
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

Vec2 MiniMap::changeRoom(int mouseX, int mouseY)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j]->getExists())
			{
				/*if (map[i][j]->mouseCollide(mouseX, mouseY))
				{*/
				if (Collision::pointBoxCollision(Vec2(mouseX, mouseY), map[i][j]->getPosition(), map[i][j]->getDimensions()))
				{
					if (Vec2(i, j) != curRoomPos)
					{
						map[curRoomPos.x][curRoomPos.y]->setOccupied(false);
						curRoomPos = Vec2(i,j);
						map[i][j]->setOccupied(true);
						return Vec2(i, j);
					}
				}
			}
		}
	}
	return Vec2(-1);
}

