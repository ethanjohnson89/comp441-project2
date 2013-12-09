#ifndef DrehmanLaser_h               // Prevent multiple definitions if this 
#define DrehmanLaser_h               // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
//#include "Still.h"
#include "constants.h"

namespace laserNS
{
    //const float MASS = 1.0f;
	//const float WIDTH 
}

// inherits from Entity class
class Laser : public Entity//Still
{

public:
    // constructor
	Laser();

    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM);

    // inherited member functions
    void update(float frameTime, bool left, bool right);
	void setRight(bool Right){right = Right;}
	bool getRight(){return right;}

	//bool collidesWith(float frameTime, Entity object);
	float getX(){return spriteData.x;}
	float getY(){return spriteData.y;}
	bool incrementCounter();
private:
	bool right;
	bool firing;
	int counter;
//	const int COUNTER_MAX = 100;
};

#endif