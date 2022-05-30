#pragma once
#include "vectors.h"

class Object
{
    public:
    float mass;
    float G = 6.67408e-11;
    float G_Experimental = 100;
    Vector2D pos,vel, acc;
    Object(float, float, float);
    Object();
    void update(); // update position
    void applyForce(Vector2D); // apply force to acceleration
    void attract(Object*); // attract other object
    float constrain(float, float, float); // constrain value between min and max
};