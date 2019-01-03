//  Module:             Gameplay Programming
//  Assignment1:        Ships and Shapes
//  Student Name:       Steven Koe
//  Student Number:     S10181536D
//  Student Name:       Jedidiah Wong
//  Student Number:     S10178790F

#ifndef _SPACEWAR_H             // prevent multiple definitions if this 
#define _SPACEWAR_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "ship.h"
#include "wall.h"
#include "explosion.h"
#include "blackhole.h"
#include "text.h"
#include "audio.h"

#include <iostream>
#include <list>
#include <vector>
namespace spacewarNS
{
	const char FONT[] = "Omelette";  // font
	const int FONT_SIZE = 48;     // font height
	const COLOR_ARGB FONT_COLOR = graphicsNS::YELLOW;
}
//=============================================================================
// Create game class
//=============================================================================
class Spacewar : public Game
{

private:
	// game items
	TextureManager nebulaTexture;   // nebula texture
	TextureManager nebulabackgroundTexture; //nebula background texture

	//TextureManager planetTexture;   // planet texture
	TextureManager ship1Texture;		// ship texture
	TextureManager ship2Texture;		// cooler ship texture
	TextureManager wallTexture;		// wall texture
	TextureManager missileTexture;	//missile texture
	TextureManager explosionTexture;	//explosion texture
	TextureManager bulletTexture;	//bullet texture
	TextureManager mineTexture;	//mine texture
	TextureManager blackholeTexture;	//black hole texture
	TextureManager rectTexture;	//big black rectangle and smaller blue one texture
	TextureManager blueHeartTexture;
	TextureManager redHeartTexture;
	TextureManager titleTexture;
	TextureManager ship1ParticleTexture;
	TextureManager ship2ParticleTexture;

	//Image   planet;                 // planet image
	Image	title;
	float titleScale;
	bool titleScaleIncrease;
	Image   nebula;                 // nebula image
	Image nebulabackground1;
	Image nebulabackground2;
	Image   blueHeart;
	Image	redHeart;

	//Ship * ship1 = NULL;
	Ship	ship1;					// ship object
	Ship	ship2;
	std::vector<Wall *> wallListTop;	//list of top walls
	std::vector<Wall *> wallListBottom;	//list of bottom walls
	std::vector<Wall *> wallListLeft;	//list of left walls
	std::vector<Wall *> wallListRight;	//list of right walls
	std::vector<std::vector<Wall*>> wallListList;	//list of wall lists;
	std::vector<Explosion *> explosionList;

	Text Player1Label;	//Player 1 Label
	Text Player1DamagePercent;	//Player 1 Damage percentage

	Text PressEnterToStart;
	int PETSalpha;
	bool alphaIncrease;

	Text gameOverText;

	Text Player2Label;	//Player 1 Label
	Text Player2DamagePercent;	//Player 1 Damage percentage
	
	const char player1Primary = 'C';
	const char player1Secondary = 'X';

	const char player2Secondary = 'M';
	int trigger = 0;
	string triggeredship = "";
	
	bool startscreenon = true;
	bool gameoverscreen = false;

	//Missile missile1;				// missile object
	Explosion explosion1;

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
	void resetGame();
	
};

#endif
