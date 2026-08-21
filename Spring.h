#pragma once

#include <vector>
#include <array>
#include <raylib.h>
#include "Ball.h"

class Spring {
public:
    Spring() = default;
    Spring(int topIndex, int botIndex, float baseLength, float k, float c) :
     topIndex(topIndex), botIndex(botIndex), baseLength(baseLength), k(k), c(c) {};
    Spring(const Spring& other) = default;
    Spring& operator=(const Spring& other) = default;

    void ApplyForce(std::vector<Ball>& balls);

    Color color = GREEN;
    int topIndex = -1;
    int botIndex = -1;
    float baseLength = 0.0f;
    float k = 0.0f; // Spring constant
    float c = 0.0f; // Damping constant
};
