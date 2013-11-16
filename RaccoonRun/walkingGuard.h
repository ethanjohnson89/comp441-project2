#ifndef walkingGuard_h               // Prevent multiple definitions if this 
#define walkingGuard_h               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "Character.h"
#include "constants.h"

namespace walkingGuardNS
{
    const float MASS = 1.0f;
}

// inherits from Entity class
class WalkingGuard : public Character
{
public:
    // constructor
	WalkingGuard();

    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM);

    // inherited member functions
    void update(float frameTime);
	bool collidesWithRaccoon(float frameTime, Entity object);
};
#endif