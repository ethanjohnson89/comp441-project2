#ifndef platform_h               // Prevent multiple definitions if this 
#define platform_h               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

//#include "entity.h"
#include "Still.h"
#include "constants.h"

namespace platformNS
{
    //const float MASS = 1.0f;
	//const float WIDTH 
}

// inherits from Entity class
class Platform : public Still
{

public:
    // constructor
	Platform();

    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM);

    // inherited member functions
    //void update(float frameTime, bool left, bool right);
};
#endif