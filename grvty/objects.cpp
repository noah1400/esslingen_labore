#include "objects.h"
#include "vectors.h"
#include <iostream>

Object::Object(float x, float y, float m)
{
    this->pos = Vector2D(x, y);
    this->vel = Vector2D(0, 0);
    this->acc = Vector2D(0, 0);
    this->mass = m;
}
Object::Object(){}

void Object::update()
{
    this->vel.add(this->acc);
    this->pos.add(this->vel);
    this->acc.set(0,0);
}

void Object::applyForce(Vector2D force)
{
    this->acc.add(force.div(this->mass));
}

void Object::attract(Object *obj)
{
    Vector2D force = Vector2D::sub(this->pos, obj->pos);
    float distanceSq = constrain(force.magSq(),100,1000);
    float strength = (this->G_Experimental * this->mass * obj->mass) / distanceSq;
    force.setMag(strength);
    obj->applyForce(force);
}

float Object::constrain(float val, float min, float max)
{
    if(val < min)
        return min;
    if(val > max)
        return max;
    return val;
}