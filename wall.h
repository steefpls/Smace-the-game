#ifndef _WALL_H
#define _WALL_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace wallNS
{
	//Location Handling
	const int WIDTH = 32;					//image width
	const int HEIGHT = 32;					//image height
	static int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	static int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int TEXTURE_COLS = 2;			//texture has 2 columns
}

class Wall : public Entity 
{
private:
	int hp;

public:
	//constructor
	Wall();
	
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
};
#endif _WALL_H
