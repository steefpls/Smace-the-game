#ifndef _SHIP_H                 // Prevent multiple definitions if this 
#define _SHIP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "missile.h"
#include "bullet.h"
#include "mine.h"
using namespace std;
#include <iostream>
#include <vector>

namespace shipNS
{
	//Location handling
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	static int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	static int Y = GAME_HEIGHT / 2 - HEIGHT / 2;

	//2d Rotation
	static float ROTATION_RATE = 0.0f;		    // degrees per second
	static float ROTATION_ACC_RATE = 450.0f ;   //degrees per second per second
	static float ROTATION_DRAG = 800.0f ;	//degrees drag per second
	static float MAX_ROTATION_RATE = 240.0f ;	 // degrees per second
	const float ROTATION_RATE_CAP = 3000.0f;	//Max Rotation Cap

	//2d Movement
	static float X_SPEED = 0.0f;            // pixels per second
	static float Y_SPEED = 0.0f;            // pixels per second
	
	const float ORIGINAL_X = 400.0f;
	const float ORIGINAL_Y = 400.0f;		//Original acceleration

	static float BOOSTED_X = 800.0f;
	static float BOOSTED_Y = 800.0f;		//Boosted speed
	static float X_ACC = ORIGINAL_X;			//pixels per second per second
	static float Y_ACC = ORIGINAL_Y;			//pixels per second per second

	static float DRAG = 98 / 100;			//air resistance (IK its in space but stfu)
	const float MASS = 300.0f;              // mass

	//Textures
	const int   TEXTURE_COLS = 2;           // texture has 2 columns
	const int   SHIP_START_FRAME = 0;      // ship1 starts at frame 0
	const int   SHIP_END_FRAME = 3;        // ship1 animation frames 0,1,2,3
	const float SHIP_ANIMATION_DELAY = 0.2f;    // time between frames
	const int   SHIELD_START_FRAME = 24;    // shield start frame
	const int   SHIELD_END_FRAME = 27;      // shield end frame
	const float SHIELD_ANIMATION_DELAY = 0.1f; // time between frames
	static float SCALE = 1.4;			//ship scale

	//Timers
	const float MAX_DASH_TIMER = 2.0f;
	static float DASH_TIMER = 1.0f;
	static bool CAN_DASH = false;
	static float BOOST_AMT = 400; //pixels per second

	const float MAX_MISSILE_TIMER = 3.0f;
	static float MISSILE_TIMER = 1.0f;
	static bool CAN_MISILE = false;

	const float MAX_BULLET_TIMER = 1.0f;
	static float BULLET_TIMER = 0.5f;
	static bool CAN_BULET = false;

	const float MAX_MINE_TIMER = 1.0f;
	static float MINE_TIMER = 0.5f;
	static bool CAN_MINE = false;

	//Arbritrary values
	static float DAMAGE_MULTIPLIER = 1.0;
	const int MAX_MINES = 20;
}

// inherits from Entity class
class Ship : public Entity
{
private:
	bool    shieldOn;
	Image   shield;
	//vector<Missile*> missileList;

public:
	// constructor
	Ship();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

	void topbottomrotatebounce();
	void leftrightrotatebounce();

	std::vector<Missile *> missileList;
	std::vector<Bullet *> bulletList;
	std::vector<Mine *> mineList;

	void spawnmissile();
	void spawnbullet();
	void spawnmine();

	void setMissileXY();
	void setBulletXY();
	void setMineXY();

	float getmissiletimer();
	float getbullettimer();
	float getminetimer();

	int getmaxmines();
	//keybinds
	char player1Right = 'D';
	char player1Left = 'A';
	char player1Up = 'W';
	char player1Down = 'S';

	float RotationRate = shipNS::ROTATION_RATE;
	float MaxRotationRate = shipNS::MAX_ROTATION_RATE;
	float RotationAccRate = shipNS::ROTATION_ACC_RATE;
	float RotationDrag = shipNS::ROTATION_DRAG;

	void dash();
	void boost(bool b);
};
#endif