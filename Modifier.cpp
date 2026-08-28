#include "Modifier.h"

void Modifier::WorldDefaultSetup(PhysicsWorld &world)
{

    world.GenerateBox(BoxAttrib::size);
    world.GenerateNet(NetAttrib::start,
                      NetAttrib::end,
                      NetAttrib::width,
                      NetAttrib::length);
    // ball args: Ball(position, weight, radius, color, canMove)
    // spring args: Spring(ballIndex1, ballIndex2, baseLength, springK, dampingC));
    // length first
    world.getBall(0).canMove = false;
    for (int i = 0; i < NetAttrib::length; i++)
    {
        world.getBall(i).canMove = false;
        world.getBall(i + (NetAttrib::width - 1) * NetAttrib::length).canMove = false;
    }
    for (int i = 0; i < NetAttrib::width * NetAttrib::length; i += NetAttrib::length)
    {
        world.getBall(i).canMove = false;
        world.getBall(i + NetAttrib::length - 1).canMove = false;
    }
    world.getBall(NetAttrib::width * NetAttrib::length - 1).canMove = false;
}
void Modifier::Wiggle(PhysicsWorld &world, float duration)
{
    int i = 0;
    float height = sinf(duration) * 20.0f;
    float width = cosf(duration) * 20.0f;
    for (Ball &ball : world.balls)
    {
        if (!ball.canMove && i++ < NetAttrib::length)
        {
            ball.position.y = NetAttrib::start.y + height;
            ball.position.z = NetAttrib::start.z + width;
        }
        else if (!ball.canMove)
        {
            ball.position.y = NetAttrib::start.y - height;
            ball.position.z = NetAttrib::start.z - width;
        }
    }
}