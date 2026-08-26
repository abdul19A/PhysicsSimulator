#include "Ball.h"

void Ball::Draw() const
{
    DrawSphere(position, radius, color);
}