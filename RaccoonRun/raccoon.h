#ifndef raccoon_h               // Prevent multiple definitions if this 
#define raccoon_h               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "Character.h"
#include "constants.h"

namespace raccoonNS
{
    const float MASS = 1.0f;
}

// inherits from Entity class
class Raccoon : public Character
{
public:
    // constructor
	Raccoon();

    void update(float frameTime);

	bool onLand;
};
#endif