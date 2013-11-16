// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "raccoon.h"

//=============================================================================
// default constructor
//=============================================================================
Raccoon::Raccoon() : Character()
{
	// Base Character is set for JPo - override as necessary
	spriteData.width = RACCOON_WIDTH;
	spriteData.height = RACCOON_HEIGHT;
	spriteData.x = GAME_WIDTH/4;
	spriteData.y = GAME_HEIGHT - (GAME_HEIGHT/3);
	spriteData.rect.bottom = RACCOON_HEIGHT;
	spriteData.rect.right = RACCOON_WIDTH;
	velocity.x = 0;
	velocity.y = 0;
	frameDelay = JPO_ANIMATION_DELAY;
	/*startFrame = JPO_LOOKING_RIGHT_START;
	endFrame = JPO_LOOKING_RIGHT_END;*/
	startFrame = RACCOON_LOOKING_RIGHT_START;
	endFrame = RACCOON_LOOKING_RIGHT_START;
	currentFrame = startFrame;

	// Collision box
	edge.bottom = JPO_HALF_HEIGHT+10;
	edge.top = -JPO_HALF_HEIGHT;
	edge.left = -JPO_HALF_WIDTH;
	edge.right = JPO_HALF_WIDTH;
	
	mass = 10.0f; // will probably need to change this!
	collisionType = entityNS::BOX;

	//added by Christy. For Raccoon, obviously.
	magicNumberX=0;
	magicNumberY=0;

	onLand = true;
}

void Raccoon::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move along X 
    spriteData.y += frameTime * velocity.y;         // move along Y

	if(!onLand)
		velocity.y += frameTime * GRAVITY;              // gravity

    // Bounce off walls
    if (spriteData.x > GAME_WIDTH - spriteData.width)  // if hit right screen edge
    {
        spriteData.x = GAME_WIDTH - spriteData.width;  // position at right screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    } else if (spriteData.x < 0)                    // else if hit left screen edge
    {
        spriteData.x = 0;                           // position at left screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    }
    if (spriteData.y > GAME_HEIGHT - spriteData.height) // if hit bottom screen edge
    {
        spriteData.y = GAME_HEIGHT - spriteData.height; // position at bottom screen edge
        velocity.y = 0;
    } else if (spriteData.y < 0)                    // else if hit top screen edge
    {
        spriteData.y = 0;                           // position at top screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    }
}
