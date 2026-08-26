#include "Modifier.h"

const Vector3 Modifier::start = {-299, 300, -100};
const Vector3 Modifier::end = {299, 300, 100};
void Modifier::WorldDefaultSetup(PhysicsWorld &world)
{
    // 1. Add the floor
    // world.addWall(Wall({-10.0f, -50.0f, 0.0f}, {04.0f, 0.8f, 0.0f}, {50.0f, 50.0f}, RED, 1.0f, 0.5f));

    world.GenerateBox(BoxAttrib::size);

    // ball args: Ball(position, weight, radius, color, canMove)
    // spring args: Spring(ballIndex1, ballIndex2, baseLength, springK, dampingC));

    world.GenerateNet(start, end, width, length);
    // length first
    for (int i = 0; i < length; i++)
    {
        world.getBall(i).canMove = false;
        world.getBall((width - 1) * length + i).canMove = false;
    }
}
void Modifier::Wiggle(PhysicsWorld &world, float duration)
{
    int i = 0;
    float height = sinf(duration) * 20.0f;
    float width = cosf(duration) * 20.0f;
    for (Ball &ball : world.balls)
    {
        if (!ball.canMove && i++ < length)
        {
            ball.position.y = start.y + height;
            ball.position.z = start.z + width;
        }
        else if (!ball.canMove)
        {
            ball.position.y = start.y - height;
            ball.position.z = start.z - width;
        }
    }
}