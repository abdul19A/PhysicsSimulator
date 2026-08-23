#include "PhysicsConfig.h"

void setUpWorldDefault(PhysicsWorld &world)
{
    // 1. Add the floor
    world.addWall(Wall({-10.0f, -50.0f, 0.0f}, {04.0f, 0.8f, 0.0f}, {50.0f, 50.0f}, RED, 1.0f, 0.5f));
    world.addWall(Wall({0.0f, -10.0f, 50.0f}, {-0.2f, 0.8f, 0.0f}, {150.0f, 150.0f}, BLUE, 1.0f, 0.0f));
    //   Spring parameters
    // const float restLength = 0.0f;
    // const float springK = .0f;  // Higher stiffness helps hold up longer chains
    // const float dampingC = 0.0; // Keeps the chain from oscillating infinitely
    const float weight = 10.0f;
    const float radius = 0.5f;
    // ball args: Ball(position, weight, radius, color, canMove)
    // spring args: Spring(ballIndex1, ballIndex2, baseLength, springK, dampingC));
    world.addBall(Ball({0.0f, 0.5f, 0.0f}, weight, radius, BLUE, true));
    // world.addBall(Ball({3.0f, 1.0f, 2.0f}, weight, 0.05, RED, false));

    // world.addSpring(Spring(0, 1, restLength, springK, dampingC));
}

Config config;
PhysicsWorld configPhysicsWorld;
