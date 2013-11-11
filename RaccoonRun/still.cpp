// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "Still.h"

//=============================================================================
// default constructor
//=============================================================================
Still::Still() : Entity()
{
	//still life should know where its world coordinates are. 
	//maybe send it a bool in update telling it whether to move left / right?
	// Right now these are hardcoded for JPo - later we'll be deriving classes from this for specific characters
	spriteData.width = JPO_WIDTH;
	spriteData.height = JPO_HEIGHT;
	spriteData.x = GAME_WIDTH/4;
	spriteData.y = GAME_HEIGHT - (GAME_HEIGHT/3);
	spriteData.rect.bottom = JPO_HEIGHT;
	spriteData.rect.right = JPO_WIDTH;
	velocity.x = 0;
	velocity.y = 0;
	frameDelay = JPO_ANIMATION_DELAY;
	startFrame = JPO_LOOKING_RIGHT_START;
	endFrame = JPO_LOOKING_RIGHT_END;
	currentFrame = startFrame;
	
	mass = 10.0f; // will probably need to change this!
	collisionType = entityNS::BOX;
}

bool Still::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Still::update(float frameTime, bool left, bool right)
{
	//needs a move-left / move-right bool. If received, will move the still object either left or right. 
    //Entity::update(frameTime);
	if(left)
	{
		spriteData.x++;
	}
	else if(right)
	{
		spriteData.x--;
	}
    //spriteData.x += frameTime * velocity.x;         // move along X 
    //spriteData.y += frameTime * velocity.y;         // move along Y
}
void Still::update(bool moveLeft, bool moveRight)
{
	//if(moveLeft)
	//{
	//	spriteData.x++;
	//}
	//else if(moveRight)
	//{
	//	spriteData.x--;
	//}
	//else
	//	return;
}