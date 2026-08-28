
#include "defaults.h"

FollowCam Basic::camera{
    (Vector3){0.0f, 2.0f, -5.0f}, // startPos
    2.0f,                         // turnSpeed
    1.4f,                         // pitchLimit  in radian
    500.0f,                       // moveSpeed
    90.0f,                        // fovy
    200.0f                        // followRadius
};

FreeCam Basic::freeCamera(
    (Vector3){3.0f, 1.0f, -8.0f},
    1.5f,  // turnSpeed
    1.4f,  // pitchLimit
    20.0f, // moveSpeed
    90.0f  // fov
);

PhysicsWorld Basic::world = PhysicsWorld();
