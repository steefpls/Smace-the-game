#ifndef _PLAYER_H                 // Prevent multiple definitions if this 
#define _PLAYER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "ship.h"
using namespace std;
#include <iostream>
#include <vector>

namespace playerNS
{
	const char player1Right = 'D';
	const char player1Left = 'A';
	const char player1Up = 'W';
	const char player1Down = 'S';

	const char player2Right = VK_RIGHT;
	const char player2Left = VK_LEFT;
	const char player2Up = VK_UP;
	const char player2Down = VK_DOWN;
}

// inherits from Entity class
class Player : public Entity
{
private:

public:
	// constructor
	Player();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	vector<Ship *> shipList;
};
#endif
