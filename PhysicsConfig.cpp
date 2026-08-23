#include "PhysicsConfig.h"

void setUpWorldDefault(PhysicsWorld &world)
{
    // 1. Add the floor
    // world.addWall(Wall({-10.0f, -50.0f, 0.0f}, {04.0f, 0.8f, 0.0f}, {50.0f, 50.0f}, RED, 1.0f, 0.5f));
    world.addWall(Wall({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {150.0f, 150.0f}, BLUE, 1.0f, 1.0f));
    world.addWall(Wall({150.0f, 150.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}, {150.0f, 150.0f}, RED, 1.0f, 1.0f));
    world.addWall(Wall({-150.0f, 150.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {150.0f, 150.0f}, YELLOW, 1.0f, 1.0f));
    world.addWall(Wall({0.0f, 150.0f, 150.0f}, {0.0f, 0.0f, -1.0f}, {150.0f, 150.0f}, GREEN, 1.0f, 1.0f));
    world.addWall(Wall({0.0f, 150.0f, -150.0f}, {0.0f, 0.0f, 1.0f}, {150.0f, 150.0f}, ORANGE, 1.0f, 1.0f));
    world.addWall(Wall({0.0f, 300.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {150.0f, 150.0f}, PURPLE, 1.0f, 1.0f));
    //   Spring parameters
    const float restLength = 0.0f;
    const float springK = 0.50f; // Higher stiffness helps hold up longer chains
    const float dampingC = 0.0;  // Keeps the chain from oscillating infinitely
    const float weight = 10.0f;
    const float radius = 1.0f;
    // ball args: Ball(position, weight, radius, color, canMove)
    // spring args: Spring(ballIndex1, ballIndex2, baseLength, springK, dampingC));

    for (float x = -100.0f; x <= 100.0f; x += 10.0f)
    {
        for (float z = -100.0f; z <= 100.0f; z += 10.0f)
        {
            world.addBall(Ball({x, 100.0f, z}, weight, radius, GRAY, true));
        }
    } // 11 x 11
    for (int x = 0; x < 21; x++)
    {
        for (int z = 0; z < 21; z++)
        {
            if (x < 20)
                world.addSpring(Spring(z * 21 + x, z * 21 + x + 1, 10.0f, springK, dampingC));
            if (z < 20)
                world.addSpring(Spring(z * 21 + x, (z + 1) * 21 + x, 10.0f, springK, dampingC));
        }
    }
    world.getBall(0).canMove = false;
    world.getBall(21 - 1).canMove = false;
    world.getBall(21 * 21 - 21).canMove = false;
    world.getBall(21 * 21 - 1).canMove = false;
}

Config config;
PhysicsWorld configPhysicsWorld;
