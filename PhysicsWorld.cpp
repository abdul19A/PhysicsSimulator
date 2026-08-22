#include "PhysicsWorld.h"

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
        float cur_dt = dt;
        for (Wall &wall : walls)
        {
            cur_dt = wall.WallCollideBall(ball, cur_dt);
        }
        ball.VelocityToPosition(cur_dt);
        ball.ResetForce();
    }
}

void PhysicsWorld::Draw()
{
    for (const Ball &ball : balls)
    {
        DrawSphere(ball.position, ball.radius, ball.color);
        DrawSphereWires(ball.position, ball.radius * 1.02f, 10, 10, WHITE);
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
