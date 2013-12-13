// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "DrehmanSniper.h"

//=============================================================================
// default constructor
//=============================================================================
Sniper::Sniper() : Still()
{
	// Right now these are hardcoded for JPo - later we'll be deriving classes from this for specific characters
	spriteData.width = JPO_WIDTH;
	spriteData.height = JPO_HEIGHT;
	spriteData.x = GAME_WIDTH/4;
	spriteData.y = GAME_HEIGHT - (GAME_HEIGHT/3);
	spriteData.rect.bottom = JPO_HEIGHT;
	spriteData.rect.right = JPO_WIDTH;
	velocity.x = 0;
	velocity.y = 0;

	frameDelay = SNIPER_ANIMATION_DELAY;
	startFrame = 0;
	endFrame = 3;
	currentFrame = startFrame;
	/*
	frameDelay = JPO_ANIMATION_DELAY;
	//startFrame = JPO_LOOKING_RIGHT_START;
	//endFrame = JPO_LOOKING_RIGHT_END;
	startFrame = JPO_LOOKING_RIGHT_START;
	endFrame=JPO_LOOKING_RIGHT_START;
	currentFrame = startFrame;
	*/

	// Collision box
	edge.bottom = JPO_HALF_HEIGHT;
	edge.top = -JPO_HALF_HEIGHT;
	edge.left = -JPO_HALF_WIDTH;
	edge.right = JPO_HALF_WIDTH;
	
	mass = 10.0f; // will probably need to change this!
	collisionType = entityNS::BOX;

	//added by Christy. For Raccoon, obviously.
	magicNumberX=0;
	magicNumberY=0;

	turnLeft = turnRight = false;
}

bool Sniper::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
    return(Still::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Sniper::update(float frameTime, bool left, bool right)
{
    Entity::update(frameTime);
    Still::update(frameTime, left, right);	
}

void Sniper::ai(Entity *player)
{
	/*
	if(spriteData.x < player->getX() && velocity.x < 0)
		turnRight = true;
	else if(spriteData.x > player->getX() && velocity.x > 0)
		turnLeft = true;

	if(abs(spriteData.x - player->getX()) > JPO_PROXIMITY_DISTANCE)
	{
		if(velocity.x >= 0)
			velocity.x = JPO_PROXIMITY_SPEED;
		else
			velocity.x = -JPO_PROXIMITY_SPEED;
	}
	else
	{
		if(velocity.x >= 0)
			velocity.x = JPO_SPEED;
		else
			velocity.x = -JPO_SPEED;
	}
	*/
}