
#ifndef _SPACEWAR_H             // prevent multiple definitions if this 
#define _SPACEWAR_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "ship.h"
#include "wall.h"
#include "missile.h"
//#include "bullet1.h"


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

	Image   planet;                 // planet image
	Image   nebula;                 // nebula image

	//Ship * ship1 = NULL;
	Ship	ship1;					// ship object
	Wall	wall1;					// wall object
	Missile missile1;				// missile object

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
