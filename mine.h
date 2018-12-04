#ifndef _MINE_H
#define _MINE_H
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace mineNS
{
	//Location handling
	const int WIDTH = 900;                   // image width
	const int HEIGHT = 868;                  // image height
	static int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	static int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

	//2d Rotation
	static float ROTATION_RATE = 0.0f;		    // degrees per second
	static float ROTATION_ACC_RATE = 450.0f;   //degrees per second per second
	static float ROTATION_DRAG = 400.0f;	//degrees drag per second
	static float MAX_ROTATION_RATE = 240.0f;	 // degrees per second

	//2d Movement
	static float X_SPEED = 500.0f;                // pixels per second
	static float Y_SPEED = 500.0f;                // pixels per second
	static float X_ACC = 40000.0f;			//pixels per second per second
	static float Y_ACC = 40000.0f;			//pixels per second per second
	static float DRAG = 98 / 100;			//air resistance (IK its in space but stfu)
	const float MAX_VELOCITY = 40000.0f;		//max speed
	//Textures
	const int   TEXTURE_COLS = 1;           // texture has 2 columns
	const int   MINE_START_FRAME = 0;      // ship1 starts at frame 0
	const int   MINE_END_FRAME = 0;        // ship1 animation frames 0,1,2,3
	const float MINE_ANIMATION_DELAY = 0.2f;    // time between frames

	//Arbritrary values
	static float DAMAGE_MULTIPLIER = 1.0;
	const float DAMAGE = 200.0f;
	const int MAX_BOUNCES = 3;
	static int BOUNCES = 0;

	const float MASS = 1.0e14f;
	static bool ACTIVE = true;
	static float SCALE = 0.04;
	//const int COLLISION_RADIUS = 60 / 2;

	const double MAX_HP = 1000.0;			//wall maxhp
	static double HP = MAX_HP;				//wall hp
	static double HP_PERCENTAGE = (HP / MAX_HP) * 100.0;
}

class Mine : public Entity
{
protected:
	//int hp;

public:
	//constructor
	Mine();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	bool getdel();
	void setAngle(float a);
	float getDamage();

};
#endif _MINE_H
