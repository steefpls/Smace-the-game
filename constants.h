//  Module:             Gameplay Programming
//  Assignment1:        Ships and Shapes
//  Student Name:       Steven Koe
//  Student Number:     S10181536D
//  Student Name:       Jedidiah Wong
//  Student Number:     S10178790F

#ifndef _CONSTANTS_H            // prevent multiple definitions if this 
#define _CONSTANTS_H            // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)



//-----------------------------------------------
//                  Constants
//-----------------------------------------------

//weapon types
enum WEAPON {BULLET, TORPEDO, SHIP, WALL};

// graphic images
const char NEBULA_IMAGE[] = "pictures\\Ships-and-shapes-Backgroundshapes.png";  // photo source NASA/courtesy of nasaimages.org 
const char NEBULABACKGROUND_IMAGE[] = "pictures\\BackgroundShipsandSHapes.png";
const char PLANET_IMAGE[] = "pictures\\planet.png"; // picture of planet
const char SHIP1_IMAGE[] = "pictures\\ship1.png";   // spaceship
const char SHIP2_IMAGE[] = "pictures\\ship2.png";  //cooler spaceship
const char WALL_IMAGE[] = "pictures\\wallAlt.png";   // wall
const char MISSILE_IMAGE[] = "pictures\\missile.png";	//missile
const char EXPLOSION_IMAGE[] = "pictures\\explosion.png";	//explosion
const char BULLET_IMAGE[] = "pictures\\Bullet123.png";	//bullet
const char MINE_IMAGE[] = "pictures\\mine.png";	//mine
const char BLACKHOLE_IMAGE[] = "pictures\\blackhole.png";	//black hole
const char RECTANGLE_IMAGE[] = "pictures\\bigblackrect.png";	//big black rectangle and smaller blue one
const char BLUEHEART_IMAGE[] = "pictures\\red_heart.png";	//blue heart
const char REDHEART_IMAGE[] = "pictures\\blue_heart.png";	//red heart

const char TITLE_IMAGE[] = "pictures\\Title.png";


// audio files
const char WAVE_BANK[] = "audio\\Win\\Wave Bank.xwb";
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";

//audio cues
const char BGM[] = "koriuchi8bit";
const char BOOM[] = "boom";
const char MISSILE[] = "missileLaunch";
const char BULLETSHOT[] = "bulletShot";
const char SHIPHITSHIP[] = "ShipHitShip";
const char MINEBLEEP[] = "mineBleep";

////keybinds
//const char player1Right = 'D';
//const char player1Left = 'A';
//const char player1Up = 'W';
//const char player1Down = 'S';

//const char player2Right = VK_RIGHT;
//const char player2Left = VK_LEFT;
//const char player2Up = VK_UP;
//const char player2Down = VK_DOWN;

static bool startscreen = true;
// window
const char CLASS_NAME[] = "Spacewar";
const char GAME_TITLE[] = "Spacewar";
const bool FULLSCREEN = true;              // windowed or fullscreen
const UINT GAME_WIDTH =  1920;               // width of game in pixels
const UINT GAME_HEIGHT = 1080;               // height of game in pixels
 
// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key
const UCHAR SHIFT_KEY = VK_SHIFT;	//Shift key
const UCHAR SPACE = VK_SPACE;			// Space Key
const UCHAR CTRL = VK_CONTROL;			// Ctrl key




#endif
