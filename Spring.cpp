#include "Spring.h"

void Spring::Draw(const std::vector<Ball> &balls)
{
    float colorT = std::clamp(Constants::springColorSensitivity / (std::abs(stretch) + 1), 0.0f, 1.0f);
    color = ColorLerp(RED, GREEN, colorT);
    DrawLine3D(balls.at(topIndex).position,
               balls.at(botIndex).position,
               color);
}
void Spring::ApplyForce(std::vector<Ball> &balls)
{
    if (isBroken)
        return;
    Ball &topBall = balls.at(topIndex);
    Ball &botBall = balls.at(botIndex);
    if (!topBall.canMove && !botBall.canMove)
        return;

    Vector3 topPos = topBall.position;
    Vector3 botPos = botBall.position;

    float dx = topPos.x - botPos.x;
    float dy = topPos.y - botPos.y;
    float dz = topPos.z - botPos.z;

    float currentLength = std::sqrt(dx * dx + dy * dy + dz * dz);

    if (currentLength < 1e-6f)
        return;

    // 3D Unit vector pointing from botBall to topBall
    float ux = dx / currentLength;
    float uy = dy / currentLength;
    float uz = dz / currentLength;

    // Hooke's Law: F_spring = -k * dx
    stretch = currentLength - baseLength;
    if (stretch > Constants::springLimit && Constants::springCanBreak)
    {
        isBroken = true;
        return;
    }

    float springForceMag = -k * stretch;

    // Damping Force: F_damping = -c * (relative velocity dot unit vector)

    float relVelX = topBall.velocity.x - botBall.velocity.x;
    float relVelY = topBall.velocity.y - botBall.velocity.y;
    float relVelZ = topBall.velocity.z - botBall.velocity.z;

    float velAlongAxis = relVelX * ux + relVelY * uy + relVelZ * uz;
    float dampingForceMag = -c * velAlongAxis;

    float totalForceMag = springForceMag + dampingForceMag;

    if (!topBall.canMove || !botBall.canMove)
        totalForceMag *= 2;

    Vector3 netSpringForce = {
        totalForceMag * ux,
        totalForceMag * uy,
        totalForceMag * uz};

    // Apply equal and opposite 3D forces using Ball's ApplyForce helper
    if (topBall.canMove)
        topBall.ApplyForce(netSpringForce);
    if (botBall.canMove)
        botBall.ApplyForce({-netSpringForce.x, -netSpringForce.y, -netSpringForce.z});
}