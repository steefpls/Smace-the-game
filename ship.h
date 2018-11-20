#ifndef _SHIP_H                 // Prevent multiple definitions if this 
#define _SHIP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace shipNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	static int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	static int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	static float ROTATION_RATE = 0;		    // degrees per second
	static float ROTATION_ACC_RATE = 100 * PI / 180;   //degrees per second per second
	static float ROTATION_DRAG = 90 / 100;	//percentage drag per second
	static float X_SPEED = 0;                // pixels per second
	static float Y_SPEED = 0;                // pixels per second
	static float X_ACC = 300;			//pixels per second per second
	static float Y_ACC = 300;			//pixels per second per second
	static float DRAG = 99 / 100;			//air resistance (IK its in space but stfu)
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 2;           // texture has 2 columns
	const int   SHIP1_START_FRAME = 0;      // ship1 starts at frame 0
	const int   SHIP1_END_FRAME = 3;        // ship1 animation frames 0,1,2,3
	const int   SHIP2_START_FRAME = 8;      // ship2 starts at frame 8
	const int   SHIP2_END_FRAME = 11;       // ship2 animation frames 8,9,10,11
	const float SHIP_ANIMATION_DELAY = 0.2f;    // time between frames
	const int   SHIELD_START_FRAME = 24;    // shield start frame
	const int   SHIELD_END_FRAME = 27;      // shield end frame
	const float SHIELD_ANIMATION_DELAY = 0.1f; // time between frames
}

// inherits from Entity class
class Ship : public Entity
{
private:
	bool    shieldOn;
	Image   shield;
public:
	// constructor
	Ship();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void damage(WEAPON);
};
#endif