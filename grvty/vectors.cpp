#include <math.h>
#include "vectors.h"

Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
}
Vector2D::Vector2D()
{
    this->x = 0;
    this->y = 0;
}

void Vector2D::set(float x_, float y_)
{
    this->x = x_;
    this->y = y_;
}
void Vector2D::setMag(float mag){
    float len = this->length();
    if(len != 0){
        this->x = this->x/len * mag;
        this->y = this->y/len * mag;
    }else{
        this->x = 0;
        this->y = 0;
    }
}
float Vector2D::mag(){
    return this->length();
}
float Vector2D::magSq(){
    return this->x*this->x + this->y*this->y;
}
Vector2D Vector2D::add(Vector2D v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}
Vector2D Vector2D::sub(Vector2D v)
{
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}
Vector2D Vector2D::mul(float f)
{
    this->x *= f;
    this->y *= f;
    return *this;
}
Vector2D Vector2D::div(float f)
{
    this->x /= f;
    this->y /= f;
    return *this;
}
float Vector2D::length()
{
    return sqrt(x * x + y * y);
}
Vector2D Vector2D::normalize()
{
    float l = length();
    if (l != 0)
    {
        this->x /= l;
        this->y /= l;
    }
    return *this;
}
Vector2D Vector2D::rotate(float angle)
{
    float x = this->x;
    float y = this->y;
    this->x = x * cos(angle) - y * sin(angle);
    this->y = x * sin(angle) + y * cos(angle);
    return *this;
}
Vector2D Vector2D::cross(Vector2D v)
{
    return Vector2D(this->y * v.x - this->x * v.y, this->x * v.y - this->y * v.x);
}
Vector2D Vector2D::operator+(Vector2D v)
{
    return Vector2D(this->x + v.x, this->y + v.y);
}
Vector2D Vector2D::operator-(Vector2D v)
{
    return Vector2D(this->x - v.x, this->y - v.y);
}
Vector2D Vector2D::operator*(float f)
{
    return Vector2D(this->x * f, this->y * f);
}
Vector2D Vector2D::operator/(float f)
{
    return Vector2D(this->x / f, this->y / f);
}
Vector2D Vector2D::operator-()
{
    return Vector2D(-this->x, -this->y);
}
bool Vector2D::operator==(Vector2D v)
{
    return (this->x == v.x && this->y == v.y);
}
bool Vector2D::operator!=(Vector2D v)
{
    return (this->x != v.x || this->y != v.y);
}
Vector2D Vector2D::operator=(Vector2D v)
{
    this->x = v.x;
    this->y = v.y;
    return *this;
}
Vector2D Vector2D::operator+=(Vector2D v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}
Vector2D Vector2D::operator-=(Vector2D v)
{
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}
Vector2D Vector2D::operator*=(float f)
{
    this->x *= f;
    this->y *= f;
    return *this;
}
Vector2D Vector2D::operator/=(float f)
{
    this->x /= f;
    this->y /= f;
    return *this;
}
float Vector2D::operator*(Vector2D v)
{
    return this->x * v.x + this->y * v.y;
}

// static functions

Vector2D Vector2D::sub(Vector2D v1, Vector2D v2)
{
    return Vector2D(v1.x - v2.x, v1.y - v2.y);
}
Vector2D Vector2D::add(Vector2D v1, Vector2D v2)
{
    return Vector2D(v1.x + v2.x, v1.y + v2.y);
}
Vector2D Vector2D::mul(Vector2D v, float f)
{
    return Vector2D(v.x * f, v.y * f);
}
Vector2D Vector2D::div(Vector2D v, float f)
{
    return Vector2D(v.x / f, v.y / f);
}