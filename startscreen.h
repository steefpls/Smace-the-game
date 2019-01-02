//  Module:             Gameplay Programming
//  Assignment1:        Ships and Shapes
//  Student Name:       Steven Koe
//  Student Number:     S10181536D
//  Student Name:       Jedidiah Wong
//  Student Number:     S10178790F

#ifndef _STARTSCREEN_H             // prevent multiple definitions if this 
#define _STARTSCREEN_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "text.h"
#include "spacewar.h"

#include <iostream>
#include <list>
#include <vector>
namespace startscreenNS
{
	const char FONT[] = "Arial Bold";  // font
	const int FONT_SIZE = 48;     // font height
	const COLOR_ARGB FONT_COLOR = graphicsNS::YELLOW;
}
//=============================================================================
// Create game class
//=============================================================================
class Startscreen : public Game
{

private:
	// game items
	TextureManager nebulaTexture;   // nebula texture
	Image   nebula;                 // nebula image


public:
	// Constructor
	Startscreen();

	// Destructor
	virtual ~Startscreen();

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

