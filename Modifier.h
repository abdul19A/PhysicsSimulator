#pragma once

#include "raylib.h"
#include "PhysicsWorld.h"

class Modifier
{

public:
    static const Vector3 start;
    static const Vector3 end;
    static const int width = 500;
    static const int length = 1;
    static void WorldDefaultSetup(PhysicsWorld &world);
    static void Wiggle(PhysicsWorld &world, float duration);
};

extern const Vector3 start;
extern const Vector3 end;