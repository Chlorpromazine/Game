#include "mapEditor.h"

mapEditor mapEditor::mapEditControl;

mapEditor::mapEditor()
{
	tileType = 1;
	tile = 0;
}

void mapEditor::drawMap(SDL_Surface* surface)
{
	Area::AreaControl.OnRender(surface, Camera::CameraControl.GetX(), Camera::CameraControl.GetY());
	SDL_Flip(surface);
}

void CApp::moveMap()
{
	if (moveUp)
		Camera::CameraControl.OnMove(0, moveMapSpeed);
	if (moveDown)
		Camera::CameraControl.OnMove(0, -moveMapSpeed);
	if (moveLeft)
		Camera::CameraControl.OnMove(moveMapSpeed, 0);
	if (moveRight)
		Camera::CameraControl.OnMove(-moveMapSpeed, 0);

}

void mapEditor::editTile()
{
	int mapXClick = (-Camera::CameraControl.GetX() + mLocX) / 16;
	int mapYClick = (-Camera::CameraControl.GetY() + mLocY) / 16;

	int IdX = mapXClick / mapWidth ;
	int IdY = mapYClick / mapHeight ;

	//todo: holdclick
	collision::cC.mapInfoCollision[mapXClick + mapYClick * mapWidth*mapPerAreaX] = tileType;
	if (IdX + IdY*mapPerAreaX >= 0 && mapXClick%mapWidth + mapYClick%mapHeight*mapWidth >= 0)
		Area::AreaControl.MapList[IdX + IdY*mapPerAreaX].modifyTileList(mapXClick%mapWidth + mapYClick%mapHeight*mapWidth, tile, tileType);
}

void mapEditor::changeTile(int type)
{
	tile = type;
}

void mapEditor::changeTileType(int type)
{
	tileType = type;
}

void mapEditor::writeMap()
{
	ofstream output;

}