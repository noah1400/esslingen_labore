#pragma once

class Vector2D
{
    public:
    float x,y;
    Vector2D(float, float);
    Vector2D();
    void set(float, float);
    void setMag(float);
    float mag();
    float magSq();
    Vector2D add(Vector2D);
    Vector2D sub(Vector2D);
    Vector2D mul(float);
    Vector2D div(float);
    float length();
    Vector2D normalize();
    Vector2D rotate(float);
    Vector2D cross(Vector2D);
    Vector2D operator+(Vector2D);
    Vector2D operator-(Vector2D);
    Vector2D operator*(float);
    Vector2D operator/(float);
    Vector2D operator-();
    bool operator==(Vector2D);
    bool operator!=(Vector2D);
    Vector2D operator=(Vector2D);
    Vector2D operator+=(Vector2D);
    Vector2D operator-=(Vector2D);
    Vector2D operator*=(float);
    Vector2D operator/=(float);
    float operator*(Vector2D);

    static Vector2D sub(Vector2D, Vector2D);
    static Vector2D add(Vector2D, Vector2D);
    static Vector2D mul(Vector2D, float);
    static Vector2D div(Vector2D, float);
};