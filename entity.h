
#ifndef _ENTITY_H                 // prevent multiple definitions if this 
#define _ENTITY_H                 // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "input.h"
#include "image.h"
#include "game.h"

namespace entityNS
{
	enum COLLISION_TYPE { NONE, CIRCLE, BOX, ROTATED_BOX };
}

class Entity : public Image
{
protected:
	entityNS::COLLISION_TYPE collisionType;
	VECTOR2 center;			//The centre of the entity
	float radius;			//Defines the radius of circle used for circular collision detection
	VECTOR2 distSquared;    // used for calculating circle collision
	float   sumRadiiSquared;
	RECT edge;				//The rectangular region used by BOX or ROTATED_BOX collision detection
	VECTOR2 corners[4];		//For ROTATED_BOX collision detection
	VECTOR2 edge01, edge03;	//Edges used for projection
	float edge01Min, edge01Max, edge03Min, edge03Max;	//min and max projections
	VECTOR2 velocity;		//The velocity containing the current entity velocity
	VECTOR2 deltaV;         // added to velocity during next call to update()
	float mass;				//The mass of the entity
	float   rr;             // Radius squared variable
	Input   *input;         // pointer to the input system
	HRESULT hr;             // standard return type
	bool active;			//The current state of this entity. Only active entities may collide
	bool rotatedBoxReady;	//True when rotated collision box is ready

	// --- The following functions are protected because they are not intended to be
	// --- called from outside the class.
	// Circular collision detection 
	// Pre: &ent = Other entity
	// Post: &collisionVector contains collision vector
	virtual bool collideCircle(Entity &ent, VECTOR2 &collisionVector);
	// Axis aligned box collision detection
	// Pre: &ent = Other entity
	// Post: &collisionVector contains collision vector
	virtual bool collideBox(Entity &ent, VECTOR2 &collisionVector);
	// Separating axis collision detection between boxes
	// Pre: &ent = Other entity
	// Post: &collisionVector contains collision vector
	virtual bool collideRotatedBox(Entity &ent, VECTOR2 &collisionVector);
	// Separating axis collision detection between box and circle
	// Pre: &ent = Other entity
	// Post: &collisionVector contains collision vector
	virtual bool collideRotatedBoxCircle(Entity &ent, VECTOR2 &collisionVector);
	// Separating axis collision detection helper functions
	void computeRotatedBox();
	bool projectionsOverlap(Entity &ent);
	bool collideCornerCircle(VECTOR2 corner, Entity &ent, VECTOR2 &collisionVector);

public:
	//Constructor
	Entity();
	//Destructor
	virtual ~Entity() {}

	//=========
	// GETTERS
	//=========
	// Return center of scaled Entity as screen x,y.
	virtual const VECTOR2* getCenter()
	{
		center = VECTOR2(getCenterX(), getCenterY());
		return &center;
	}

	// Return radius of collision circle.
	virtual float getRadius() const { return radius; }

	// Return RECT structure used for BOX and ROTATED_BOX collision detection.
	virtual const RECT& getEdge() const { return edge; }

	// Return corner c of ROTATED_BOX
	virtual const VECTOR2* getCorner(UINT c) const
	{
		if (c >= 4)
			c = 0;
		return &corners[c];
	}

	// Return velocity vector.
	virtual const VECTOR2 getVelocity() const { return velocity; }

	// Return active.
	virtual bool  getActive()         const { return active; }

	// Return mass.
	virtual float getMass()           const { return mass; }

	// Return collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
	virtual entityNS::COLLISION_TYPE getCollisionType() { return collisionType; }

	//=========
	// SETTERS
	//=========
	 // Set velocity.
	virtual void  setVelocity(VECTOR2 v) { velocity = v; }

	// Set delta velocity. Added to velocity in update().
	virtual void  setDeltaV(VECTOR2 dv) { deltaV = dv; }

	// Set active.
	virtual void  setActive(bool a) { active = a; }

	// Set mass.
	virtual void  setMass(float m) { mass = m; }

	//========
	// OTHERS
	//========
	 // Update Entity.
	// typically called once per frame
	// frameTime is used to regulate the speed of movement and animation
	virtual void update(float frameTime);

	// Initialize Entity
   // Pre: *gamePtr = pointer to Game object
   //      width = width of Image in pixels  (0 = use full texture width)
   //      height = height of Image in pixels (0 = use full texture height)
   //      ncols = number of columns in texture (1 to n) (0 same as 1)
   //      *textureM = pointer to TextureManager object
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);

	// Activate Entity.
	virtual void activate();

	// Empty ai function to allow Entity objects to be instantiated.
	//virtual void ai(float frameTime, Entity &ent);

	// Is this entity outside the specified rectangle?
	virtual bool outsideRect(RECT rect);

	// Does this entity collide with ent?
	virtual bool collidesWith(Entity &ent, VECTOR2 &collisionVector);

	// Damage this Entity with weapon.
	virtual void damage(int weapon);

	// Entity bounces after collision with other Entity
	void bounce(VECTOR2 &collisionVector, Entity &ent);
	double anglebetween (Entity &ent1, Entity &ent2);

};
#endif
