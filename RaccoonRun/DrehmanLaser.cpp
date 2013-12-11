#include "DrehmanLaser.h"

//=============================================================================
// default constructor
//=============================================================================
Laser::Laser() : Entity()//Still()
{
	//still life should know where its world coordinates are. 
	//maybe send it a bool in update telling it whether to move left / right?
	spriteData.width = LASER_WIDTH;
	spriteData.height = LASER_HEIGHT;
	spriteData.x = GAME_WIDTH/4;
	spriteData.y = GAME_HEIGHT - (GAME_HEIGHT/3);
	spriteData.rect.bottom = LASER_HEIGHT;
	spriteData.rect.right = LASER_WIDTH;
	velocity.x = 0;
	velocity.y = 0;
//	frameDelay = LASER_ANIMATION_DELAY;
//	startFrame = 0;
//	endFrame = 3;
//	currentFrame = startFrame;

	// Collision box
    edge.bottom = LASER_HALF_HEIGHT-1;
    edge.top = -LASER_HALF_HEIGHT;
    edge.left = -LASER_HALF_WIDTH;
    edge.right = LASER_HALF_WIDTH;
	
	mass = 10.0f; // will probably need to change this!
	collisionType = entityNS::ROTATED_BOX;
	magicNumberX=-18;
	magicNumberY=-20;

	right = false;
	counter = 0;
}

bool Laser::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Laser::update(float frameTime)
{
	Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move along X 
    spriteData.y += frameTime * velocity.y;         // move along Y
//	Still::update(frameTime, left, right);
}

bool Laser::incrementCounter()
{
	++counter;
	if(counter==COUNTER_MAX)
	{
		counter = 0;
		return true;
	}
	return false;
}