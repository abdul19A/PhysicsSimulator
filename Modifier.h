#pragma once

#include <raylib.h>
#include "PhysicsWorld.h"
#include "Constants.h"
class Modifier
{

public:
    static void WorldDefaultSetup(PhysicsWorld &world);
    static void Wiggle(PhysicsWorld &world, float duration);
};

extern const Vector3 start;
extern const Vector3 end;