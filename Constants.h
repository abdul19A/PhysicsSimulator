#pragma once

#include <raylib.h>
#include "CameraController.h"

class BgAttrib
{
public:
    static Color color;
};

class ScreenAttrib
{
public:
    static const int width;
    static const int height;
    static const int targetFPS;
};

class Constants
{
public:
    static const float gravity;
    static const int stepsPerFrame;
    static const float springColorSensitivity;
    static const float springLimit;
    static const bool springCanBreak;
};

class NetAttrib
{
public:
    static const float springK; // Higher stiffness helps hold up longer chains
    static const float springC; // Keeps the chain from oscillating infinitely
    static const float ballWeight;
    static const float ballRadius;
    static Vector3 start;
    static Vector3 end;
    static const int width;
    static const int length;
    static const float springSize;
};

class CanDraw
{
public:
    static const bool ball;
    static const bool spring;
    static const bool wall;
    static const bool plane;
};

class Gaurd
{
public:
    static const int collisionLoop;
};

class BoxAttrib
{
public:
    static Color colors[6];
    static const float size;
};
