#ifndef _EXPLOSION_H
#define _EXPLOSION_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace explosionNS
{
	//Location Handling
	const int WIDTH = 180;					//image width
	const int HEIGHT = 180;					//image height
	static float X = GAME_WIDTH / 2;
	static float Y = GAME_HEIGHT / 2;

	//Texture handling
	const int TEXTURE_COLS = 5;			//texture has 1 columns
	const int EXPLOSION_START_FRAME = 0;      // ship1 starts at frame 0
	const int EXPLOSION_END_FRAME = 6;        // ship1 animation frames 0,1,2,3

	//const float MASS = 1.0e14f;
	static bool ACTIVE = true;
	static float SCALE = 0.5;
	//const int COLLISION_RADIUS = 60 / 2;
}

class Explosion : public Entity
{
protected:
	//int hp;

public:
	//constructor
	Explosion();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

};
#endif 