
#ifndef _BULLET1_H                 // Prevent multiple definitions if this 
#define _BULLET1_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "ship.h"
#include "entity.h"
#include "constants.h"

namespace bullet1NS
{
	//Location handling
	const int WIDTH = 1280;                   // image width
	const int HEIGHT = 1280;                  // image height
	static int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	static int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

	//2d Rotation
	static float ROTATION_RATE = 0.0f;		    // degrees per second
	static float ROTATION_ACC_RATE = 250.0f;   //degrees per second per second
	static float ROTATION_DRAG = 200.0f;	//degrees drag per second
	static float MAX_ROTATION_RATE = 240.0f;	 // degrees per second

	//2d Movement
	static float X_SPEED = 0.0f;                // pixels per second
	static float Y_SPEED = 0.0f;                // pixels per second
	static float X_ACC = 300.0f;			//pixels per second per second
	static float Y_ACC = 300.0f;			//pixels per second per second

	const float MASS = 300.0f;              // mass

	//Textures
	const int   TEXTURE_COLS = 1;           // texture has 1 column
	const int   BULLET1_START_FRAME = 0;      // bullet1 starts at frame 0
	const int   BULLET1_END_FRAME = 0;        // bullet1 animation frames 0,1,2,3

	const float BULLET1_ANIMATION_DELAY = 0.2f;    // time between frames

}

// inherits from Entity class
class Bullet : public Entity
{
private:
	Ship	ship;
	Image   bullet;
public:
	// constructor
	Bullet();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
};
#endif