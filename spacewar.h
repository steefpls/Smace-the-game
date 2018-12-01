
#ifndef _SPACEWAR_H             // prevent multiple definitions if this 
#define _SPACEWAR_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "ship.h"
#include "wall.h"
//#include "missile.h"
#include "explosion.h"
//#include "bullet1.h"

#include <iostream>
#include <list>
#include <vector>
//=============================================================================
// Create game class
//=============================================================================
class Spacewar : public Game
{
private:
	// game items
	TextureManager nebulaTexture;   // nebula texture
	TextureManager planetTexture;   // planet texture
	TextureManager shipTexture;		// ship texture
	TextureManager wallTexture;		// wall texture
	TextureManager missileTexture;	//missile texture
	TextureManager explosionTexture;	//explosion texture

	Image   planet;                 // planet image
	Image   nebula;                 // nebula image

	//Ship * ship1 = NULL;
	Ship	ship1;					// ship object
	std::vector<Wall *> wallListTop;	//list of top walls
	std::vector<Wall *> wallListBottom;	//list of bottom walls
	std::vector<Wall *> wallListLeft;	//list of left walls
	std::vector<Wall *> wallListRight;	//list of right walls
	std::vector<std::vector<Wall*>> wallListList;	//list of wall lists
	
	//Missile missile1;				// missile object
	Explosion explosion1;

	//Bullet	bullet1;				// bullet image

public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif
