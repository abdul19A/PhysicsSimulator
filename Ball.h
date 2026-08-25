#pragma once

#include <raylib.h>
#include <raymath.h>
#include <vector>

class Ball
{
public:
    Ball() = default;

    Ball(Vector3 position, float weight, float radius, Color color, bool canMove) : position(position), weight(weight), radius(radius), color(color), canMove(canMove)
    {
        velocity = {0.0f, 0.0f, 0.0f};
        netForce = {0.0f, 0.0f, 0.0f};
        collided = false;
    };
    Ball(const Ball &other) = default;
    Ball &operator=(Ball &other) = default;

    // Physics
    void ResetForce() { netForce = {0.0f, 0.0f, 0.0f}; };
    void ApplyGravity(float gravity) { netForce = Vector3Subtract(netForce, {0.0f, gravity, 0.0f}); };
    void ApplyForce(Vector3 force) { netForce = Vector3Add(netForce, force); };
    void ForceToVelocity(float dt) { velocity = Vector3Add(velocity, Vector3Scale(netForce, dt)); };
    void VelocityToPosition(float dt) { position = Vector3Add(position, Vector3Scale(velocity, dt)); };

    void Draw() const;

    Vector3 position;
    Vector3 velocity;
    Vector3 netForce;

    float weight;
    float radius;
    Color color;
    bool canMove;
    bool collided;
};
