// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "pizza.h"

//=============================================================================
// default constructor
//=============================================================================
Pizza::Pizza() : Still()
{
	//still life should know where its world coordinates are. 
	//maybe send it a bool in update telling it whether to move left / right?
	spriteData.width = CPSOUP_WIDTH;
	spriteData.height = CPSOUP_HEIGHT;
	spriteData.x = GAME_WIDTH/4;
	spriteData.y = GAME_HEIGHT - (GAME_HEIGHT/3);
	spriteData.rect.bottom = CPSOUP_HEIGHT;
	spriteData.rect.right = CPSOUP_WIDTH;
	velocity.x = 0;
	velocity.y = 0;
//	frameDelay = CPSOUP_ANIMATION_DELAY;
//	startFrame = 0;
//	endFrame = 3;
//	currentFrame = startFrame;

	// Collision box
    edge.bottom = -PIZZA_HALF_HEIGHT-1; // same as top so that he only collides from the top
    edge.top = -PIZZA_HALF_HEIGHT;
    edge.left = -PIZZA_HALF_WIDTH;
    edge.right = PIZZA_HALF_WIDTH;
	
	mass = 10.0f; // will probably need to change this!
	collisionType = entityNS::BOX;
	magicNumberX=50;
	magicNumberY=10;
}

bool Pizza::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Pizza::update(float frameTime, bool left, bool right)
{
	Entity::update(frameTime);
	Still::update(frameTime, left, right);
}
