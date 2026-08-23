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
    Color color;

    Vector3 corners[4];
    float frictionCoef;
    float bounceCoef;

    Wall(Vector3 pos, Vector3 norm, Vector2 sz, Color color, float friction, float bounce);
    Wall(const Wall &other) = default;
    Wall &operator=(Wall &other) = default;
    float GetSignedDistance(Ball &ball);
    float WallCollideBall(Ball &ball, float dt) const;
    void Draw() const;
};