#ifndef _WALL_H
#define _WALL_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace wallNS
{
	//Location Handling
	const int WIDTH = 60;					//image width
	const int HEIGHT = 60;					//image height
	static int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	static int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	
	//Texture handling
	const int TEXTURE_COLS = 4;			//texture has 1 columns
	const int WALL1_START_FRAME = 0;      // ship1 starts at frame 0
	const int WALL1_END_FRAME = 0;        // ship1 animation frames 0,1,2,3

	const float MASS = 1.0e14f;
	static bool ACTIVE = true;
	static float SCALE = 1;
	//const int COLLISION_RADIUS = 60 / 2;
	static double HP = 1000.0;				//wall hp
}

class Wall : public Entity 
{
protected:
	//int hp;

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
