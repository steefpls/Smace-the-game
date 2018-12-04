#ifndef _BLACKHOLE_H                 // Prevent multiple definitions if this 
#define _BLACKHOLE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"

#include "constants.h"


namespace blackholeNS
{
	//Location handling
	const int WIDTH = 256;                   // image width
	const int HEIGHT = 256;                  // image height
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
	const float MASS = 300.0f;              // mass
	const float MAX_VELOCITY = 40000.0f;		//max speed
	//Textures
	const int   TEXTURE_COLS = 5;           // texture has 2 columns
	const int   BLACKHOLE_START_FRAME = 0;      // ship1 starts at frame 0
	const int   BLACKHOLE_END_FRAME = 35;        // ship1 animation frames 0,1,2,3
	const float BLACKHOLE_ANIMATION_DELAY = 0.01f;    // time between frames
	static float SCALE = 1;			//ship scale

	//Arbritrary values
	static float DAMAGE_MULTIPLIER = 1.0;
	const float DAMAGE = 200.0f;
	const int MAX_BOUNCES = 3;
	static int BOUNCES = 0;
}

// inherits from Entity class
class Blackhole : public Entity
{
private:
	//bool    shieldOn;
	//Image   shield;
public:
	// constructor
	Blackhole();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	bool getdel();
	void setAngle(float a);
	float getDamage();


	//void damage(WEAPON);
};
#endif _BLACKHOLE_H
