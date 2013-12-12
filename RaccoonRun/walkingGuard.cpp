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

bool WalkingGuard::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
    return(Character::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void WalkingGuard::update(float frameTime, bool left, bool right)
{
    Entity::update(frameTime);
    spriteData.x += frameTime * velocity.x;         // move along X 
    spriteData.y += frameTime * velocity.y;         // move along Y

	// Compensate for scrolling screen
	if(left)
		spriteData.x += frameTime*STILL_SPEED;
	else if(right)
		spriteData.x -= frameTime*STILL_SPEED;

    // Bounce off walls
	// Note: top-of-screen commented out since the guard will never go there
    //if (spriteData.x > GAME_WIDTH - spriteData.width)  // if hit right screen edge
    //{
    //    spriteData.x = GAME_WIDTH - spriteData.width;  // position at right screen edge
    //    turnLeft = true;
    //} else if (spriteData.x < 0)                    // else if hit left screen edge
    //{
    //    spriteData.x = 0;                           // position at left screen edge
    //    turnRight = true;
    //}
    if (spriteData.y > GAME_HEIGHT - spriteData.height) // if hit bottom screen edge
    {
        spriteData.y = GAME_HEIGHT - spriteData.height; // position at bottom screen edge
        velocity.y = 0;
    } /*else if (spriteData.y < 0)                    // else if hit top screen edge
    {
        spriteData.y = 0;                           // position at top screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    }*/

	if(turnLeft)
	{
		velocity.x = -velocity.x;                   // reverse X direction
		setFrames(JPO_WALKING_LEFT_START, JPO_WALKING_LEFT_END);
		turnLeft = false;
	}
	else if(turnRight)
	{
		velocity.x = -velocity.x;                   // reverse X direction
		setFrames(JPO_WALKING_RIGHT_START, JPO_WALKING_RIGHT_END);
		turnRight = false;
	}

    velocity.y += frameTime * GRAVITY;              // gravity
}
bool WalkingGuard::collidesWithRaccoon(float frameTime, Entity object)
{
	//ONLY USE THIS WITH RACCOON.
	bool collides=false;

	float bottom;
	//bottom=(JPO_HEIGHT*getScale()+spriteData.y);
	bottom=getY()+getHeight()*getScale();// THIS WORKS. DO NOT CHANGE.
	float top;
	top=spriteData.y+20;
	float left;
	left=getX()+22;
	float right;
	right=getX()+JPO_WIDTH*getScale();

	float ebottom;
	ebottom=(object.getY())+object.getHeight()*object.getScale();
	float eleft;
	eleft= object.getX();
	float eright;
	eright= object.getX() + object.getWidth()*object.getScale()-50;
	float etop;
	etop=ebottom+RACCOON_HEIGHT;

	if(ebottom<=bottom && ebottom>=(top+40))
	{
		if(eleft<=left && eright>=left)
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

void WalkingGuard::ai(Raccoon *player)
{
	// If the raccoon is within reach of the guard (>= 400 px from the top of the screen), the guard will run directly toward him.
	// Otherwise, the guard will pace back and forth, waiting for the racoon to come down from the trees.
	// He will run at full speed when the racoon is on the ground, and pace more slowly while he's in the trees.
	if(player->getY() >= 400)
	{
		if(spriteData.x < player->getX() && velocity.x < 0)
			turnRight = true;
		else if(spriteData.x > player->getX() && velocity.x > 0)
			turnLeft = true;

		if(velocity.x >= 0)
			velocity.x = JPO_PROXIMITY_SPEED;
		else
			velocity.x = -JPO_PROXIMITY_SPEED;
	}
	else
	{
		if(abs(spriteData.x - player->getX()) > JPO_PROXIMITY_DISTANCE)
			if(spriteData.x < player->getX() && velocity.x < 0)
				turnRight = true;
			else if(spriteData.x > player->getX() && velocity.x > 0)
				turnLeft = true;

		if(velocity.x >= 0)
			velocity.x = JPO_SPEED;
		else
			velocity.x = -JPO_SPEED;
	}

	/*if(abs(spriteData.x - player->getX()) > JPO_PROXIMITY_DISTANCE)
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
	}*/
}

//bool WalkingGuard::setCurrentStep(PatternStep step)
//{
//	if(currentStep == step)
//		return false;
//	currentStep = step;
//	return true;
//}