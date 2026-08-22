#include "Wall.h"

Wall::Wall(Vector3 pos, Vector3 norm, Vector2 sz, float friction, float bounce)
    : position(pos), normal(Vector3Normalize(norm)), size(sz), frictionCoef(friction), bounceCoef(bounce)
{
    // Generate orthonormal basis vectors (right and up) for the plane surface
    Vector3 upGuide = {0.0f, 1.0f, 0.0f};

    // If the normal is pointing straight up/down, use Z as the up-guide
    if (std::abs(normal.y) > 0.99f)
    {
        upGuide = {0.0f, 0.0f, -1.0f};
    }

    right = Vector3Normalize(Vector3CrossProduct(normal, upGuide));
    up = Vector3Normalize(Vector3CrossProduct(right, normal));
}

void Wall::Draw() const
{
    Vector3 halfRight = Vector3Scale(right, size.x * 0.5f);
    Vector3 halfUp = Vector3Scale(up, size.y * 0.5f);

    Vector3 bl = Vector3Subtract(Vector3Subtract(position, halfRight), halfUp);
    Vector3 br = Vector3Subtract(Vector3Add(position, halfRight), halfUp);
    Vector3 tr = Vector3Add(Vector3Add(position, halfRight), halfUp);
    Vector3 tl = Vector3Add(Vector3Subtract(position, halfRight), halfUp);

    rlBegin(RL_QUADS);
    rlColor4ub(200, 100, 50, 255);
    rlNormal3f(normal.x, normal.y, normal.z);
    rlVertex3f(tl.x, tl.y, tl.z);
    rlVertex3f(tr.x, tr.y, tr.z);
    rlVertex3f(br.x, br.y, br.z);
    rlVertex3f(bl.x, bl.y, bl.z);
    rlEnd();

    // --- Grid overlay ---
    float cellSize = 1.0f; // world units per grid cell — tweak to taste
    float lift = 0.01f;    // nudge lines slightly off the surface to avoid z-fighting

    Vector3 offset = Vector3Scale(normal, lift);

    rlBegin(RL_LINES);
    rlColor4ub(0, 0, 0, 120);

    // lines running along 'up', stepping across 'right'
    int stepsX = (int)(size.x / cellSize);
    for (int i = 0; i <= stepsX; i++)
    {
        float t = (float)i / stepsX;
        Vector3 base = Vector3Add(bl, Vector3Scale(Vector3Subtract(br, bl), t));
        Vector3 top = Vector3Add(tl, Vector3Scale(Vector3Subtract(tr, tl), t));
        base = Vector3Add(base, offset);
        top = Vector3Add(top, offset);
        rlVertex3f(base.x, base.y, base.z);
        rlVertex3f(top.x, top.y, top.z);
    }

    // lines running along 'right', stepping across 'up'
    int stepsY = (int)(size.y / cellSize);
    for (int i = 0; i <= stepsY; i++)
    {
        float t = (float)i / stepsY;
        Vector3 left = Vector3Add(bl, Vector3Scale(Vector3Subtract(tl, bl), t));
        Vector3 rightEdge = Vector3Add(br, Vector3Scale(Vector3Subtract(tr, br), t));
        left = Vector3Add(left, offset);
        rightEdge = Vector3Add(rightEdge, offset);
        rlVertex3f(left.x, left.y, left.z);
        rlVertex3f(rightEdge.x, rightEdge.y, rightEdge.z);
    }
    rlEnd();
}
float Wall::WallCollideBall(Ball &ball, float dt)
{

    Vector3 p0 = Vector3Subtract(ball.position, position);

    float posNormProduct = Vector3DotProduct(p0, normal);

    float velNormProduct = Vector3DotProduct(ball.velocity, normal);
    if (velNormProduct >= 0.0f)
        return dt; // early out + root out weird collisions

    float t = -posNormProduct / velNormProduct;

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
