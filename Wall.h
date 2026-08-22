#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <cassert>
#include "Ball.h"

class Wall
{
public:
    Vector3 position;
    Vector3 normal;
    Vector2 size;

    Vector3 right;
    Vector3 up;

    float frictionCoef;
    float bounceCoef;

    Wall(Vector3 pos, Vector3 norm, Vector2 sz, float friction, float bounce);
    Wall(const Wall &other) = default;
    Wall &operator=(Wall &other) = default;

    float WallCollideBall(Ball &ball, float dt);
    void Draw() const;
};