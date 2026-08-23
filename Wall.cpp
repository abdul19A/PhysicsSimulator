#include "Wall.h"

Wall::Wall(Vector3 pos, Vector3 norm, Vector2 sz, Color color, float friction, float bounce)
    : position(pos), normal(Vector3Normalize(norm)), size(sz), color(color), frictionCoef(friction), bounceCoef(bounce)
{
    // Generate orthonormal basis vectors (right and up) for the plane surface
    Vector3 upGuide = {0.0f, 1.0f, 0.0f};

    // If the normal is pointing straight up/down, use Z as the up-guide
    if (std::abs(normal.y) > 0.99f)
    {
        upGuide = {0.0f, 0.0f, -1.0f};
    }

    Vector3 right = Vector3Normalize(Vector3CrossProduct(normal, upGuide));
    Vector3 up = Vector3Normalize(Vector3CrossProduct(right, normal));

    corners[0] = Vector3Add(Vector3Scale(right, size.x), Vector3Scale(up, -size.y));
    corners[1] = Vector3Add(Vector3Scale(right, -size.x), Vector3Scale(up, -size.y));
    corners[2] = Vector3Add(Vector3Scale(right, -size.x), Vector3Scale(up, size.y));
    corners[3] = Vector3Add(Vector3Scale(right, size.x), Vector3Scale(up, size.y));

    for (int i = 0; i < 4; i++)
    {
        corners[i] = Vector3Add(position, corners[i]);
    }
}

void Wall::Draw() const
{
    DrawTriangle3D(corners[0], corners[1], corners[2], color);
    DrawTriangle3D(corners[2], corners[3], corners[0], color);
    DrawTriangle3D(corners[2], corners[1], corners[0], color);
    DrawTriangle3D(corners[0], corners[3], corners[2], color);

    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            DrawLine3D(corners[i], corners[j], WHITE);
        }
    }
}
float Wall::GetSignedDistance(Ball &ball)
{
    return Vector3DotProduct(
        Vector3Subtract(ball.position, position),
        normal);
}
float Wall::WallCollideBall(Ball &ball, float dt) const
{

    Vector3 p0 = Vector3Subtract(ball.position, position);
    float separation = Vector3DotProduct(p0, normal) - ball.radius;
    float velNormProduct = Vector3DotProduct(ball.velocity, normal);
    if (separation <= 0.0f)
    {
        ball.position = Vector3Add(ball.position, Vector3Scale(normal, -separation));

        if (velNormProduct < 0.0f)
        {
            ball.velocity = Vector3Subtract(
                Vector3Scale(ball.velocity, frictionCoef),
                Vector3Scale(normal, velNormProduct * (frictionCoef + bounceCoef)));
        }
        return dt;
    }

    if (velNormProduct >= 0.0f)
        return dt; // early out + root out weird collisions

    float t = -separation / velNormProduct;

    if (t > dt || t < 0.0f)
        return dt;

    ball.collided = true;

    ball.position = Vector3Add(
        ball.position,
        Vector3Scale(ball.velocity, t));

    ball.velocity = Vector3Subtract(
        Vector3Scale(ball.velocity, frictionCoef),
        Vector3Scale(normal, velNormProduct * (frictionCoef + bounceCoef)));

    return dt - t;
}
