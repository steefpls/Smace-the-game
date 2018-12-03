#ifndef _MISSILE_H                 // Prevent multiple definitions if this 
#define _MISSILE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"

#include "constants.h"


namespace missileNS
{
	//Location handling
	const int WIDTH = 300;                   // image width
	const int HEIGHT = 1599;                  // image height
	static int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	static int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

	//2d Rotation
	static float ROTATION_RATE = 0.0f;		    // degrees per second
	static float ROTATION_ACC_RATE = 450.0f;   //degrees per second per second
	static float ROTATION_DRAG = 400.0f;	//degrees drag per second
	static float MAX_ROTATION_RATE = 240.0f;	 // degrees per second

	
	//2d Movement
	static float X_SPEED = 100.0f;                // pixels per second
	static float Y_SPEED = 100.0f;                // pixels per second
	static float X_ACC = 40000.0f;			//pixels per second per second
	static float Y_ACC = 40000.0f;			//pixels per second per second
	static float DRAG = 98 / 100;			//air resistance (IK its in space but stfu)
	const float MASS = 300.0f;              // mass
	const float MAX_VELOCITY = 1000;
	//Textures
	const int   TEXTURE_COLS = 1;           // texture has 2 columns
	const int   MISSILE_START_FRAME = 0;      // ship1 starts at frame 0
	const int   MISSILE_END_FRAME = 0;        // ship1 animation frames 0,1,2,3
	//const int   SHIP2_START_FRAME = 8;      // ship2 starts at frame 8
	//const int   SHIP2_END_FRAME = 11;       // ship2 animation frames 8,9,10,11
	const float MISSILE_ANIMATION_DELAY = 0.2f;    // time between frames
	//const int   SHIELD_START_FRAME = 24;    // shield start frame
	//const int   SHIELD_END_FRAME = 27;      // shield end frame
	//const float SHIELD_ANIMATION_DELAY = 0.1f; // time between frames
	static float SCALE = 0.05;			//ship scale

	//Timers
	const float MAX_DASH_TIMER = 3.0f;
	static float DASH_TIMER = 1.0f;
	static bool CAN_DASH = false;
	static float BOOST_AMT = 400; //pixels per second

	//Arbritrary values
	static float DAMAGE_MULTIPLIER = 1.0;
	const float DAMAGE = 500.0f;
}

// inherits from Entity class
class Missile : public Entity
{
private:
	//bool    shieldOn;
	//Image   shield;
public:
	// constructor
	Missile();

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
#endif _MISSILE_H