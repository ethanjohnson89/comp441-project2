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
	/*startFrame = JPO_LOOKING_RIGHT_START;
	endFrame = JPO_LOOKING_RIGHT_END;*/
	startFrame = RACCOON_LOOKING_RIGHT_START;
	endFrame=RACCOON_LOOKING_RIGHT_START;
	currentFrame = startFrame;
	
	mass = 10.0f; // will probably need to change this!
	collisionType = entityNS::BOX;

	//added by Christy. For Raccoon, obviously.
	magicNumberX=0;
	magicNumberY=0;
}

bool Raccoon::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
    return(Character::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Raccoon::update(float frameTime)
{
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move along X 
    spriteData.y += frameTime * velocity.y;         // move along Y

    // Bounce off walls
    if (spriteData.x > GAME_WIDTH - JPO_WIDTH)  // if hit right screen edge
    {
        spriteData.x = GAME_WIDTH - JPO_WIDTH;  // position at right screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    } else if (spriteData.x < 0)                    // else if hit left screen edge
    {
        spriteData.x = 0;                           // position at left screen edge
        velocity.x = -velocity.x;                   // reverse X direction
    }
    if (spriteData.y > GAME_HEIGHT - JPO_HEIGHT) // if hit bottom screen edge
    {
        spriteData.y = GAME_HEIGHT - JPO_HEIGHT; // position at bottom screen edge
        velocity.y = 0;
    } else if (spriteData.y < 0)                    // else if hit top screen edge
    {
        spriteData.y = 0;                           // position at top screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    }

    velocity.y += frameTime * GRAVITY;              // gravity
}
bool Raccoon::collidesWith(float frameTime, Entity object)
{
	bool collides=false;
	int myLowY=(getHeight()*getScale()+spriteData.y)+10;;
	int left=getCenterX()-RACCOON_HALF_WIDTH*getScale();
	int right=left+getWidth()*getScale();
	//int top=getCenterY()-RACCOON_HALF_HEIGHT*getScale();
	//just checking baseCollision
	if((left>=(object.getX()+object.getMagicNumberX()) && left<=object.getX()+object.getWidth()*object.getScale())||
		(right>=(object.getX()+object.getMagicNumberX()) && right<=object.getX()+object.getWidth()*object.getScale()))
		//checks left edge within collision width, then checks right edge.
	{
		if(myLowY>=object.getY()-object.getMagicNumberY() && myLowY<=(object.getY()+object.getHeight()*getScale()+object.getMagicNumberY()))
		{
			collides=true;
		}
	}
	return collides;
	return false;
}