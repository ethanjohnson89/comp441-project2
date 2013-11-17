// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "cheeseburger.h"

//=============================================================================
// default constructor
//=============================================================================
Cheeseburger::Cheeseburger() : Still()
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
    edge.bottom = CHEESEBURGER_HALF_HEIGHT-1;
    edge.top = -CHEESEBURGER_HALF_HEIGHT;
    edge.left = -CHEESEBURGER_HALF_WIDTH;
    edge.right = CHEESEBURGER_HALF_WIDTH;
	
	mass = 10.0f; // will probably need to change this!
	collisionType = entityNS::BOX;
	magicNumberX=-18;
	magicNumberY=-20;
}

bool Cheeseburger::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Cheeseburger::update(float frameTime, bool left, bool right)
{
//	Entity::update(frameTime);
	Still::update(frameTime, left, right);
}
//bool Cheeseburger::collidesWith(float frameTime, Entity object)
//{
//	bool collides=false;
//
//		//bool collides=false;
//
//	float bottom;
//	//bottom=(JPO_HEIGHT*getScale()+spriteData.y);
//	bottom=getY()+getHeight()*getScale();// THIS WORKS. DO NOT CHANGE.
//	float top;
//	top=spriteData.y+20;
//	float left;
//	left=getX()+22;
//	float right;
//	right=getX()+CHECKPOINT_WIDTH*getScale();
//
//	float ebottom;
//	ebottom=(object.getY())+object.getHeight()*object.getScale();
//	float eleft;
//	eleft= object.getX();
//	float eright;
//	eright= object.getX() + object.getWidth()*object.getScale()-50;
//	float etop;
//	etop=ebottom+RACCOON_HEIGHT;
//
//	if(/*(ebottom<=(bottom) && ebottom>=(top))|| (etop>=top && etop<=bottom)
//		||*/ (ebottom<=bottom && etop>=bottom) || (etop>=top&&etop<=bottom))
//	{
//		if(eleft<=left && eright>=left )
//			collides = true;
//	}
//
//	return collides;
//}
