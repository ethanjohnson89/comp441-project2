// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "walkingGuard.h"

//=============================================================================
// default constructor
//=============================================================================
WalkingGuard::WalkingGuard() : Character()
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
	startFrame = JPO_LOOKING_RIGHT_START;
	endFrame=JPO_LOOKING_RIGHT_START;
	currentFrame = startFrame;
	
	mass = 10.0f; // will probably need to change this!
	collisionType = entityNS::BOX;

	//added by Christy. For Raccoon, obviously.
	magicNumberX=0;
	magicNumberY=0;
}

bool WalkingGuard::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
    return(Character::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void WalkingGuard::update(float frameTime)
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
bool WalkingGuard::collidesWith(float frameTime, Entity object)
{
	bool collides=false;

	float bottom;
	//bottom=(JPO_HEIGHT*getScale()+spriteData.y);
	bottom=getY()+getHeight()*getScale();// THIS WORKS. DO NOT CHANGE.
	float top;
	top=spriteData.y+20;
	float left;
	left=getX();
	float right;
	right=getCenterY()+(JPO_WIDTH*getScale()/2);

	float ebottom;
	ebottom=(object.getY())+object.getHeight()*object.getScale();
	float eleft;
	eleft= object.getX()/* - object.getWidth()*object.getScale()/2*/;
	float eright;
	eright= object.getX() + object.getWidth()*object.getScale();

	///*if(ebottom<=bottom)
	//	return true;*/
	//if(ebottom>=top)
	//	return true;
	if(ebottom<=bottom && ebottom>=top)
	{
		if(eleft>=left)
			return true;
		else
			return false;
	}

	//if(ebottom<=bottom && ebottom>=top)
	//{
	//	if((eleft>=left && eleft<=right))
	//		collides=true;
	//	else
	//		collides=false;
	//}

	//int myLowY=(getHeight()*getScale()+spriteData.y);
	//int left=getCenterX()-JPO_WIDTH*getScale()/2;
	//int right=left+getWidth()*getScale();
	////int top=getCenterY()-RACCOON_HALF_HEIGHT*getScale();
	////just checking baseCollision
	//if((left>=(object.getX()+object.getMagicNumberX()) && left<=object.getX()+object.getWidth()*object.getScale())||
	//	(right>=(object.getX()+object.getMagicNumberX()) && right<=object.getX()+object.getWidth()*object.getScale()))
	//	//checks left edge within collision width, then checks right edge.
	//{
	//	if(myLowY>=object.getY()-object.getMagicNumberY() && myLowY<=(object.getY()+object.getHeight()*getScale()+object.getMagicNumberY()))
	//	{
	//		collides=true;
	//	}
	//}
	return collides;
}