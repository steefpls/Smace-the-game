//  Module:             Gameplay Programming
//  Assignment1:        Ships and Shapes
//  Student Name:       Steven Koe
//  Student Number:     S10181536D
//  Student Name:       Jedidiah Wong
//  Student Number:     S10178790F

#ifndef _EXPLOSION_H
#define _EXPLOSION_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "audio.h"

namespace explosionNS
{
	//Location Handling
	const int WIDTH = 128;					//image width
	const int HEIGHT = 128;					//image height
	static float X = GAME_WIDTH / 2;
	static float Y = GAME_HEIGHT / 2;

	//Texture handling
	const int TEXTURE_COLS = 10;			//texture has 1 columns
	const int EXPLOSION_START_FRAME = 1;      // ship1 starts at frame 0
	const int EXPLOSION_END_FRAME = 10;        // ship1 animation frames 0,1,2,3
	const float EXPLOSION_ANIMATION_DELAY = 0.05;
	
	const float MASS = 1.0e14f;
	static bool ACTIVE = true;
	static float SCALE = 2;
	//const int COLLISION_RADIUS = 60 / 2;
	const float DAMAGE = 50.0f;
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