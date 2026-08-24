#include "PhysicsConfig.h"

void setUpWorldDefault(PhysicsWorld &world)
{
    // 1. Add the floor
    // world.addWall(Wall({-10.0f, -50.0f, 0.0f}, {04.0f, 0.8f, 0.0f}, {50.0f, 50.0f}, RED, 1.0f, 0.5f));

    world.GenerateBox(300.0f);

    // ball args: Ball(position, weight, radius, color, canMove)
    // spring args: Spring(ballIndex1, ballIndex2, baseLength, springK, dampingC));

    Vector3 start = {-100, 150, -100};
    Vector3 end = {100, 150, 100};
    int width = 11;
    int length = 11;
    world.GenerateNet(start, end, width, length);
}

Config config;
PhysicsWorld configPhysicsWorld;
