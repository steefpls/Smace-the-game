//
//#include "bullet1.h"
//
////=============================================================================
//// default constructor
////=============================================================================
//Bullet::Ship() : Entity()
//{
//	spriteData.width = shipNS::WIDTH;           // size of Ship1
//	spriteData.height = shipNS::HEIGHT;
//	spriteData.x = shipNS::X;                   // location on screen
//	spriteData.y = shipNS::Y;
//	spriteData.rect.bottom = shipNS::HEIGHT;    // rectangle to select parts of an image
//	spriteData.rect.right = shipNS::WIDTH;
//	velocity.x = 0;                             // velocity X
//	velocity.y = 0;                             // velocity Y
//	frameDelay = shipNS::SHIP_ANIMATION_DELAY;
//	startFrame = shipNS::SHIP1_START_FRAME;     // first frame of ship animation
//	endFrame = shipNS::SHIP1_END_FRAME;     // last frame of ship animation
//	currentFrame = startFrame;
//	radius = shipNS::WIDTH / 2.0;
//	shieldOn = false;
//	mass = shipNS::MASS;
//	collisionType = entityNS::ROTATED_BOX;
//}
//
////=============================================================================
//// Initialize the Ship.
//// Post: returns true if successful, false if failed
////=============================================================================
//bool Ship::initialize(Game *gamePtr, int width, int height, int ncols,
//	TextureManager *textureM)
//{
//	shield.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
//	shield.setFrames(shipNS::SHIELD_START_FRAME, shipNS::SHIELD_END_FRAME);
//	shield.setCurrentFrame(shipNS::SHIELD_START_FRAME);
//	shield.setFrameDelay(shipNS::SHIELD_ANIMATION_DELAY);
//	shield.setLoop(true);                  // do not loop animation
//	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
//}
////=============================================================================
//// Update all game items
////=============================================================================
//void Bullet::update(float frameTime)
//{
//
//}