#include "PhysicsWorld.h"

void PhysicsWorld::GenerateBox(float size)
{
    addWall(Wall({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {size, size}, BLUE, 1.0f, 1.0f));
    addWall(Wall({size, size, 0.0f}, {-1.0f, 0.0f, 0.0f}, {size, size}, RED, 1.0f, 1.0f));
    addWall(Wall({-size, size, 0.0f}, {1.0f, 0.0f, 0.0f}, {size, size}, YELLOW, 1.0f, 1.0f));
    addWall(Wall({0.0f, size, size}, {0.0f, 0.0f, -1.0f}, {size, size}, GREEN, 1.0f, 1.0f));
    addWall(Wall({0.0f, size, -size}, {0.0f, 0.0f, 1.0f}, {size, size}, ORANGE, 1.0f, 1.0f));
    addWall(Wall({0.0f, 2 * size, 0.0f}, {0.0f, -1.0f, 0.0f}, {size, size}, PURPLE, 1.0f, 1.0f));
}

void PhysicsWorld::GenerateNet(Vector3 start, Vector3 end, int width, int length)
{
    const float restLength = 0.0f;
    const float springK = 500.0f; // Higher stiffness helps hold up longer chains
    const float dampingC = 10.5;  // Keeps the chain from oscillating infinitely
    const float weight = 0.1f;
    const float radius = 1.0f;

    if (width < 2)
        return;

    float du = (end.x - start.x) / (width - 1);
    float dv = (end.z - start.z) / (length - 1);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < length; j++)
        {
            Vector3 pos = start;
            pos.x += du * static_cast<float>(i);
            pos.z += dv * static_cast<float>(j);

            addBall(Ball(pos, weight, radius, GRAY, true));
            int index = j + i * length;
            if (j < length - 1)
                addSpring(Spring(index, index + 1, dv, springK, dampingC));
            if (i < width - 1)
                addSpring(Spring(index, index + length, du, springK, dampingC));
        }
    }
    getBall(0).canMove = false;
    getBall(length - 1).canMove = false;
    getBall(width * length - 1).canMove = false;
    getBall(width * (length - 1)).canMove = false;
}
void PhysicsWorld::ApplyForces(float dt)
{
    for (Spring &spring : springs)
    {
        spring.ApplyForce(balls);
    }

    for (Ball &ball : balls)
    {
        if (!ball.canMove)
            continue;

        ball.ApplyGravity(9.81f);
        ball.ForceToVelocity(dt);
        float remaining_dt = dt;
        int loopGaurd = 0;
        do
        {
            ball.collided = false;
            for (const Wall &wall : walls)
            {
                remaining_dt = wall.WallCollideBall(ball, remaining_dt);
            }
        } while (ball.collided == true && ++loopGaurd < 4);

        ball.VelocityToPosition(remaining_dt);

        ball.ResetForce();
    }
}

void PhysicsWorld::Draw()
{
    for (const Ball &ball : balls)
    {
        DrawSphere(ball.position, ball.radius, ball.color);
        // DrawSphereWires(ball.position, ball.radius * 1.01f, 5, 3, WHITE);
    }
    for (const Spring &spring : springs)
    {
        DrawLine3D(balls.at(spring.topIndex).position,
                   balls.at(spring.botIndex).position,
                   spring.color);
    }
    for (const Wall &wall : walls)
    {
        wall.Draw();
    }
}

void PhysicsWorld::OnExit()
{
    std::cout << "SAVING INFO: Writing to file..." << std::endl;

    if (BallForce.WriteToFile())
    {
        std::cout << "SAVING INFO: writing complete!" << std::endl;
    }
    else
    {
        std::cout << "SAVING INFO: error writing" << std::endl;
    }
}
