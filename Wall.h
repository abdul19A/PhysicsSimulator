#pragma once
#include <algorithm>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

#include "Ball.h"


class Wall {
public:
    Vector3 position;
    Vector3 normal;
    Vector2 size;
    float posNormProduct;

    Vector3 right;
    Vector3 up;

    float frictionCoef;
    float bounceCoef;

    Wall(Vector3 pos, Vector3 norm, Vector2 sz, float friction, float bounce);
    Wall(const Wall& other) = default;
    Wall& operator=(const Wall& other) = default;

    float WallCollideBall(Ball& ball, float dt) const;
    void Draw() const;
};