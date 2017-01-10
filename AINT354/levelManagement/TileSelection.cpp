#include "TileSelection.h"


TileSelection::TileSelection(Vec2 pos, Vec2 tilesWH, TileTypeManager *ttmng, Texture *white, Texture *grey) : ScreenElement(pos, Vec2(tilesWH.x*32, tilesWH.y*32))
{

	outline = white;
	grid = grey;
	outlinePos = pos;
	std::unordered_map<std::string, std::vector<TileType*>> tileTypes = ttmng->getTileTypesVector();

	tilesXY = tilesWH;


	std::string type = "O";
	int ttSize = tileTypes[type].size();

	tileSize = Vec2(32, 32);

	int c = 1;

	for (int i = 0; i < tilesWH.y; i++)
	{
		for (int j = 0; j < tilesWH.x; j++)
		{
			if (c < ttSize)
			{
				Vec2 spritePos;
				Tile *t = new Tile(Vec2(pos.x+(j*tileSize.x), pos.y + (i*tileSize.y)), tileSize, tileTypes[type][c]);

				selectionTiles[type].push_back(t);

				c++;
			}
			else {
				break;
			}
		}
	}

	type = "B";
	ttSize = tileTypes[type].size();
	c = 1;
	for (int i = 0; i < tilesWH.y; i++)
	{
		for (int j = 0; j < tilesWH.x; j++)
		{
			if (c < ttSize)
			{
				Vec2 spritePos;
				Tile *t = new Tile(Vec2(pos.x + (j*tileSize.x), pos.y + (i*tileSize.y)), tileSize, tileTypes[type][c]);

				selectionTiles[type].push_back(t);

				c++;
			}
			else {
				break;
			}
		}
	}



	typeSelected = "B";
}

TileSelection::~TileSelection()
{

}


void TileSelection::update(float dt)
{

}

void TileSelection::render(SDL_Renderer* renderer)
{
	//render tiles
	for (int i = 0; i < selectionTiles[typeSelected].size(); i++)
	{
		selectionTiles[typeSelected][i]->render(renderer);
	}
	//render grid
	for (int i = 0; i < tilesXY.x + 1; i++)
	{
		grid->pushToScreen(renderer, Vec2((i * 32) + pos.x, pos.y), Vec2(1.0f, tilesXY.y * 32));
	}
	for (int j = 0; j < tilesXY.y + 1; j++)
	{
		grid->pushToScreen(renderer, Vec2(pos.x, j * 32 + pos.y), Vec2(tilesXY.x * 32, 1.0f));
	}

	
	//render sqaure to show what user has selected
	if (typeSelected != "C")
	{
		outline->pushToScreen(renderer, outlinePos, Vec2(tileSize.x, 1.0f));
		outline->pushToScreen(renderer, outlinePos + Vec2(0.0f, tileSize.y), Vec2(tileSize.x, 1.0f));
		outline->pushToScreen(renderer, outlinePos + Vec2(tileSize.x, 0.0f), Vec2(1.0f, tileSize.y));
		outline->pushToScreen(renderer, outlinePos, Vec2(1.0f, tileSize.y));
	}
}

void TileSelection::changeSelectedTile(Vec2 mousePos)
{
	if (typeSelected == "O" || typeSelected == "B")
	{
		for (int i = 0; i < selectionTiles[typeSelected].size(); i++)
		{
			if (Collision::pointBoxCollision(mousePos, selectionTiles[typeSelected][i]->getPosition(), selectionTiles[typeSelected][i]->getDimensions()))
			{
				selectedTile = selectionTiles[typeSelected][i]->getTileTypeID();
				outlinePos = selectionTiles[typeSelected][i]->getPosition();
			}
		}
	}
	else if (typeSelected == "C")
	{
		selectedTile = "#";
		outlinePos = NULL;
	}
	
}

std::string TileSelection::getSelectedTile()
{
	return selectedTile;
}

void TileSelection::setTypeSelected(std::string type)
{
	typeSelected = type;
	if (type != "C")
	{
		selectedTile = selectionTiles[typeSelected][0]->getTileTypeID();
		outlinePos = selectionTiles[typeSelected][0]->getPosition();
	}
}

std::string TileSelection::getTypeSelected()
{
	return typeSelected;
}