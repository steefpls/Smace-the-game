//  Module:             Gameplay Programming
//  Assignment1:        Ships and Shapes
//  Student Name:       Steven Koe
//  Student Number:     S10181536D
//  Student Name:       Jedidiah Wong
//  Student Number:     S10178790F

#ifndef _MISSILE_H                 // Prevent multiple definitions if this 
#define _MISSILE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"

#include "constants.h"


namespace missileNS
{
	//Location handling
	const int WIDTH = 150;                   // image width
	const int HEIGHT = 200;                  // image height
	static int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	static int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

	//2d Rotation
	static float ROTATION_RATE = 0.0f;		    // degrees per second
	static float ROTATION_ACC_RATE = 450.0f;   //degrees per second per second
	static float ROTATION_DRAG = 400.0f;	//degrees drag per second
	static float MAX_ROTATION_RATE = 240.0f;	 // degrees per second

	
	//2d Movement
	static float X_SPEED = 0.0f;                // pixels per second
	static float Y_SPEED = 0.0f;                // pixels per second
	static float X_ACC = 2000.0f;			//pixels per second per second
	static float Y_ACC = 2000.0f;			//pixels per second per second
	static float DRAG = 98 / 100;			//air resistance (IK its in space but stfu)
	const float MASS = 300.0f;              // mass
	const float MAX_VELOCITY = 2000.0f;		//max speed 
	//Textures
	const int   TEXTURE_COLS = 1;           // texture has 2 columns
	const int   MISSILE_START_FRAME = 0;      // ship1 starts at frame 0
	const int   MISSILE_END_FRAME = 0;        // ship1 animation frames 0,1,2,3
	const float MISSILE_ANIMATION_DELAY = 0.2f;    // time between frames
	static float SCALE = 0.125;			//ship scale

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
	float xacc = missileNS::X_ACC;
	float yacc = missileNS::Y_ACC;

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