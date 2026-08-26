#include "PhysicsWorld.h"

void PhysicsWorld::GenerateBox(float size)
{
    addWall(Wall({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {size, size}, BoxAttrib::colors[0], 1.0f, 1.0f));
    addWall(Wall({size, size, 0.0f}, {-1.0f, 0.0f, 0.0f}, {size, size}, BoxAttrib::colors[1], 1.0f, 1.0f));
    addWall(Wall({-size, size, 0.0f}, {1.0f, 0.0f, 0.0f}, {size, size}, BoxAttrib::colors[2], 1.0f, 1.0f));
    addWall(Wall({0.0f, size, size}, {0.0f, 0.0f, -1.0f}, {size, size}, BoxAttrib::colors[3], 1.0f, 1.0f));
    addWall(Wall({0.0f, size, -size}, {0.0f, 0.0f, 1.0f}, {size, size}, BoxAttrib::colors[4], 1.0f, 1.0f));
    addWall(Wall({0.0f, 2 * size, 0.0f}, {0.0f, -1.0f, 0.0f}, {size, size}, BoxAttrib::colors[5], 1.0f, 1.0f));
}

void PhysicsWorld::GenerateNet(Vector3 start, Vector3 end, int width, int length)
{
    float du, dv;
    if (width < 2)
        du = 0;
    else
    {
        du = (end.x - start.x) / (width - 1);
    }
    if (length < 2)
    {
        dv = 0;
    }
    else
    {
        dv = (end.z - start.z) / (length - 1);
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < length; j++)
        {
            Vector3 pos = start;
            pos.x += du * static_cast<float>(i);
            pos.z += dv * static_cast<float>(j);

            addBall(Ball(pos, NetAttrib::ballWeight, NetAttrib::ballRadius, GRAY, true));
            int index = j + i * length;
            if (j < length - 1)
                addSpring(Spring(index, index + 1, dv * NetAttrib::springSize, NetAttrib::springK, NetAttrib::springC));
            if (i < width - 1)
                addSpring(Spring(index, index + length, du * NetAttrib::springSize, NetAttrib::springK, NetAttrib::springC));
        }
    }
    getBall(0).canMove = false;
    getBall(length - 1).canMove = false;
    getBall(width * length - 1).canMove = false;
    getBall((width - 1) * length).canMove = false;
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

        ball.ApplyGravity(Constants::gravity);
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
        } while (ball.collided == true && ++loopGaurd < Gaurd::collisionLoop);
        ball.VelocityToPosition(remaining_dt);

        ball.ResetForce();
    }
}

void PhysicsWorld::Draw()
{
    if (CanDraw::ball)
        for (const Ball &ball : balls)
        {
            ball.Draw();
        }
    if (CanDraw::spring)
        for (Spring &spring : springs)
        {
            spring.Draw(balls);
        }
    if (CanDraw::wall)
        for (const Wall &wall : walls)
        {
            wall.Draw();
        }
    if (CanDraw::plane)
        DrawGrid(10, BoxAttrib::size / 5.0f);
}
