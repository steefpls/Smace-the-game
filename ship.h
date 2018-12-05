#ifndef _SHIP_H                 // Prevent multiple definitions if this 
#define _SHIP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "missile.h"
#include "bullet.h"
#include "mine.h"
#include "blackhole.h"


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
	
	const float ORIGINAL_X_ACC = 400.0f;
	const float ORIGINAL_Y_ACC = 400.0f;		//Original acceleration

	static float BOOSTED_X_ACC = 800.0f;
	static float BOOSTED_Y_ACC = 800.0f;		//Boosted speed
	//static float X_ACC = ORIGINAL_X_ACC;			//pixels per second per second
	//static float Y_ACC = ORIGINAL_Y_ACC;			//pixels per second per second

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
	//static bool CAN_DASH = false;
	const float BOOST_AMT = 400; //pixels per second

	//Missile
	const float MAX_MISSILE_TIMER = 1.5f;
	static float MISSILE_TIMER = 0.5f;
	
	//bullet
	const float MAX_BULLET_TIMER = 0.75f;
	static float BULLET_TIMER = 0.5f;
	
	//Mine
	const float MAX_MINE_TIMER = 0.5f;
	static float MINE_TIMER = 0.5f;
	
	//blackhole
	const float MAX_BLACKHOLE_TIMER = 5.0f;
	static float BLACKHOLE_TIMER = 1.0f;
	
	//Arbritrary values
	static double DAMAGE_MULTIPLIER = 1.0;
	static float DAMAGE_RESISTANCE = 1000.0;
	const int MAX_MINES = 20;
	static int NO_OF_BULLETS_SHOT = 4;
	static double DEGREE_SPREAD = 20.0f;
	static float MAX_HP = 4000;
	static float HP = MAX_HP;

	const float LIFE_COUNT = 3.0f;
}

// inherits from Entity class
class Ship : public Entity
{
private:
	bool    shieldOn;
	Image   shield;
	//vector<Missile*> missileList;

protected:
	float dashTimer;
	float missileTimer;
	float bulletTimer;
	float mineTimer;
	float blackholeTimer;
	float damageResistance;
	float maxhp;

	int noOfBullets = shipNS::NO_OF_BULLETS_SHOT;
	float bulletDegreeSpread = shipNS::DEGREE_SPREAD;
	float lifeCount;


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
	std::vector<Blackhole *> blackholeList;	//list of black holes

	std::vector<Image *> lifeList;
	
	double getKnockBack();

	void spawnmissile();
	void spawnbullet();
	void spawnmine();
	void spawnblackhole();

	void setMissileXY();
	void setBulletXY(double b);
	void setMineXY();
	void setBlackholeXY();

	float getmissiletimer();
	float getbullettimer();
	float getminetimer();
	float getblackholetimer();

	float x_acc = shipNS::ORIGINAL_X_ACC;
	float y_acc = shipNS::ORIGINAL_Y_ACC;

	int getmaxmines();
	int getnoofbullets();
	float getDamageResistance();

	double getdegreespread();

	//keybinds
	char player1Right = 'D';
	char player1Left = 'A';
	char player1Up = 'W';
	char player1Down = 'S';

	float RotationRate = shipNS::ROTATION_RATE;
	float MaxRotationRate = shipNS::MAX_ROTATION_RATE;
	float RotationAccRate = shipNS::ROTATION_ACC_RATE;
	float RotationDrag = shipNS::ROTATION_DRAG;

	float getLifeCount();
	void setLifeCount(float lifeCount);

	void dash();
	void boost(bool b);
	double getMaxHP();
	string getdamagestring();
};
#endif _SHIP_H