#include "Ball.h"

// ==========================================
// Ball Implementation
// ==========================================
void Ball::Draw() const
{
    DrawSphere(position, radius, color);
    // DrawSphereWires(ball.position, ball.radius * 1.01f, 5, 3, WHITE);
}