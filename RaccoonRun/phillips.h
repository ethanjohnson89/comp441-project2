#ifndef phillips_h               // Prevent multiple definitions if this 
#define phillips_h               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//#include "entity.h"
#include "Still.h"
#include "constants.h"
#include "image.h"


namespace checkpointNS
{
    //const float MASS = 1.0f;
	//const float WIDTH 
}

// inherits from Entity class
class Checkpoint : public Still
{

public:
    // constructor
	Checkpoint();

    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM);

	bool collidesWith(float frameTime, Entity object);
    // inherited member functions
    //void update(float frameTime, bool left, bool right);
};

#endif