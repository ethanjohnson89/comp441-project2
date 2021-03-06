// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "phillips.h"

//=============================================================================
// default constructor
//=============================================================================
Checkpoint::Checkpoint() : Still()
{
	//still life should know where its world coordinates are. 
	//maybe send it a bool in update telling it whether to move left / right?
	// Right now these are hardcoded for JPo - later we'll be deriving classes from this for specific characters
	//spriteData.width = JPO_WIDTH;
	//spriteData.height = JPO_HEIGHT;
	//spriteData.x = GAME_WIDTH/4;
	//spriteData.y = GAME_HEIGHT - (GAME_HEIGHT/3);
	//spriteData.rect.bottom = JPO_HEIGHT;
	//spriteData.rect.right = JPO_WIDTH;
	//velocity.x = 0;
	//velocity.y = 0;
	//frameDelay = JPO_ANIMATION_DELAY;
	//startFrame = JPO_LOOKING_RIGHT_START;
	//endFrame = JPO_LOOKING_RIGHT_END;
	//currentFrame = startFrame;

	// Collision box
    edge.bottom = -CHECKPOINT_HEIGHT/2-1/*PLATFORM_HALF_HEIGHT-1*/; // same as top so that he only collides from the top
    edge.top = -CHECKPOINT_HEIGHT/2;
    edge.left = -CHECKPOINT_WIDTH/2;
    edge.right = CHECKPOINT_WIDTH/2;
	
	mass = 10.0f; // will probably need to change this!
	collisionType = entityNS::BOX;
	magicNumberX=50;
	magicNumberY=10;
}

bool Checkpoint::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
//void Platform::update(float frameTime, bool left, bool right)
//{
//	//needs a move-left / move-right bool. If received, will move the still object either left or right. 
//    Entity::update(frameTime);
//	if(left)
//	{
//		spriteData.x--;
//	}
//	else if(right)
//	{
//		spriteData.x++;
//	}
//    //spriteData.x += frameTime * velocity.x;         // move along X 
//    //spriteData.y += frameTime * velocity.y;         // move along Y
//}
bool Checkpoint::collidesWith(float frameTime, Entity object)
{
	bool collides=false;

		//bool collides=false;

	float bottom;
	//bottom=(JPO_HEIGHT*getScale()+spriteData.y);
	bottom=getY()+getHeight()*getScale();// THIS WORKS. DO NOT CHANGE.
	float top;
	top=spriteData.y/*+20*/;
	float left;
	left=getX()/*+22*/;
	float right;
	right=getX()+CHECKPOINT_WIDTH*getScale();

	float ebottom;
	ebottom=(object.getY())+object.getHeight()*object.getScale();
	float eleft;
	eleft= object.getX();
	float eright;
	eright= object.getX() + object.getWidth()*object.getScale()-50;
	float etop;
	etop=ebottom+RACCOON_HEIGHT;

	if((ebottom<=(bottom+10) && ebottom>=(top-10))|| (etop>=bottom && etop<=bottom))
	{
		if(/*eleft<=left && eright>=left*/eright>=left)
			return true;
		//else
			//return false;
	}

	return collides;
}

/****************************************************
****frisbee stuff************************************
*****************************************************/
void Frisbee::update(float frameTime)
{
	if(spriteData.x<=GAME_WIDTH)
	{
		//setVisible(true);
		spriteData.x+=velocity.x;
		//velocity.y=1;
		if(spriteData.x>=0-FRISBEE_WIDTH*getScale())
			spriteData.y+=velocity.y;
	}
	else
	{
		reset();
	}
	if(spriteData.y>=GAME_HEIGHT-getHeight())
		reset();
	
}
void Frisbee::reset()
{
	spriteData.x=-3000;
	spriteData.y=300;
	setVisible(false);
}
