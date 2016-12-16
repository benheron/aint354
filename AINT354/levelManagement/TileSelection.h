#pragma once

#include "../ScreenElement.h"
#include "TileTypeManager.h"
#include "Tile.h"
#include "../Texture.h"
#include "../Collision.h"

class TileSelection  : public ScreenElement {
public:

	TileSelection(Vec2 pos, Vec2 tilesWH,  TileTypeManager *ttmng, Texture *white);
	~TileSelection();

	void render(SDL_Renderer* renderer);

	void update(float dt);


	void changeSelectedTile(Vec2 mousePos);
	std::string getSelectedTile();


	void setTypeSelected(std::string type);

	std::string getTypeSelected();

protected:

	std::string selectedTile;
	std::unordered_map<std::string, std::vector<Tile*>> selectionTiles;

	Vec2 outlinePos;
	Texture *outline;

	Vec2 tileSize;

	std::string typeSelected;
};