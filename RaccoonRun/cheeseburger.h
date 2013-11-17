#ifndef cheeseburger_h               // Prevent multiple definitions if this 
#define cheeseburger_h               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//#include "entity.h"
#include "Still.h"
#include "constants.h"

namespace cheeseburgerNS
{
    //const float MASS = 1.0f;
	//const float WIDTH 
}

// inherits from Entity class
class Cheeseburger : public Still
{

public:
    // constructor
	Cheeseburger();

    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM);

    // inherited member functions
    void update(float frameTime, bool left, bool right);
	bool collidesWith(float frameTime, Entity object);
	float getX(){return spriteData.x;}
	float getY(){return spriteData.y;}
};
#endif