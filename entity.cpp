//  Module:             Gameplay Programming
//  Assignment1:        Ships and Shapes
//  Student Name:       Steven Koe
//  Student Number:     S10181536D
//  Student Name:       Jedidiah Wong
//  Student Number:     S10178790F

#include "entity.h"

//=============================================================================
// constructor
//=============================================================================
Entity::Entity() : Image()
{
	radius = 1.0;
	edge.left = -1;
	edge.top = -1;
	edge.right = 1;
	edge.bottom = 1;
	mass = 1.0;
	velocity.x = 0.0;
	velocity.y = 0.0;
	maxvel = 0.0;
	deltaV.x = 0.0;
	deltaV.y = 0.0;
	active = true;                  // the entity is active
	rotatedBoxReady = false;
	collisionType = entityNS::NONE;
	damagemultiplier = 1.0;
}

//=============================================================================
// Initialize the Entity.
// Pre: *gamePtr = pointer to Game object
//      width = width of Image in pixels  (0 = use full texture width)
//      height = height of Image in pixels (0 = use full texture height)
//      ncols = number of columns in texture (1 to n) (0 same as 1)
//      *textureM = pointer to TextureManager object
// Post: returns true if successful, false if failed
//=============================================================================
bool Entity::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	input = gamePtr->getInput();                // the input system
	audio = gamePtr->getAudio();
	return(Image::initialize(gamePtr->getGraphics(), width, height, ncols, textureM));
}

//=============================================================================
// activate the entity
//=============================================================================
void Entity::activate()
{
	active = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Entity::update(float frameTime)
{
	velocity += deltaV;
	deltaV.x = 0;
	deltaV.y = 0;
	Image::update(frameTime);
	rotatedBoxReady = false;    // for rotatedBox collision detection
}

//=============================================================================
// Perform collision detection between this entity and the other Entity.
// Each entity must use a single collision type. Complex shapes that require
// multiple collision types may be done by treating each part as a separate
// entity.
// Typically called once per frame.
// The collision types: CIRCLE, BOX, or ROTATED_BOX.
// Post: returns true if collision, false otherwise
//       sets collisionVector if collision
//=============================================================================
bool Entity::collidesWith(Entity &ent, VECTOR2 &collisionVector)
{
	// if either entity is not active then no collision may occcur
	if (!active || !ent.getActive())
		return false;

	// If both entities are CIRCLE collision
	if (collisionType == entityNS::CIRCLE && ent.getCollisionType() == entityNS::CIRCLE)
		return collideCircle(ent, collisionVector);
	// If both entities are BOX collision
	if (collisionType == entityNS::BOX && ent.getCollisionType() == entityNS::BOX)
		return collideBox(ent, collisionVector);
	// All other combinations use separating axis test
	if (collisionType == entityNS::ROTATED_BOX&&ent.getCollisionType() == entityNS::ROTATED_BOX)
		return collideRotatedBox(ent, collisionVector);
	// If neither entity uses CIRCLE collision
	if (collisionType != entityNS::CIRCLE && ent.getCollisionType() != entityNS::CIRCLE)
		return collideRotatedBox(ent, collisionVector);
	else    // one of the entities is a circle
		if (collisionType == entityNS::CIRCLE)  // if this entity uses CIRCLE collision
		{
			// Check for collision from other box with our circle
			bool collide = ent.collideRotatedBoxCircle(*this, collisionVector);
			// Put the collision vector in the proper direction
			collisionVector *= -1;              // reverse collision vector
			return collide;
		}
		else    // the other entity uses CIRCLE collision
			return collideRotatedBoxCircle(ent, collisionVector);
	return false;
}

//=============================================================================
// Circular collision detection method
// Called by collision(), default collision detection method
// Post: returns true if collision, false otherwise
//       sets collisionVector if collision
//=============================================================================
bool Entity::collideCircle(Entity &ent, VECTOR2 &collisionVector)
{
	// difference between centers
	distSquared = *getCenter() - *ent.getCenter();
	distSquared.x = distSquared.x * distSquared.x;      // difference squared
	distSquared.y = distSquared.y * distSquared.y;

	// Calculate the sum of the radii (adjusted for scale)
	sumRadiiSquared = (radius*getScale()) + (ent.radius*ent.getScale());
	sumRadiiSquared *= sumRadiiSquared;                 // square it

	// if entities are colliding
	if (distSquared.x + distSquared.y <= sumRadiiSquared)
	{
		// set collision vector
		collisionVector = *ent.getCenter() - *getCenter();
		return true;
	}
	return false;   // not colliding
}

//=============================================================================
// Axis aligned bounding box collision detection method
// Called by collision()
// Post: returns true if collision, false otherwise
//       sets collisionVector if collision
//=============================================================================
bool Entity::collideBox(Entity &ent, VECTOR2 &collisionVector)
{
	// if either entity is not active then no collision may occcur
	if (!active || !ent.getActive())
		return false;

	// Check for collision using Axis Aligned Bounding Box.
	if ((getCenterX() + edge.right*getScale() < ent.getCenterX() + ent.getEdge().left*ent.getScale()) ||
		(getCenterX() + edge.left*getScale() > ent.getCenterX() + ent.getEdge().right*ent.getScale()) ||
		(getCenterY() + edge.bottom*getScale() < ent.getCenterY() + ent.getEdge().top*ent.getScale()) ||
		(getCenterY() + edge.top*getScale() > ent.getCenterY() + ent.getEdge().bottom*ent.getScale()))
	{

		return false;
	}
	// set collision vector
	collisionVector = *ent.getCenter() - *getCenter();
	return true;
}


//=============================================================================
// Rotated Box collision detection method
// Called by collision()
// Post: returns true if collision, false otherwise
//       sets collisionVector if collisionw
// Uses Separating Axis Test to detect collision. 
// The separating axis test:
//   Two boxes are not colliding if their projections onto a line do not overlap.
//=============================================================================
bool Entity::collideRotatedBox(Entity &ent, VECTOR2 &collisionVector)
{
	computeRotatedBox();                    // prepare rotated box
	ent.computeRotatedBox();                // prepare rotated box
	if (projectionsOverlap(ent) && ent.projectionsOverlap(*this))
	{
		// set collision vector
		collisionVector = *ent.getCenter() - *getCenter();
		return true;
	}
	return false;
}

//=============================================================================
// Projects other box onto this edge01 and edge03.
// Called by collideRotatedBox()
// Post: returns true if projections overlap, false otherwise
//=============================================================================
bool Entity::projectionsOverlap(Entity &ent)
{
	float projection, min01, max01, min03, max03;

	// project other box onto edge01
	projection = graphics->Vector2Dot(&edge01, ent.getCorner(0)); // project corner 0
	min01 = projection;
	max01 = projection;
	// for each remaining corner
	for (int c = 1; c < 4; c++)
	{
		// project corner onto edge01
		projection = graphics->Vector2Dot(&edge01, ent.getCorner(c));
		if (projection < min01)
			min01 = projection;
		else if (projection > max01)
			max01 = projection;
	}
	if (min01 > edge01Max || max01 < edge01Min) // if projections do not overlap
		return false;                       // no collision is possible

	// project other box onto edge03
	projection = graphics->Vector2Dot(&edge03, ent.getCorner(0)); // project corner 0
	min03 = projection;
	max03 = projection;
	// for each remaining corner
	for (int c = 1; c < 4; c++)
	{
		// project corner onto edge03
		projection = graphics->Vector2Dot(&edge03, ent.getCorner(c));
		if (projection < min03)
			min03 = projection;
		else if (projection > max03)
			max03 = projection;
	}
	if (min03 > edge03Max || max03 < edge03Min) // if projections do not overlap
		return false;                       // no collision is possible

	return true;                            // projections overlap
}

//=============================================================================
// Rotated Box and Circle collision detection method
// Called by collision()
// Uses separating axis test on edges of box and radius of circle.
// If the circle center is outside the lines extended from the collision box
// edges (also known as the Voronoi region) then the nearest box corner is checked
// for collision using a distance check.
// The nearest corner is determined from the overlap tests.
//
//   Voronoi0 |   | Voronoi1
//         ---0---1---
//            |   |
//         ---3---2---
//   Voronoi3 |   | Voronoi2
//
// Pre: This entity must be box and other entity (ent) must be circle.
// Post: returns true if collision, false otherwise
//       sets collisionVector if collision
//=============================================================================
bool Entity::collideRotatedBoxCircle(Entity &ent, VECTOR2 &collisionVector)
{
	float min01, min03, max01, max03, center01, center03;

	computeRotatedBox();                    // prepare rotated box

	// project circle center onto edge01
	center01 = graphics->Vector2Dot(&edge01, ent.getCenter());
	min01 = center01 - ent.getRadius()*ent.getScale(); // min and max are Radius from center
	max01 = center01 + ent.getRadius()*ent.getScale();
	if (min01 > edge01Max || max01 < edge01Min) // if projections do not overlap
		return false;                       // no collision is possible

	// project circle center onto edge03
	center03 = graphics->Vector2Dot(&edge03, ent.getCenter());
	min03 = center03 - ent.getRadius()*ent.getScale(); // min and max are Radius from center
	max03 = center03 + ent.getRadius()*ent.getScale();
	if (min03 > edge03Max || max03 < edge03Min) // if projections do not overlap
		return false;                       // no collision is possible

	// circle projection overlaps box projection
	// check to see if circle is in voronoi region of collision box
	if (center01 < edge01Min && center03 < edge03Min)    // if circle in Voronoi0
		return collideCornerCircle(corners[0], ent, collisionVector);
	if (center01 > edge01Max && center03 < edge03Min)    // if circle in Voronoi1
		return collideCornerCircle(corners[1], ent, collisionVector);
	if (center01 > edge01Max && center03 > edge03Max)    // if circle in Voronoi2
		return collideCornerCircle(corners[2], ent, collisionVector);
	if (center01 < edge01Min && center03 > edge03Max)    // if circle in Voronoi3
		return collideCornerCircle(corners[3], ent, collisionVector);

	// circle not in voronoi region so it is colliding with edge of box
	// set collision vector, uses simple center of circle to center of box
	collisionVector = *ent.getCenter() - *getCenter();
	return true;
}

//=============================================================================
// The box corner is checked for collision with circle using a distance check.
// Called by collideRotatedBoxCircle()
// Post: returns true if collision, false otherwise
//       sets collisionVector if collision
//=============================================================================
bool Entity::collideCornerCircle(VECTOR2 corner, Entity &ent, VECTOR2 &collisionVector)
{
	distSquared = corner - *ent.getCenter();            // corner - circle
	distSquared.x = distSquared.x * distSquared.x;      // difference squared
	distSquared.y = distSquared.y * distSquared.y;

	// Calculate the sum of the radii, then square it
	sumRadiiSquared = ent.getRadius()*ent.getScale();   // (0 + circleR)
	sumRadiiSquared *= sumRadiiSquared;                 // square it

	// if corner and circle are colliding
	if (distSquared.x + distSquared.y <= sumRadiiSquared)
	{
		// set collision vector
		collisionVector = *ent.getCenter() - corner;
		return true;
	}
	return false;
}

//=============================================================================
// Compute corners of rotated box, projection edges and min and max projections
// 0---1  corner numbers
// |   |
// 3---2
//=============================================================================
void Entity::computeRotatedBox()
{
	if (rotatedBoxReady)
		return;
	float projection;

	VECTOR2 rotatedX(cos(spriteData.angle), sin(spriteData.angle));
	VECTOR2 rotatedY(-sin(spriteData.angle), cos(spriteData.angle));

	const VECTOR2 *center = getCenter();
	corners[0] = *center + rotatedX * ((float)edge.left*getScale()) +
		rotatedY * ((float)edge.top*getScale());
	corners[1] = *center + rotatedX * ((float)edge.right*getScale()) +
		rotatedY * ((float)edge.top*getScale());
	corners[2] = *center + rotatedX * ((float)edge.right*getScale()) +
		rotatedY * ((float)edge.bottom*getScale());
	corners[3] = *center + rotatedX * ((float)edge.left*getScale()) +
		rotatedY * ((float)edge.bottom*getScale());

	// corners[0] is used as origin
	// The two edges connected to corners[0] are used as the projection lines
	edge01 = VECTOR2(corners[1].x - corners[0].x, corners[1].y - corners[0].y);
	graphics->Vector2Normalize(&edge01);
	edge03 = VECTOR2(corners[3].x - corners[0].x, corners[3].y - corners[0].y);
	graphics->Vector2Normalize(&edge03);

	// this entities min and max projection onto edges
	projection = graphics->Vector2Dot(&edge01, &corners[0]);
	edge01Min = projection;
	edge01Max = projection;
	// project onto edge01
	projection = graphics->Vector2Dot(&edge01, &corners[1]);
	if (projection < edge01Min)
		edge01Min = projection;
	else if (projection > edge01Max)
		edge01Max = projection;
	// project onto edge03
	projection = graphics->Vector2Dot(&edge03, &corners[0]);
	edge03Min = projection;
	edge03Max = projection;
	projection = graphics->Vector2Dot(&edge03, &corners[3]);
	if (projection < edge03Min)
		edge03Min = projection;
	else if (projection > edge03Max)
		edge03Max = projection;

	rotatedBoxReady = true;
}

//=============================================================================
// Is this Entity outside the specified rectangle
// Post: returns true if outside rect, false otherwise
//=============================================================================
bool Entity::outsideRect(RECT rect)
{
	if (spriteData.x + spriteData.width*getScale() < rect.left ||
		spriteData.x > rect.right ||
		spriteData.y + spriteData.height*getScale() < rect.top ||
		spriteData.y > rect.bottom)
		return true;
	return false;
}

////=============================================================================
//// damage
//// This entity has been damaged by a weapon.
//// Override this function in the inheriting class.
////=============================================================================
//void Entity::damage(int weapon)
//{}

//=============================================================================
// Entity bounces after collision with a sphere collision box
//=============================================================================
void Entity::bounce(VECTOR2 &collisionVector, Entity &ent)
{
	VECTOR2 Vdiff = ent.getVelocity() - velocity;
	VECTOR2 cUV = collisionVector;              // collision unit vector
	Graphics::Vector2Normalize(&cUV);
	float cUVdotVdiff = Graphics::Vector2Dot(&cUV, &Vdiff);
	float massRatio = 2.0f;
	if (getMass() != 0)
		massRatio *= (ent.getMass() / (getMass() + ent.getMass()));

	// If entities are already moving apart then bounce must
	// have been previously called and they are still colliding.
	// Move entities apart along collisionVector
	if (cUVdotVdiff > 0)
	{
		setX(getX() - cUV.x * massRatio * damagemultiplier);
		setY(getY() - cUV.y * massRatio * damagemultiplier);
	}
	else
		deltaV += ((massRatio * cUVdotVdiff) * cUV* damagemultiplier);
}

//=============================================================================
// Entity bounces after collision with a static square collision box
//=============================================================================
int Entity::squarebounce(Entity &ent1)
{
	double angbet = anglebetween(ent1);

	if (angbet >= 315 || angbet < 45)				//Top Wall
	{
		if (ent1.getVelocityY() > 0)				//If ship is moving down
		{
			ent1.setVelocityY(-(ent1.getVelocityY())); //Reverse Y Velocity
			return 1;
		}
		else
		{
			ent1.setVelocityY(ent1.getVelocityY() - (4));	//Else if stuck in wall, Force it out
		}
	}
	else if (angbet >= 45 && angbet < 135)				//Right Wall
	{
		if (ent1.getVelocityX() < 0)				//If ship is moving left
		{
			ent1.setVelocityX(-(ent1.getVelocityX())); //Reverse X Velocity
			return 2;
		}
		else
		{
			ent1.setVelocityX(ent1.getVelocityX() + (4));	//Else if stuck in wall, Force it riht
		}
	}
	else if (angbet >= 135 && angbet < 225)				//Bottom Wall
	{
		if (ent1.getVelocityY() < 0)				//If ship is moving up
		{
			ent1.setVelocityY(-(ent1.getVelocityY())); //Reverse Y Velocity
			return 3;
		}
		else
		{
			ent1.setVelocityY(ent1.getVelocityY() +4);	//Else if stuck in wall, Force it out
		}
	}
	else															//left wall
	{
		if (ent1.getVelocityX() > 0)				//If ship is moving right
		{
			ent1.setVelocityX(-(ent1.getVelocityX())); //Reverse X Velocity
			return 4;
		}
		else
		{
			ent1.setVelocityX(ent1.getVelocityX() - (4));	//Else if stuck in wall, Force it left
		}
	}
}

double Entity::anglebetween(Entity &ent2)	//Returns in degrees
{
	double Xdiff = ent2.getCenterX() - getCenterX();
	double Ydiff = ent2.getCenterY() - getCenterY();

	if (ent2.getCenterX() > getCenterX())			//if the object is on the right:
	{
		return 90 + (atan(Ydiff / Xdiff) / (2 * PI) * 360);			//Return result in degrees, refer to steven why +90
	}
	else
	{
		return 270 + (atan(Ydiff / Xdiff) / (2 * PI) * 360);		//Return result in degrees, refer to steven why +270
	}
}

double Entity::bulletbounce(Entity &ent1)
{
	double angbet = anglebetween(ent1);
	return angbet;
}
//=============================================================================
// Get Velocities
//=============================================================================
double Entity::getVelocityX()
{
	return velocity.x;
}
double Entity::getVelocityY()
{
	return velocity.y;
}
void Entity::setVelocityX(float v)
{
	velocity.x = v;
}
void Entity::setVelocityY(float v)
{
	velocity.y = v;
}

void Entity::topbottomrotatebounce() {}
void Entity::leftrightrotatebounce() {}

double Entity::getHP()
{
	return hp;
}
void Entity::setHP(double hpVal) 
{
	hp = hpVal;
}

//=============================================================================
// Get and Set Damage
//=============================================================================
double Entity::getDamage()
{
	return damage;
}
void Entity::setDamage(double d)
{
	damage = d;
}

//=================================================================
// Get Explosion Blast
//=================================================================
void Entity::getExplosionBlast(Entity &ent2, float blastPower)
{
	float powerX = abs(ent2.getCenterX() - getCenterX());
	float powerY = abs(ent2.getCenterY() - getCenterY());
	float power = 1/(powerX+ powerY);
	double angbet = anglebetween(ent2);
	angbet = (angbet * PI / 180)+0.005;		//So angbet is never exactly 0 or PI, since that causes wonky behaviour that I can't fix (steve)
	ent2.setVelocityX(ent2.getVelocityX() + (blastPower * power *1000* sin(angbet)));
	ent2.setVelocityY(ent2.getVelocityY() + (blastPower * power *1000* -cos(angbet)));
}
