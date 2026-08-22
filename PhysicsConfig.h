#pragma once
#include <raylib.h>
#include "CameraController.h"
#include "PhysicsWorld.h"

struct Config
{
    FollowCam basicCamera{
        {0.0f, 2.0f, -5.0f}, // startPos
        2.0f,                // turnSpeed
        1.4f,                // pitchLimit  in radian
        5.0f,                // moveSpeed
        90.0f,               // fovy
        8.0f                 // followRadius
    };
    FreeCam basicFreeCamera{
        //{ 0.0f, 5.0f, -20.0f }, // startPos
        {3.0f, 1.0f, -8.0f},
        1.5f, // turnSpeed
        1.4f, // pitchLimit
        5.0f, // moveSpeed
        90.0f // fov
    };

    struct Background
    {
        Color color = {0, 0, 0, 255};
    } background;

    struct Screen
    {
        int width = 1000;
        int height = 800;
        int targetFPS = 60;
    } screen;
    int stepsPerFrame = 100;
};
void setUpWorldDefault(PhysicsWorld &world);
extern Config config;
extern PhysicsWorld configPhysicsWorld;